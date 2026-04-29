$ErrorActionPreference = "Stop"

$projectRoot = Split-Path -Parent $PSScriptRoot
$env:PLATFORMIO_CORE_DIR = "C:\.pio"

Push-Location $projectRoot
try {
    C:\Users\sodo\.platformio\penv\Scripts\platformio.exe run -e esp32-s3-devkitc-n16r8-sx1262
}
finally {
    Pop-Location
}
