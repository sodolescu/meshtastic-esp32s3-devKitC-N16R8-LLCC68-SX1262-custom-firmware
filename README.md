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
| RXEN | GPIO 5 |
| TXEN | GPIO 6 |

DIO2 is not connected to the ESP32 in this build. RF switching is controlled explicitly by the ESP32 using `RXEN` and `TXEN`.

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
| `esp32-s3-devkitc-n16r8-llcc68.bin` | `6DC033570932648A126E9903CFA198CC181B6916638F5E08AE1D0F91E63C4032` |
| `esp32-s3-devkitc-n16r8-sx1262.bin` | `3C490E3C41B40CD41B7D120B1791A6CAF4BB1F57EF0ACD7064AD4003F41FC1AD` |

## Radio Notes

These variants use explicit MCU-controlled RF switching for modules with `RXEN` and `TXEN` pins:

```c
#define SX126X_RXEN 5
#define SX126X_TXEN 6
```

Optional DIO3 TCXO power is enabled with fallback for XTAL modules:

```c
#define SX126X_DIO3_TCXO_VOLTAGE 1.8
#define TCXO_OPTIONAL
```

## Build

This repository is mainly for flashing the included binaries. To rebuild from source, copy `boards/` and `variants/` into a Meshtastic firmware checkout with PlatformIO installed, then run one of:

```powershell
platformio run -e esp32-s3-devkitc-n16r8-llcc68
platformio run -e esp32-s3-devkitc-n16r8-sx1262
```
