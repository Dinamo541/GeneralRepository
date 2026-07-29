<#
    Ejecuta el archivo activo de VS Code en una TERMINAL EXTERNA de Windows.

    La compilacion se hace aqui (en la terminal de VS Code) para que los errores
    sigan siendo clicables gracias al problemMatcher; unicamente la EJECUCION se
    abre en una consola aparte, que queda esperando con "pause" al terminar.

    Lo invoca la tarea "Run: archivo activo en terminal externa" (tecla F8).
#>
[CmdletBinding()]
param(
    [Parameter(Mandatory = $true)][string]$Target,
    [Parameter(Mandatory = $true)][string]$Workspace
)

$ErrorActionPreference = 'Stop'

$GppPath = 'C:/Copiladores/mingw64-SFML/bin/g++.exe'
$GccPath = 'C:/Copiladores/mingw64-SFML/bin/gcc.exe'

$SfmlInclude = Join-Path $Workspace '.vscode\include'
$SfmlLib     = Join-Path $Workspace '.vscode\lib'
$SfmlBin     = Join-Path $Workspace '.vscode\bin'

$dir  = [System.IO.Path]::GetDirectoryName($Target)
$base = [System.IO.Path]::GetFileNameWithoutExtension($Target)
$ext  = [System.IO.Path]::GetExtension($Target).ToLowerInvariant()

function Stop-WithError([string]$Message) {
    Write-Host "ERROR: $Message" -ForegroundColor Red
    exit 1
}

# Devuelve la ruta absoluta de una herramienta del PATH, o corta con un mensaje claro.
function Resolve-Tool([string]$Name, [string]$Hint) {
    $cmd = Get-Command $Name -ErrorAction SilentlyContinue
    if (-not $cmd) { Stop-WithError "No se encontro '$Name' en el PATH. $Hint" }
    return $cmd.Source
}

function Invoke-Compiler([string]$Exe, [string[]]$Arguments) {
    if (-not (Test-Path -LiteralPath $Exe)) {
        Stop-WithError "No existe el compilador '$Exe'."
    }
    Write-Host "Compilando: $base$ext" -ForegroundColor Cyan
    & $Exe @Arguments
    if ($LASTEXITCODE -ne 0) {
        Stop-WithError "La compilacion fallo (codigo $LASTEXITCODE)."
    }
}

# Lanza un comando en una consola de Windows independiente de VS Code.
function Start-ExternalConsole {
    param(
        [string]  $WorkingDir,
        [string]  $Command,
        [string]  $Title,
        [string[]]$PathPrepend = @()
    )

    $lines = New-Object System.Collections.Generic.List[string]
    $lines.Add('@echo off')
    $lines.Add('chcp 65001 > nul')
    $lines.Add("title $Title")
    $lines.Add("cd /d ""$WorkingDir""")
    foreach ($p in $PathPrepend) { $lines.Add("set ""PATH=$p;%PATH%""") }
    $lines.Add('echo.')
    $lines.Add($Command)
    $lines.Add('set "_exit=%ERRORLEVEL%"')
    $lines.Add('echo.')
    $lines.Add('echo ============================================================')
    $lines.Add('echo  Proceso terminado. Codigo de salida: %_exit%')
    $lines.Add('pause')
    $lines.Add('del "%~f0" > nul 2>&1')

    # UTF-8 sin BOM: con "chcp 65001" cmd interpreta bien las rutas con acentos.
    $bat = Join-Path $env:TEMP ('vscode-run-{0}.cmd' -f [guid]::NewGuid().ToString('N'))
    [System.IO.File]::WriteAllLines($bat, $lines, (New-Object System.Text.UTF8Encoding($false)))

    Start-Process -FilePath $bat -WorkingDirectory $WorkingDir | Out-Null
    Write-Host "Ejecutando '$Title' en una terminal externa." -ForegroundColor Green
}

<#
    Elige que archivos .cpp/.c compilar, distinguiendo los dos estilos que
    conviven en este repositorio:

      1. Un solo translation unit: Main.cpp hace #include "Funciones.cpp".
         Ahi solo se compila Main.cpp; incluir el otro archivo aparte causaria
         errores de "multiple definition" al enlazar.

      2. Proyecto real de varios archivos: Main.cpp + Clase.cpp, cada uno
         compilado por separado y enlazados juntos.

    Si la carpeta tiene varios main() -- ejercicios sueltos -- se compila solo
    el archivo activo, que es el comportamiento clasico.
