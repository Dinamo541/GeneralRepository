#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
servir.py
Sirve la copia descargada por HTTP, igual que lo hace el servidor original.

Util sobre todo si descargaste con --sin-reescribir: en ese caso los HTML
conservan rutas absolutas (/static/css/base.css) que solo funcionan servidas
desde la raiz de un servidor, no abriendo el archivo con doble clic.

Uso:
    python servir.py                       # sirve ./sitio_descargado en :8000
    python servir.py -d otra_carpeta       # otra carpeta
    python servir.py -p 5500               # otro puerto
    python servir.py --no-abrir            # no abrir el navegador
"""

import argparse
import os
import sys
import webbrowser
from functools import partial
from http.server import SimpleHTTPRequestHandler, ThreadingHTTPServer

DEFAULT_DIR = "sitio_descargado"
DEFAULT_PORT = 8000

EXTRA_TYPES = {
    ".woff2": "font/woff2",
    ".woff": "font/woff",
    ".ttf": "font/ttf",
    ".otf": "font/otf",
    ".webp": "image/webp",
    ".avif": "image/avif",
    ".mjs": "text/javascript",
    ".map": "application/json",
}


class SiteHandler(SimpleHTTPRequestHandler):
    """Igual que el servidor estatico estandar, pero resolviendo las rutas sin
    extension del estilo /logica/topic/topic1/proposiciones."""

    extensions_map = {**SimpleHTTPRequestHandler.extensions_map, **EXTRA_TYPES}

    def translate_path(self, path):
        local = super().translate_path(path)
        if os.path.isdir(local) or os.path.isfile(local):
            return local
        # /ruta -> /ruta/index.html  y  /ruta -> /ruta.html
        for candidate in (os.path.join(local, "index.html"), local + ".html"):
            if os.path.isfile(candidate):
                return candidate
        return local

    def guess_type(self, path):
        base = super().guess_type(path)
        if base in ("text/html", "text/css", "text/javascript",
                    "application/javascript"):
            return base + "; charset=utf-8"
        return base

    def log_message(self, fmt, *args):
        if not self.server.quiet:            # type: ignore[attr-defined]
            sys.stderr.write("  %s\n" % (fmt % args))


def main():
    parser = argparse.ArgumentParser(
        description="Sirve por HTTP la copia local del sitio."
    )
    parser.add_argument("-d", "--dir", default=DEFAULT_DIR,
                        help=f"carpeta a servir (por defecto {DEFAULT_DIR})")
    parser.add_argument("-p", "--puerto", "--port", dest="port",
                        type=int, default=DEFAULT_PORT,
                        help=f"puerto (por defecto {DEFAULT_PORT})")
    parser.add_argument("--no-abrir", dest="open_browser", action="store_false",
                        help="no abrir el navegador automaticamente")
    parser.add_argument("-q", "--silencioso", dest="quiet", action="store_true",
                        help="no registrar cada peticion")
    args = parser.parse_args()

    root = os.path.abspath(args.dir)
    if not os.path.isdir(root):
        sys.exit(f"No existe la carpeta '{root}'.\n"
                 "Descarga primero el sitio con:  python DownloadSource.py")

    handler = partial(SiteHandler, directory=root)
    server = ThreadingHTTPServer(("127.0.0.1", args.port), handler)
    server.quiet = args.quiet                # type: ignore[attr-defined]

    url = f"http://localhost:{args.port}/"
    print(f"Sirviendo {root}")
    print(f"  -> {url}")
    print("  Ctrl+C para detener.\n")
    if args.open_browser:
        webbrowser.open(url)
    try:
        server.serve_forever()
    except KeyboardInterrupt:
        print("\nServidor detenido.")
    finally:
        server.server_close()


if __name__ == "__main__":
    main()
