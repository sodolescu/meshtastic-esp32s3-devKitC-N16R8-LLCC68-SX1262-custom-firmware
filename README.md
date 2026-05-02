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

## Flash

The files in `firmware/` are combined factory images and should be flashed at offset `0x0`.

1. Download the correct `.bin` file from `firmware/`.
2. Connect the ESP32-S3 DevKitC and put it in bootloader mode if it does not enter automatically.
3. Flash with `esptool.py`, replacing `COMx` with your serial port.

LLCC68:

```powershell
esptool.py --chip esp32s3 --port COMx --baud 921600 write_flash 0x0 firmware\esp32-s3-devkitc-n16r8-llcc68.bin
```

SX1262:

```powershell
esptool.py --chip esp32s3 --port COMx --baud 921600 write_flash 0x0 firmware\esp32-s3-devkitc-n16r8-sx1262.bin
```

## Checksums

| Firmware | SHA-256 |
| --- | --- |
| `esp32-s3-devkitc-n16r8-llcc68.bin` | `DA735B2228616D0123AD627A2E7BD4DCC6B4C128F51E85BBA536803E8E4A8240` |
| `esp32-s3-devkitc-n16r8-sx1262.bin` | `87F553761B182310EF5B453CFBD4C586DE05F331AD78B5E43ABEE82CC829F8BF` |

## Radio Notes

These variants enable DIO2 RF switching and optional DIO3 TCXO power for SX126x-family modules. This is required by many bare LLCC68/SX1262 modules even when DIO2/DIO3 are not wired to ESP32 GPIO pins.

## Build

This repository is mainly for flashing the included binaries. To rebuild from source, copy `boards/` and `variants/` into a Meshtastic firmware checkout with PlatformIO installed, then run one of:

```powershell
platformio run -e esp32-s3-devkitc-n16r8-llcc68
platformio run -e esp32-s3-devkitc-n16r8-sx1262
```