#>
function Select-Sources([string]$Directory, [string]$ActiveFile, [string]$Filter) {
    $candidates = @(
        Get-ChildItem -LiteralPath $Directory -Filter $Filter -File |
            Where-Object { -not $_.Name.StartsWith('.') } |
            Sort-Object Name
    )

    $text = @{}
    foreach ($c in $candidates) {
        $text[$c.FullName] = [string](Get-Content -LiteralPath $c.FullName -Raw)
    }

    # Fuentes que otro archivo incorpora con #include "algo.cpp": no se compilan
    # por separado, ya viajan dentro de quien los incluye.
    $included = New-Object 'System.Collections.Generic.HashSet[string]' ([System.StringComparer]::OrdinalIgnoreCase)
    foreach ($c in $candidates) {
        foreach ($m in [regex]::Matches($text[$c.FullName], '(?m)^\s*#\s*include\s*"([^"]+)"')) {
            $name = [System.IO.Path]::GetFileName($m.Groups[1].Value)
            if ($name -like $Filter) { [void]$included.Add($name) }
        }
    }

    $compilable = @($candidates | Where-Object { -not $included.Contains($_.Name) })
    $withMain = @(
        $compilable | Where-Object { $text[$_.FullName] -match '(?m)^\s*(?:int|void)\s+main\s*\(' }
    )

    if ($withMain.Count -eq 1) {
        $entry = $withMain[0]
        # Si el punto de entrada incluye otros .cpp, es un unico translation unit.
        $pullsInSources = [regex]::Matches($text[$entry.FullName], '(?m)^\s*#\s*include\s*"([^"]+)"') |
            Where-Object { [System.IO.Path]::GetFileName($_.Groups[1].Value) -like $Filter }

        $files = if ($pullsInSources) {
            @($entry.FullName)
        } else {
            @($compilable | ForEach-Object { $_.FullName })
        }

        return [pscustomobject]@{ Files = $files; Entry = $entry.BaseName }
    }

    return [pscustomobject]@{
        Files = @($ActiveFile)
        Entry = [System.IO.Path]::GetFileNameWithoutExtension($ActiveFile)
    }
}

function Invoke-NativeBuildAndRun([string]$Compiler, [string]$Filter, [string[]]$ExtraFlags) {
    $picked = Select-Sources -Directory $dir -ActiveFile $Target -Filter $Filter
    $exe    = Join-Path $dir ($picked.Entry + '.exe')

    if ($picked.Files.Count -gt 1) {
        Write-Host ("Enlazando {0} archivos de la carpeta." -f $picked.Files.Count) -ForegroundColor Cyan
    }

    $usesSfml = $picked.Files | Where-Object {
        (Get-Content -LiteralPath $_ -Raw) -match '#include\s*[<"]SFML/'
    }

    $arguments = @('-fdiagnostics-color=always', '-g') + $ExtraFlags + $picked.Files
    $pathPrepend = @()

    if ($usesSfml) {
        Write-Host 'Detectado SFML: agregando includes y librerias del workspace.' -ForegroundColor Cyan
        $arguments += @(
            "-I$SfmlInclude",
            "-L$SfmlLib",
            '-lsfml-graphics', '-lsfml-window', '-lsfml-audio', '-lsfml-system'
        )
        $pathPrepend += $SfmlBin
    }

    $arguments += @('-o', $exe)

    Invoke-Compiler -Exe $Compiler -Arguments $arguments
    Start-ExternalConsole -WorkingDir $dir -Command """$exe""" -Title $picked.Entry -PathPrepend $pathPrepend
}

switch ($ext) {

    { $_ -in '.cpp', '.cc', '.cxx' } {
        Invoke-NativeBuildAndRun -Compiler $GppPath -Filter '*.cpp' -ExtraFlags @('-std=c++17')
    }

    '.c' {
        Invoke-NativeBuildAndRun -Compiler $GccPath -Filter '*.c' -ExtraFlags @('-std=c17')
    }

    '.java' {
        $javac = Resolve-Tool 'javac' 'Instala un JDK y agregalo al PATH.'
        $java  = Resolve-Tool 'java'  'Instala un JDK y agregalo al PATH.'
        $bin   = Join-Path $dir 'bin'
        New-Item -ItemType Directory -Path $bin -Force | Out-Null

        Invoke-Compiler -Exe $javac -Arguments @(
            '-encoding', 'UTF-8', '-sourcepath', $dir, '-d', $bin, $Target
        )
        Start-ExternalConsole -WorkingDir $dir `
            -Command """$java"" -Dfile.encoding=UTF-8 -cp ""$bin"" $base" `
            -Title "Java: $base"
    }

    '.py' {
        $python = Resolve-Tool 'python' 'Instala Python y agregalo al PATH.'
        Start-ExternalConsole -WorkingDir $dir `
            -Command """$python"" -X utf8 ""$Target""" `
            -Title "Python: $base"
    }

    '.js' {
        $node = Resolve-Tool 'node' 'Instala Node.js y agregalo al PATH.'
        Start-ExternalConsole -WorkingDir $dir `
            -Command """$node"" ""$Target""" `
            -Title "Node: $base"
    }

    '.html' {
        Write-Host "Abriendo $base$ext en el navegador." -ForegroundColor Green
        Start-Process -FilePath $Target | Out-Null
    }

    default {
        Stop-WithError "Extension '$ext' no soportada. Se admiten: .cpp .cc .cxx .c .java .py .js .html"
    }
}
