# descargar.ps1
# Descarga el sitio completo usando el entorno virtual de .venv.
# Si el entorno no existe, lo crea llamando a setup.ps1.
#
# Uso:
#   powershell -ExecutionPolicy Bypass -File descargar.ps1
#   powershell -ExecutionPolicy Bypass -File descargar.ps1 -Url http://otro.sitio/
#   powershell -ExecutionPolicy Bypass -File descargar.ps1 -Servir
#   powershell -ExecutionPolicy Bypass -File descargar.ps1 -Extra '--continuar'

[CmdletBinding()]
param(
    [string]$Url = 'http://23.22.58.242/',
    [string]$Salida = 'sitio_descargado',
    [switch]$Servir,
    [string[]]$Extra = @()
)

$ErrorActionPreference = 'Stop'
$here = Split-Path -Parent $MyInvocation.MyCommand.Definition
$venvPython = Join-Path $here '.venv\Scripts\python.exe'

if (-not (Test-Path $venvPython)) {
    Write-Host "El entorno no existe todavia; lo preparo ahora." -ForegroundColor Yellow
    & powershell -NoProfile -ExecutionPolicy Bypass -File (Join-Path $here 'setup.ps1')
    if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
}

Push-Location $here
try {
    $argumentos = @('DownloadSource.py', $Url, '-o', $Salida) + $Extra
    Write-Host "== Descargando $Url ==" -ForegroundColor Cyan
    & $venvPython @argumentos
    $codigo = $LASTEXITCODE

    if ($codigo -eq 0 -and $Servir) {
        Write-Host ""
        Write-Host "== Sirviendo la copia local ==" -ForegroundColor Cyan
        & $venvPython 'servir.py' '-d' $Salida
    }
} finally {
    Pop-Location
}

exit $codigo
