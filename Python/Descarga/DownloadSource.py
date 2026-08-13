#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
DownloadSource.py
Descarga completa ("espejo") de un sitio web, conservando la estructura de
carpetas tal cual la sirve el servidor.

Que hace, en orden:
  1. Rastrea (crawl) todas las paginas del mismo host partiendo de la URL base.
  2. Descarga todos los recursos que esas paginas usan: CSS, JS, imagenes,
     fuentes, videos, PDFs... incluidos los que estan en CDNs externos
     (Bootstrap, Font Awesome, Google Fonts, MathJax, three.js, etc.).
  3. Sigue los url(...) y @import de las hojas de estilo, asi que tambien caen
     las fuentes .woff2 y las imagenes de fondo que solo aparecen dentro del CSS.
  4. Reescribe los enlaces a rutas relativas para que la copia se pueda navegar
     sin conexion, haciendo doble clic en index.html (se desactiva con
     --sin-reescribir si prefieres los archivos exactamente como los sirve
     el servidor).
  5. Escribe un manifiesto JSON y un arbol de la estructura descargada.

Uso tipico:
    python DownloadSource.py                          # espeja la URL por defecto
    python DownloadSource.py http://ejemplo.com       # otro sitio
    python DownloadSource.py -o mi_copia              # otra carpeta de salida
    python DownloadSource.py --hilos 4 --pausa 0.2    # mas suave con el servidor
    python DownloadSource.py --continuar              # reanuda sin re-descargar
    python DownloadSource.py --sin-reescribir         # copia cruda, sin tocar

