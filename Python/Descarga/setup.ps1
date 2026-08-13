# setup.ps1
# Prepara el entorno para DownloadSource.py: crea un entorno virtual en
# .venv e instala las dependencias de requirements.txt.
#
# Uso:
#   powershell -ExecutionPolicy Bypass -File setup.ps1
#   powershell -ExecutionPolicy Bypass -File setup.ps1 -Recrear

[CmdletBinding()]
param(
    [switch]$Recrear
)

$ErrorActionPreference = 'Stop'
$here = Split-Path -Parent $MyInvocation.MyCommand.Definition
$venv = Join-Path $here '.venv'
$venvPython = Join-Path $venv 'Scripts\python.exe'

function Find-BasePython {
    # El 'python' del PATH puede ser el de MSYS2, que viene sin pip.
    # El lanzador 'py' apunta al CPython oficial de Windows, que si lo trae.
    if (Get-Command py -ErrorAction SilentlyContinue) {
        & py -3 -c "import sys" 2>$null
        if ($LASTEXITCODE -eq 0) { return @('py', '-3') }
    }
    foreach ($name in @('python', 'python3')) {
        $cmd = Get-Command $name -ErrorAction SilentlyContinue
        if (-not $cmd) { continue }
        & $cmd.Source -m pip --version 2>$null | Out-Null
        if ($LASTEXITCODE -eq 0) { return @($cmd.Source) }
    }
    return $null
}

Write-Host "== Preparando entorno en $here ==" -ForegroundColor Cyan

if ($Recrear -and (Test-Path $venv)) {
    Write-Host "Borrando el entorno anterior..."
    Remove-Item -Recurse -Force $venv
}

if (-not (Test-Path $venvPython)) {
    $base = Find-BasePython
    if (-not $base) {
        Write-Host ""
        Write-Host "No encontre un Python con pip." -ForegroundColor Red
        Write-Host "Instala Python desde https://www.python.org/downloads/ " -NoNewline
        Write-Host "marcando 'Add python.exe to PATH'."
        exit 1
    }
    Write-Host "Creando entorno virtual con: $($base -join ' ')"
    if ($base.Count -eq 2) {
        & $base[0] $base[1] -m venv $venv
    } else {
        & $base[0] -m venv $venv
    }
    if (-not (Test-Path $venvPython)) {
        Write-Host "No se pudo crear el entorno virtual." -ForegroundColor Red
        exit 1
    }
} else {
    Write-Host "El entorno virtual ya existe (usa -Recrear para rehacerlo)."
}

Write-Host "Actualizando pip..."
& $venvPython -m pip install --upgrade pip --quiet

Write-Host "Instalando dependencias..."
& $venvPython -m pip install -r (Join-Path $here 'requirements.txt') --quiet
if ($LASTEXITCODE -ne 0) {
    Write-Host "Fallo la instalacion de dependencias." -ForegroundColor Red
    exit 1
}

Write-Host ""
Write-Host "Entorno listo." -ForegroundColor Green
& $venvPython -c "import requests, bs4; print('  requests', requests.__version__); print('  beautifulsoup4', bs4.__version__)"
Write-Host ""
Write-Host "Siguiente paso:" -ForegroundColor Cyan
Write-Host "  powershell -ExecutionPolicy Bypass -File descargar.ps1"
