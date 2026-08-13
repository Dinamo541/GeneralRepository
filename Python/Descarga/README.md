# Descarga completa del sitio EduCore

Herramienta para bajar `http://23.22.58.242/` entero al disco y poder abrirlo
sin conexión, con el mismo aspecto y la misma estructura de carpetas que tiene
en el servidor.

## Puesta en marcha (una sola vez)

```powershell
powershell -ExecutionPolicy Bypass -File setup.ps1
```

Crea un entorno virtual en `.venv` e instala `requests` y `beautifulsoup4`.

> **Por qué hace falta el entorno virtual:** en esta máquina el comando
> `python` del PATH es el de MSYS2 (`C:\msys64\ucrt64\bin\python.exe`), que
> viene **sin pip**, así que ahí no se pueden instalar las dependencias.
> `setup.ps1` usa el lanzador `py -3`, que apunta al CPython oficial de
> Windows, y deja todo aislado en `.venv`.

## Descargar el sitio

```powershell
powershell -ExecutionPolicy Bypass -File descargar.ps1
```

O directamente con el intérprete del entorno:

```powershell
.venv\Scripts\python.exe DownloadSource.py
```

Al terminar tendrás la carpeta `sitio_descargado/`. Ábrela con doble clic en
`index.html`: los enlaces ya son relativos, así que se navega igual que el
sitio real, sin internet y sin servidor.

Si prefieres servirla por HTTP (idéntico al original, con `localhost` en vez
de la IP):

```powershell
.venv\Scripts\python.exe servir.py
```

## Qué se descarga

Del último volcado: **126 archivos, 5.4 MB, 81 páginas HTML, 0 fallos**.

```
sitio_descargado/
├── index.html              portada
├── logica/                 curso TDC400 + sus 43 lecciones
├── arquitectura/           curso EIF205 + sus 30 lecciones
├── lab/                    laboratorio y sus 7 ejercicios
├── static/                 css, js e imágenes del propio servidor
├── _externo/               recursos de CDNs, guardados por dominio
│   ├── cdn.jsdelivr.net/        Bootstrap 5.3.2, MathJax 3, OrbitControls
│   ├── cdnjs.cloudflare.com/    Font Awesome 6.5.1 (+ sus webfonts), three.js
│   ├── fonts.googleapis.com/    hoja de estilos de la fuente Inter
│   └── fonts.gstatic.com/       archivos .woff2 de Inter
├── _manifiesto.json        cada archivo con su URL, tamaño y sha256
└── _estructura.txt         árbol completo de lo descargado
```

Los recursos de CDN se bajan y se enlazan en local a propósito: sin eso la
copia se vería rota en cuanto no hubiera internet, porque el diseño depende de
Bootstrap, de Font Awesome y de la fuente Inter.

## Lo que NO se puede descargar

Por HTTP solo llega lo que el servidor le entrega al navegador: el HTML ya
renderizado, el CSS, el JS y las imágenes. **El código fuente del servidor no
viaja por la red**, así que no se puede obtener con esta herramienta:

- las rutas de Flask (los `@app.route` en Python),
- las plantillas Jinja originales (`templates/*.html`),
- la base de datos o los archivos de datos,
- la configuración de nginx.

Lo que consigues es una copia fiel de **la web publicada**, no del repositorio
del proyecto. Para eso último hay que pedirle el repositorio a quien lo
mantiene.

## Opciones útiles

| Opción | Para qué sirve |
| --- | --- |
| `-o CARPETA` | carpeta de salida (por defecto `sitio_descargado`) |
| `--hilos N` | descargas simultáneas (por defecto 8) |
| `--pausa S` | espera S segundos entre peticiones, para no saturar el servidor |
| `--continuar` | reanuda una descarga interrumpida sin volver a bajar lo que ya está |
| `--sin-reescribir` | deja los archivos exactamente como los sirve el servidor (con rutas absolutas); úsalo junto con `servir.py` |
| `--sin-externos` | no baja nada de los CDNs |
| `--max-paginas N` | tope de páginas; `0` = sin límite |
| `--extra RUTA` | añade una URL de arranque extra (páginas que no están enlazadas) |
| `--subdominios` | rastrea también los subdominios |

Ver todas con `.venv\Scripts\python.exe DownloadSource.py --help`.

## Desde VS Code

En la paleta de comandos → *Run Task*:

- **Descarga: preparar entorno (.venv)**
- **Descarga: descargar sitio completo**
- **Descarga: servir copia local**

Y en el panel de depuración está la configuración **Descarga:
DownloadSource.py**, que ya usa el intérprete del `.venv`.

## Cómo funciona por dentro

1. Parte de la URL base y sigue todos los enlaces del mismo host.
2. De cada página saca `href`, `src`, `srcset`, `poster`, `data-src`, los
   `<style>` y los `style="..."`.
3. De cada CSS saca los `url(...)` y los `@import`: así caen las fuentes
   `.woff2` y las imágenes de fondo, que no aparecen en ningún HTML.
4. Sigue las redirecciones (`/logica` → `/logica/`) y las anota, para que los
   enlaces que apuntaban a la URL vieja sigan funcionando en local.
5. Guarda cada URL en la ruta que le corresponde. Las rutas sin extensión se
   guardan como `carpeta/index.html`, que es lo que evita que `/logica` y
   `/logica/topic/...` choquen entre sí.
6. Al final reescribe todos los enlaces a rutas relativas.