Limite importante: por HTTP solo se puede obtener lo que el servidor entrega al
navegador (HTML ya renderizado, CSS, JS, imagenes). El codigo fuente del
servidor -las rutas de Flask, las plantillas Jinja, la base de datos- no viaja
por la red y por lo tanto no se puede descargar con esta herramienta.
"""

import argparse
import hashlib
import json
import os
import posixpath
import queue
import re
import sys
import threading
import time
from datetime import datetime
from urllib.parse import urljoin, urlsplit, urlunsplit, unquote, quote
from urllib.robotparser import RobotFileParser

try:
    import requests
    from requests.adapters import HTTPAdapter
    from bs4 import BeautifulSoup
except ImportError:
    sys.exit(
        "Faltan dependencias (requests / beautifulsoup4).\n"
        "Ejecuta primero:  powershell -ExecutionPolicy Bypass -File setup.ps1\n"
        "o bien:           py -3 -m pip install -r requirements.txt"
    )

try:
    from urllib3.util.retry import Retry
except ImportError:  # urllib3 muy antiguo empaquetado dentro de requests
    from requests.packages.urllib3.util.retry import Retry  # type: ignore


# --------------------------------------------------------------------------
# Configuracion por defecto
# --------------------------------------------------------------------------

DEFAULT_URL = "https://monkeytype.com"
DEFAULT_OUT = "sitio_descargado"
# User-Agent de navegador real: algunos CDNs (Google Fonts) devuelven formatos
# distintos -woff2 en vez de ttf- segun quien pregunte.
DEFAULT_UA = (
    "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 "
    "(KHTML, like Gecko) Chrome/126.0.0.0 Safari/537.36"
)

EXTERNAL_DIR = "_externo"      # ahi van los recursos de otros dominios
MANIFEST_FILE = "_manifiesto.json"
TREE_FILE = "_estructura.txt"

# Extensiones que reconocemos como recurso descargable cuando aparecen en un
# dominio externo (en el propio dominio se descarga todo lo enlazado).
ASSET_EXTS = {
    ".css", ".js", ".mjs", ".json", ".xml", ".txt", ".map",
    ".png", ".jpg", ".jpeg", ".gif", ".svg", ".webp", ".ico", ".bmp", ".avif",
    ".woff", ".woff2", ".ttf", ".otf", ".eot",
    ".mp4", ".webm", ".ogv", ".mp3", ".wav", ".ogg", ".m4a",
    ".pdf", ".zip", ".csv",
}

# Content-Type -> extension, para ponerle nombre correcto a URLs sin extension
# (por ejemplo https://fonts.googleapis.com/css2?family=Inter, que es CSS).
CT_TO_EXT = {
    "text/html": ".html",
    "application/xhtml+xml": ".html",
    "text/css": ".css",
    "text/javascript": ".js",
    "application/javascript": ".js",
    "application/x-javascript": ".js",
    "application/json": ".json",
    "application/manifest+json": ".json",
    "text/xml": ".xml",
    "application/xml": ".xml",
    "text/plain": ".txt",
    "image/png": ".png",
    "image/jpeg": ".jpg",
    "image/gif": ".gif",
    "image/webp": ".webp",
    "image/avif": ".avif",
    "image/svg+xml": ".svg",
    "image/x-icon": ".ico",
    "image/vnd.microsoft.icon": ".ico",
    "font/woff": ".woff",
    "font/woff2": ".woff2",
    "font/ttf": ".ttf",
    "font/otf": ".otf",
    "application/font-woff": ".woff",
    "application/font-woff2": ".woff2",
    "application/vnd.ms-fontobject": ".eot",
    "application/pdf": ".pdf",
    "video/mp4": ".mp4",
    "video/webm": ".webm",
    "audio/mpeg": ".mp3",
    "audio/ogg": ".ogg",
    "audio/wav": ".wav",
}

# Atributos que contienen una sola URL.
URL_ATTRS = (
    ("a", "href"),
    ("area", "href"),
    ("link", "href"),
    ("script", "src"),
    ("img", "src"),
    ("img", "data-src"),
    ("img", "data-original"),
    ("source", "src"),
    ("iframe", "src"),
    ("frame", "src"),
    ("embed", "src"),
    ("video", "src"),
    ("video", "poster"),
    ("audio", "src"),
    ("track", "src"),
    ("object", "data"),
    ("input", "src"),
)
# Atributos con varias URLs separadas por comas ("imagen.png 2x, otra.png 1x").
SRCSET_ATTRS = (("img", "srcset"), ("source", "srcset"))

# Etiquetas <a>/<iframe> apuntan a paginas; el resto, a recursos.
PAGE_TAGS = {"a", "area", "iframe", "frame"}
# <link rel="..."> que no apuntan a ningun archivo real.
SKIP_LINK_RELS = {"preconnect", "dns-prefetch", "prerender"}

CSS_URL_RE = re.compile(r"""url\(\s*(['"]?)([^'")]+)\1\s*\)""", re.IGNORECASE)
CSS_IMPORT_RE = re.compile(
    r"""@import\s+(?!url\()(['"])([^'"]+)\1""", re.IGNORECASE
)
# Rutas absolutas con extension conocida dentro de archivos .js propios.
JS_REF_RE = re.compile(
    r"""['"]((?:https?:)?/[^'"\s<>]{1,300}?"""
    r"""\.(?:css|js|png|jpe?g|gif|svg|webp|ico|woff2?|ttf|otf|mp4|webm|mp3|"""
    r"""wav|ogg|json|pdf))['"]""",
    re.IGNORECASE,
)

WINDOWS_ILLEGAL = '<>:"|?*\\'
WINDOWS_RESERVED = {
    "CON", "PRN", "AUX", "NUL",
    *(f"COM{i}" for i in range(1, 10)),
    *(f"LPT{i}" for i in range(1, 10)),
}

PRINT_LOCK = threading.Lock()


# --------------------------------------------------------------------------
# Utilidades de URL y de rutas
# --------------------------------------------------------------------------

def normalize_url(url):
    """Normaliza una URL: sin fragmento, host en minusculas, puerto por defecto
    eliminado. Devuelve None si el esquema no es http(s)."""
    try:
        parts = urlsplit(url.strip())
    except ValueError:
        return None
    if parts.scheme.lower() not in ("http", "https"):
        return None
    scheme = parts.scheme.lower()
    host = (parts.hostname or "").lower()
    if not host:
        return None
    port = parts.port
    if port and not ((scheme == "http" and port == 80) or
                     (scheme == "https" and port == 443)):
        host = f"{host}:{port}"
    path = parts.path or "/"
    return urlunsplit((scheme, host, path, parts.query, ""))


def host_of(url):
    return (urlsplit(url).netloc or "").lower()


def same_site(url, base_host, allow_subdomains):
    host = host_of(url)
    if host == base_host:
        return True
    if allow_subdomains:
        bare = base_host.split(":")[0]
        return host.split(":")[0].endswith("." + bare)
    return False


def sanitize_segment(segment):
    """Convierte un tramo de URL en algo que Windows acepte como nombre."""
    cleaned = "".join(
        "_" if (ch in WINDOWS_ILLEGAL or ord(ch) < 32) else ch
        for ch in segment
    )
    cleaned = cleaned.rstrip(" .")
    if not cleaned:
        return "_"
    stem = cleaned.split(".")[0].upper()
    if stem in WINDOWS_RESERVED:
        cleaned = "_" + cleaned
    if len(cleaned) > 120:
        root, ext = os.path.splitext(cleaned)
        digest = hashlib.md5(cleaned.encode("utf-8")).hexdigest()[:8]
        cleaned = root[:100] + "_" + digest + ext[:20]
    return cleaned


def ext_from_content_type(content_type):
    base = (content_type or "").split(";")[0].strip().lower()
    return CT_TO_EXT.get(base, "")


def looks_like_html(content_type, body):
    base = (content_type or "").split(";")[0].strip().lower()
    if base in ("text/html", "application/xhtml+xml"):
        return True
    if base:
        return False
    head = body[:1024].lstrip().lower()
    return head.startswith(b"<!doctype html") or head.startswith(b"<html")


def kind_of(content_type, local_path):
    """Clasifica una respuesta como 'html', 'css', 'js' u 'otro'."""
    base = (content_type or "").split(";")[0].strip().lower()
    ext = os.path.splitext(local_path)[1].lower()
    if base in ("text/html", "application/xhtml+xml") or ext in (".html", ".htm"):
        return "html"
    if base == "text/css" or ext == ".css":
        return "css"
    if base in ("text/javascript", "application/javascript",
                "application/x-javascript") or ext in (".js", ".mjs"):
        return "js"
    return "otro"


def decode_text(body, content_type):
    """Decodifica bytes a texto respetando el charset declarado.
    Devuelve (texto, nombre_del_encoding)."""
    encoding = None
    match = re.search(r"charset=\s*['\"]?([\w\-]+)", content_type or "", re.I)
    if match:
        encoding = match.group(1)
    if not encoding:
        match = re.search(rb"charset=\s*['\"]?([\w\-]+)", body[:2048], re.I)
        if match:
            encoding = match.group(1).decode("ascii", "ignore")
    encoding = encoding or "utf-8"
    try:
        return body.decode(encoding), encoding
    except (UnicodeDecodeError, LookupError):
        return body.decode("utf-8", "replace"), "utf-8"


def human_size(num):
    for unit in ("B", "KB", "MB", "GB"):
        if num < 1024 or unit == "GB":
            return f"{num:.0f} {unit}" if unit == "B" else f"{num:.1f} {unit}"
        num /= 1024.0
    return f"{num:.1f} GB"


def log(message):
    with PRINT_LOCK:
        print(message, flush=True)


# --------------------------------------------------------------------------
# Extraccion de enlaces
# --------------------------------------------------------------------------

def extract_html_refs(soup):
    """Devuelve [(referencia_cruda, es_pagina, es_srcset)] tal como aparece
    escrito en el HTML."""
    refs = []
    for tag_name, attr in URL_ATTRS:
        for tag in soup.find_all(tag_name):
            value = tag.get(attr)
            if not value or not isinstance(value, str):
                continue
            if tag_name == "link":
                rels = {r.lower() for r in (tag.get("rel") or [])}
                if rels & SKIP_LINK_RELS:
                    continue
            refs.append((value.strip(), tag_name in PAGE_TAGS, False))

    for tag_name, attr in SRCSET_ATTRS:
        for tag in soup.find_all(tag_name):
            value = tag.get(attr)
            if value and isinstance(value, str):
                refs.append((value.strip(), False, True))

    for tag in soup.find_all("meta"):
        if (tag.get("http-equiv") or "").lower() == "refresh":
            content = tag.get("content") or ""
            match = re.search(r"url\s*=\s*(.+)", content, re.I)
            if match:
                refs.append((match.group(1).strip().strip("'\""), True, False))
    return refs


def srcset_candidates(value):
    """Separa un srcset en sus URLs individuales."""
    for piece in value.split(","):
        piece = piece.strip()
        if piece:
            yield piece.split()[0]


def extract_css_refs(text):
    """URLs crudas referenciadas dentro de una hoja de estilo."""
    refs = [m.group(2).strip() for m in CSS_URL_RE.finditer(text)]
    refs += [m.group(2).strip() for m in CSS_IMPORT_RE.finditer(text)]
    return [r for r in refs if r and not r.lower().startswith("data:")]


def is_downloadable_ref(ref):
    ref = ref.strip()
    if not ref:
        return False
    low = ref.lower()
    skip = ("#", "mailto:", "javascript:", "tel:", "data:", "about:",
            "sms:", "whatsapp:", "ftp:")
    return not low.startswith(skip)


# --------------------------------------------------------------------------
# Motor de descarga
# --------------------------------------------------------------------------

class Mirror:
    def __init__(self, args):
        base = normalize_url(args.url)
        if not base:
            sys.exit(f"URL invalida: {args.url}")
        self.base_url = base
        self.base_host = host_of(base)
        self.out_dir = os.path.abspath(args.out)
        self.args = args

        self.queue = queue.Queue()
        self.lock = threading.Lock()
        self.thread_local = threading.local()

        self.seen = set()          # URLs ya encoladas
        self.records = {}          # url final -> datos del archivo guardado
        self.url_to_local = {}     # cualquier URL (incl. redirecciones) -> ruta
        self.used_paths = set()    # rutas locales ya ocupadas
        self.failures = {}         # url -> motivo
        self.page_count = 0
        self.done_count = 0
        self.total_bytes = 0
        self.stopped = False

        self.previous = self._load_previous_manifest() if args.resume else {}
        self.robots = self._load_robots() if not args.ignore_robots else None

    # -- infraestructura --------------------------------------------------

    @property
    def session(self):
        session = getattr(self.thread_local, "session", None)
        if session is None:
            session = requests.Session()
            session.headers.update({
                "User-Agent": self.args.user_agent,
                "Accept-Language": "es-ES,es;q=0.9,en;q=0.8",
                "Accept": "*/*",
            })
            retry = Retry(
                total=self.args.retries,
                backoff_factor=0.6,
                status_forcelist=(429, 500, 502, 503, 504),
                allowed_methods=frozenset(["GET", "HEAD"]),
                raise_on_status=False,
            )
            adapter = HTTPAdapter(max_retries=retry,
                                  pool_maxsize=max(4, self.args.workers * 2))
            session.mount("http://", adapter)
            session.mount("https://", adapter)
            self.thread_local.session = session
        return session

    def _load_previous_manifest(self):
        path = os.path.join(self.out_dir, MANIFEST_FILE)
        if not os.path.isfile(path):
            return {}
        try:
            with open(path, "r", encoding="utf-8") as handle:
                data = json.load(handle)
        except (OSError, ValueError):
            return {}
        return {item["url"]: item for item in data.get("archivos", [])}

    def _load_robots(self):
        robots_url = urljoin(self.base_url, "/robots.txt")
        parser = RobotFileParser()
        try:
            response = requests.get(
                robots_url, timeout=self.args.timeout,
                headers={"User-Agent": self.args.user_agent},
            )
            if response.status_code != 200:
                return None
            parser.parse(response.text.splitlines())
            log("[i] robots.txt encontrado: se respetaran sus reglas "
                "(usa --ignorar-robots para saltarlo).")
            return parser
        except requests.RequestException:
            return None

    def allowed_by_robots(self, url):
        if self.robots is None or not same_site(url, self.base_host,
                                                self.args.subdomains):
            return True
        return self.robots.can_fetch(self.args.user_agent, url)

    # -- decision de que se descarga --------------------------------------

    def should_fetch(self, url, is_page):
        if same_site(url, self.base_host, self.args.subdomains):
            return self.allowed_by_robots(url)
        # Dominio externo: solo recursos (CSS/JS/imagenes/fuentes), nunca
        # paginas, para no acabar descargando medio internet.
        if not self.args.externals or is_page:
            return False
        ext = os.path.splitext(urlsplit(url).path)[1].lower()
        # Sin extension puede seguir siendo un recurso valido (Google Fonts),
        # siempre que venga de una etiqueta de recurso y no de un <a>.
        return ext in ASSET_EXTS or ext == ""

    def enqueue(self, url, is_page, depth):
        normalized = normalize_url(url)
        if not normalized:
            return
        with self.lock:
            if normalized in self.seen or self.stopped:
                return
            if not self.should_fetch(normalized, is_page):
                return
            self.seen.add(normalized)
        self.queue.put((normalized, is_page, depth))

    # -- asignacion de ruta local -----------------------------------------

    def local_path_for(self, url, content_type, body):
        parts = urlsplit(url)
        segments = [sanitize_segment(unquote(s))
                    for s in parts.path.split("/") if s]

        if same_site(url, self.base_host, self.args.subdomains):
            prefix = []
        else:
            prefix = [EXTERNAL_DIR, sanitize_segment(parts.netloc)]

        is_html = looks_like_html(content_type, body)
        wanted_ext = ext_from_content_type(content_type)

        if not segments or parts.path.endswith("/"):
            # "/" o ".../carpeta/" -> index.html dentro de la carpeta
            segments.append("index.html" if is_html else "index" + (wanted_ext or ".bin"))
        else:
            last = segments[-1]
            current_ext = os.path.splitext(last)[1].lower()
            if not current_ext:
                if is_html:
                    # /logica -> logica/index.html (asi nunca choca con
                    # /logica/topic/... que necesita 'logica' como carpeta)
                    segments.append("index.html")
                else:
                    segments[-1] = last + (wanted_ext or ".bin")
            elif is_html and current_ext not in (".html", ".htm"):
                # .php, .aspx... se guardan como .html para que el navegador
                # los abra directamente desde el disco.
                segments[-1] = last + ".html"
            elif wanted_ext and current_ext != wanted_ext and current_ext not in ASSET_EXTS:
                segments[-1] = last + wanted_ext

        if parts.query:
            safe_query = re.sub(r"[^A-Za-z0-9]+", "_", parts.query).strip("_")
            digest = hashlib.md5(parts.query.encode("utf-8")).hexdigest()[:8]
            root, ext = os.path.splitext(segments[-1])
            segments[-1] = f"{root}__{safe_query[:40]}_{digest}{ext}"

        relative = posixpath.join(*(prefix + segments))

        # Dos URLs distintas no pueden compartir archivo.
        with self.lock:
            candidate = relative
            counter = 1
            while candidate in self.used_paths:
                root, ext = posixpath.splitext(relative)
                candidate = f"{root}_{counter}{ext}"
                counter += 1
            self.used_paths.add(candidate)
        return candidate

    def write_file(self, relative_path, body):
        full = os.path.join(self.out_dir, relative_path.replace("/", os.sep))
        os.makedirs(os.path.dirname(full) or self.out_dir, exist_ok=True)
        with open(full, "wb") as handle:
            handle.write(body)
        return full

    # -- descarga de una URL ----------------------------------------------

    def fetch(self, url):
        """Descarga una URL, o la recupera del disco si estamos reanudando.

        Devuelve (bytes, content_type, url_final, redirecciones, registro_previo).
        El ultimo elemento es None cuando la descarga fue real.
        """
        cached = self.previous.get(url)
        if cached:
            local = os.path.join(self.out_dir,
                                 cached["local"].replace("/", os.sep))
            if os.path.isfile(local):
                with open(local, "rb") as handle:
                    body = handle.read()
                return body, cached.get("content_type", ""), url, [], cached

        response = self.session.get(
            url, timeout=self.args.timeout, allow_redirects=True,
            stream=False,
        )
        if response.status_code >= 400:
            raise requests.HTTPError(f"HTTP {response.status_code}")
        history = [normalize_url(hop.url) for hop in response.history]
        final = normalize_url(response.url) or url
        return (response.content,
                response.headers.get("Content-Type", ""),
                final,
                [h for h in history if h],
                None)

    def process(self, url, is_page, depth):
        if self.stopped:
            return
        try:
            body, content_type, final_url, history, cached = self.fetch(url)
        except requests.RequestException as exc:
            with self.lock:
                self.failures[url] = str(exc)
            log(f"[!] fallo   {url}  ({exc})")
            return

        with self.lock:
            existing = self.records.get(final_url)
        if existing:
            # Otra URL redirigia aqui y ya lo teniamos guardado.
            with self.lock:
                self.url_to_local[url] = existing["local"]
                for hop in history:
                    self.url_to_local[hop] = existing["local"]
            return

        if cached:
            # Ya estaba en disco: conservamos su ruta y no lo reescribimos
            # otra vez (sus enlaces ya son relativos).
            relative = cached["local"]
            with self.lock:
                self.used_paths.add(relative)
        else:
            relative = self.local_path_for(final_url, content_type, body)
            self.write_file(relative, body)
        text_kind = kind_of(content_type, relative)

        with self.lock:
            self.done_count += 1
            self.total_bytes += len(body)
            index = self.done_count
            self.records[final_url] = {
                "url": final_url,
                "local": relative,
                "content_type": content_type,
                "bytes": len(body),
                "sha256": hashlib.sha256(body).hexdigest(),
                "tipo": text_kind,
                "reescrito": bool(cached and cached.get("reescrito")),
            }
            self.url_to_local[url] = relative
            self.url_to_local[final_url] = relative
            for hop in history:
                self.url_to_local[hop] = relative

        marker = "[=]" if cached else "[+]"
        if not self.args.quiet:
            log(f"{marker} {index:>4}  {human_size(len(body)):>9}  {relative}")

        # Un archivo recuperado del disco que ya tiene los enlaces reescritos
        # no sirve para descubrir URLs: sus rutas ya son relativas y locales.
        # Al reanudar, la semilla son las URLs del manifiesto anterior.
        if not (cached and cached.get("reescrito")):
            self.discover(text_kind, body, content_type, final_url, depth)
        elif text_kind == "html":
            with self.lock:
                self.page_count += 1

        if self.args.delay and not cached:
            time.sleep(self.args.delay)

    def discover(self, text_kind, body, content_type, url, depth):
        """Encola todo lo que este archivo referencia."""
        internal = same_site(url, self.base_host, self.args.subdomains)

        if text_kind == "html":
            if not internal:
                return
            with self.lock:
                self.page_count += 1
                reached = (self.args.max_pages
                           and self.page_count >= self.args.max_pages
                           and not self.stopped)
                if reached:
                    self.stopped = True
            if reached:
                log(f"[i] limite de {self.args.max_pages} paginas alcanzado; "
                    "se detiene el rastreo.")
            if self.args.max_depth and depth >= self.args.max_depth:
                return
            text, _ = decode_text(body, content_type)
            soup = BeautifulSoup(text, "html.parser")
            base_tag = soup.find("base", href=True)
            page_base = urljoin(url, base_tag["href"]) if base_tag else url

            for raw, is_page, is_srcset in extract_html_refs(soup):
                if not is_downloadable_ref(raw):
                    continue
                if is_srcset:
                    for candidate in srcset_candidates(raw):
                        self.enqueue(urljoin(page_base, candidate), False, depth + 1)
                else:
                    self.enqueue(urljoin(page_base, raw), is_page, depth + 1)

            for style in soup.find_all("style"):
                for raw in extract_css_refs(style.get_text() or ""):
                    self.enqueue(urljoin(page_base, raw), False, depth + 1)
            for tag in soup.find_all(style=True):
                for raw in extract_css_refs(tag["style"]):
                    self.enqueue(urljoin(page_base, raw), False, depth + 1)

        elif text_kind == "css":
            # El CSS externo tambien se rastrea: ahi viven las fuentes de
            # Font Awesome y de Google Fonts.
            text, _ = decode_text(body, content_type)
            for raw in extract_css_refs(text):
                if is_downloadable_ref(raw):
                    self.enqueue(urljoin(url, raw), False, depth + 1)

        elif text_kind == "js" and internal and self.args.scan_js:
            text, _ = decode_text(body, content_type)
            for match in JS_REF_RE.finditer(text):
                self.enqueue(urljoin(url, match.group(1)), False, depth + 1)

    # -- bucle principal ---------------------------------------------------

    def worker(self):
        while True:
            url, is_page, depth = self.queue.get()
            try:
                self.process(url, is_page, depth)
            except Exception as exc:                # noqa: BLE001
                with self.lock:
                    self.failures[url] = f"error interno: {exc}"
                log(f"[!] error   {url}  ({exc})")
            finally:
                self.queue.task_done()

    def run(self):
        os.makedirs(self.out_dir, exist_ok=True)
        started = time.time()

        log(f"Sitio base : {self.base_url}")
        log(f"Destino    : {self.out_dir}")
        log(f"Hilos      : {self.args.workers}   "
            f"Pausa: {self.args.delay}s   "
            f"Externos: {'si' if self.args.externals else 'no'}")
        log("-" * 72)

        self.enqueue(self.base_url, True, 0)
        for extra in self.args.extra:
            self.enqueue(urljoin(self.base_url, extra), True, 0)
        if self.previous:
            log(f"[i] Reanudando: {len(self.previous)} URLs conocidas "
                "del manifiesto anterior.")
            for known in self.previous:
                self.enqueue(known, False, 0)

        for _ in range(self.args.workers):
            thread = threading.Thread(target=self.worker, daemon=True)
            thread.start()
        self.queue.join()

        elapsed = time.time() - started
        log("-" * 72)

        if not self.args.no_rewrite:
            log("Reescribiendo enlaces a rutas relativas...")
            changed = self.rewrite_all()
            log(f"  {changed} archivos ajustados para navegacion sin conexion.")

        self.write_manifest(elapsed)
        self.write_tree()
        self.summary(elapsed)

    # -- reescritura de enlaces -------------------------------------------

    def relative_target(self, page_url, page_local, raw_ref):
        """Ruta relativa local para una referencia, o None si no se descargo."""
        if not is_downloadable_ref(raw_ref):
            return None
        ref, sep, fragment = raw_ref.partition("#")
        if not ref.strip():
            return None
        absolute = normalize_url(urljoin(page_url, ref.strip()))
        if not absolute:
            return None
        target = self.url_to_local.get(absolute)
        if not target:
            return None
        start = posixpath.dirname(page_local) or "."
        relative = posixpath.relpath(target, start)
        # Se codifican los espacios y acentos, pero no los caracteres que ya
        # son validos en una ruta (bootstrap@5.3.2 debe seguir legible).
        relative = quote(relative, safe="/._-~()@!$*+,;=")
        return relative + sep + fragment if sep else relative

    @staticmethod
    def replace_attr_value(text, raw, new):
        """Sustituye el valor de atributo `raw` por `new` en el HTML crudo.

        Solo reemplaza cuando el valor coincide entero, y prueba tambien la
        variante con &amp; porque BeautifulSoup ya desescapa las entidades.
        """
        candidates = [raw]
        if "&" in raw:
            candidates.append(raw.replace("&", "&amp;"))
        for candidate in candidates:
            pattern = re.compile(
                r'(=\s*)(["\'])' + re.escape(candidate) + r'\2'
            )
            text, count = pattern.subn(
                lambda m: f"{m.group(1)}{m.group(2)}{new}{m.group(2)}", text
            )
            if count:
                return text, count
        if not re.search(r"[\s\"'<>`]", raw):
            pattern = re.compile(r"(=\s*)" + re.escape(raw) + r"(?=[\s>])")
            text, count = pattern.subn(lambda m: f"{m.group(1)}{new}", text)
            return text, count
        return text, 0

    def rewrite_css_text(self, text, page_url, page_local):
        def url_sub(match):
            quote_char, raw = match.group(1), match.group(2).strip()
            new = self.relative_target(page_url, page_local, raw)
            if not new:
                return match.group(0)
            return f"url({quote_char}{new}{quote_char})"

        def import_sub(match):
            quote_char, raw = match.group(1), match.group(2).strip()
            new = self.relative_target(page_url, page_local, raw)
            if not new:
                return match.group(0)
            return f"@import {quote_char}{new}{quote_char}"

        text = CSS_URL_RE.sub(url_sub, text)
        return CSS_IMPORT_RE.sub(import_sub, text)

    def rewrite_html(self, text, page_url, page_local):
        soup = BeautifulSoup(text, "html.parser")
        base_tag = soup.find("base", href=True)
        page_base = urljoin(page_url, base_tag["href"]) if base_tag else page_url

        pairs = []
        for raw, _is_page, is_srcset in extract_html_refs(soup):
            if is_srcset:                          # se reescribe entero
                pieces = []
                changed = False
                for piece in raw.split(","):
                    piece = piece.strip()
                    if not piece:
                        continue
                    bits = piece.split()
                    new = self.relative_target(page_base, page_local, bits[0])
                    if new:
                        bits[0] = new
                        changed = True
                    pieces.append(" ".join(bits))
                if changed:
                    pairs.append((raw, ", ".join(pieces)))
                continue
            new = self.relative_target(page_base, page_local, raw)
            if new and new != raw:
                pairs.append((raw, new))

        total = 0
        # Los valores mas largos primero: evita que "/a" pise a "/ab".
        for raw, new in sorted(set(pairs), key=lambda p: -len(p[0])):
            text, count = self.replace_attr_value(text, raw, new)
            total += count

        # url(...) de los <style> y de los atributos style="..."
        text = self.rewrite_css_text(text, page_base, page_local)
        return text, total

    def rewrite_all(self):
        changed_files = 0
        for record in list(self.records.values()):
            if record["tipo"] not in ("html", "css") or record.get("reescrito"):
                continue
            full = os.path.join(self.out_dir,
                                record["local"].replace("/", os.sep))
            try:
                with open(full, "rb") as handle:
                    body = handle.read()
            except OSError:
                continue
            text, encoding = decode_text(body, record["content_type"])
            if record["tipo"] == "html":
                new_text, _ = self.rewrite_html(text, record["url"],
                                                record["local"])
            else:
                new_text = self.rewrite_css_text(text, record["url"],
                                                 record["local"])
            record["reescrito"] = True
            if new_text == text:
                continue
            try:
                encoded = new_text.encode(encoding)
            except (UnicodeEncodeError, LookupError):
                encoded = new_text.encode("utf-8")
            with open(full, "wb") as handle:
                handle.write(encoded)
            changed_files += 1
        return changed_files

    # -- salidas finales ---------------------------------------------------

    def write_manifest(self, elapsed):
        data = {
            "url_base": self.base_url,
            "descargado": datetime.now().isoformat(timespec="seconds"),
            "segundos": round(elapsed, 1),
            "enlaces_reescritos": not self.args.no_rewrite,
            "totales": {
                "archivos": len(self.records),
                "paginas_html": self.page_count,
                "bytes": self.total_bytes,
                "fallos": len(self.failures),
            },
            "archivos": sorted(self.records.values(), key=lambda r: r["local"]),
            "fallos": [{"url": u, "motivo": m}
                       for u, m in sorted(self.failures.items())],
        }
        path = os.path.join(self.out_dir, MANIFEST_FILE)
        with open(path, "w", encoding="utf-8") as handle:
            json.dump(data, handle, indent=2, ensure_ascii=False)

    def write_tree(self):
        lines = [f"Estructura de {self.base_url}",
                 f"Generado {datetime.now():%Y-%m-%d %H:%M}", ""]
        skip = {MANIFEST_FILE, TREE_FILE}
        for root, dirs, files in os.walk(self.out_dir):
            dirs.sort()
            depth = root[len(self.out_dir):].count(os.sep)
            name = os.path.basename(root) or "."
            lines.append("    " * depth + name + "/")
            for filename in sorted(files):
                if depth == 0 and filename in skip:
                    continue
                size = os.path.getsize(os.path.join(root, filename))
                lines.append("    " * (depth + 1) +
                             f"{filename}  ({human_size(size)})")
        path = os.path.join(self.out_dir, TREE_FILE)
        with open(path, "w", encoding="utf-8") as handle:
            handle.write("\n".join(lines) + "\n")

    def summary(self, elapsed):
        internal = sum(1 for r in self.records.values()
                       if same_site(r["url"], self.base_host,
                                    self.args.subdomains))
        log("")
        log(f"Listo en {elapsed:.1f}s")
        log(f"  Archivos guardados : {len(self.records)}  "
            f"({internal} del sitio, {len(self.records) - internal} de CDNs)")
        log(f"  Paginas HTML       : {self.page_count}")
        log(f"  Tamano total       : {human_size(self.total_bytes)}")
        log(f"  Fallos             : {len(self.failures)}")
        if self.failures:
            for url, reason in sorted(self.failures.items())[:15]:
                log(f"      - {url}  ({reason})")
            if len(self.failures) > 15:
                log(f"      ... y {len(self.failures) - 15} mas")
        log("")
        log(f"  Carpeta    : {self.out_dir}")
        log(f"  Manifiesto : {MANIFEST_FILE}")
        log(f"  Estructura : {TREE_FILE}")
        index = os.path.join(self.out_dir, "index.html")
        if os.path.isfile(index):
            log("")
            log(f"  Abrelo con doble clic en: {index}")
            log("  O sirvelo igual que el original con:  python servir.py")


# --------------------------------------------------------------------------
# CLI
# --------------------------------------------------------------------------

def parse_args(argv=None):
    parser = argparse.ArgumentParser(
        description="Descarga completa de un sitio web conservando su estructura.",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="Ejemplo:  python DownloadSource.py http://23.22.58.242/ -o copia",
    )
    parser.add_argument("url", nargs="?", default=DEFAULT_URL,
                        help=f"URL base (por defecto {DEFAULT_URL})")
    parser.add_argument("-o", "--out", default=DEFAULT_OUT,
                        help=f"carpeta de salida (por defecto {DEFAULT_OUT})")
    parser.add_argument("--hilos", "--workers", dest="workers", type=int, default=8,
                        help="descargas simultaneas (por defecto 8)")
    parser.add_argument("--pausa", "--delay", dest="delay", type=float, default=0.0,
                        help="segundos de espera tras cada descarga (por defecto 0)")
    parser.add_argument("--max-paginas", "--max-pages", dest="max_pages",
                        type=int, default=5000,
                        help="tope de paginas HTML; 0 = sin limite")
    parser.add_argument("--max-profundidad", "--max-depth", dest="max_depth",
                        type=int, default=0,
                        help="profundidad maxima de enlaces; 0 = sin limite")
    parser.add_argument("--timeout", type=float, default=30.0,
                        help="timeout por peticion en segundos (por defecto 30)")
    parser.add_argument("--reintentos", "--retries", dest="retries",
                        type=int, default=3,
                        help="reintentos ante error de red (por defecto 3)")
    parser.add_argument("--sin-externos", dest="externals", action="store_false",
                        help="no descargar recursos de CDNs externos")
    parser.add_argument("--subdominios", dest="subdomains", action="store_true",
                        help="rastrear tambien los subdominios del sitio")
    parser.add_argument("--sin-reescribir", dest="no_rewrite", action="store_true",
                        help="dejar los archivos tal cual los sirve el servidor")
    parser.add_argument("--sin-js", dest="scan_js", action="store_false",
                        help="no buscar rutas de recursos dentro de los .js")
    parser.add_argument("--continuar", "--resume", dest="resume",
                        action="store_true",
                        help="reutiliza lo ya descargado segun el manifiesto")
    parser.add_argument("--ignorar-robots", dest="ignore_robots",
                        action="store_true",
                        help="no consultar robots.txt")
    parser.add_argument("--extra", action="append", default=[],
                        help="URL o ruta adicional por la que empezar "
                             "(se puede repetir)")
    parser.add_argument("--user-agent", default=DEFAULT_UA,
                        help="User-Agent a enviar")
    parser.add_argument("-q", "--silencioso", dest="quiet", action="store_true",
                        help="no listar cada archivo, solo el resumen final")
    return parser.parse_args(argv)


def main():
    try:
        sys.stdout.reconfigure(encoding="utf-8", errors="replace")
    except (AttributeError, ValueError):
        pass

    args = parse_args()
    args.workers = max(1, args.workers)
    mirror = Mirror(args)
    try:
        mirror.run()
    except KeyboardInterrupt:
        log("\n[i] Interrumpido. Lo descargado hasta ahora sigue en la carpeta; "
            "usa --continuar para reanudar.")
        mirror.write_manifest(0.0)
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
