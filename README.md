# Meshtastic ESP32-S3 DevKitC N16R8 Custom Firmware

Custom Meshtastic firmware builds for an ESP32-S3 DevKitC N16R8 wired to SX126x-family LoRa radios.

## Boards

| Project | Radio | Firmware |
| --- | --- | --- |
| `esp32-s3-devkitc-n16r8-llcc68` | LLCC68 | `firmware/esp32-s3-devkitc-n16r8-llcc68.bin` |
| `esp32-s3-devkitc-n16r8-sx1262` | SX1262 | `firmware/esp32-s3-devkitc-n16r8-sx1262.bin` |

## Radio Pinout

Both variants use the same SPI and control pins:

| Radio pin | ESP32-S3 GPIO |
| --- | --- |
| NSS / CS | GPIO 8 |
| SCK | GPIO 9 |
| MOSI | GPIO 10 |
| MISO | GPIO 11 |
| NRST / RESET | GPIO 12 |
| BUSY | GPIO 13 |
| DIO1 | GPIO 14 |

## Files

- `boards/` contains PlatformIO board definitions for the ESP32-S3 DevKitC N16R8.
- `variants/esp32s3/diy/` contains Meshtastic variant files for LLCC68 and SX1262.
- `firmware/` contains ready-to-flash factory binaries.
- `scripts/` contains helper PowerShell scripts for rebuilding inside a Meshtastic firmware checkout.

## Build

Copy `boards/` and `variants/` into a Meshtastic firmware checkout, then run one of:

```powershell
.\scripts\build-llcc68.ps1
.\scripts\build-sx1262.ps1
```

The build scripts expect PlatformIO at:

```text
C:\Users\x\.platformio\penv\Scripts\platformio.exe
```

## Flash

The files in `firmware/` are combined factory images and should be flashed at offset `0x0`.

Example:

```powershell
esptool.py --chip esp32s3 --port COMx --baud 921600 write_flash 0x0 firmware\esp32-s3-devkitc-n16r8-llcc68.bin
```

Replace `COMx` with the ESP32-S3 serial port.
