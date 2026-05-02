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

## Required LoRa Setup

After a factory flash, Meshtastic starts with `lora.region` unset. Set the legal region for your country on both boards before transmitting. For US testing with one LLCC68 board and one SX1262 board, use the same custom modem profile on both boards:

```powershell
meshtastic --port COMx --set lora.region US
meshtastic --port COMx --set lora.use_preset false
meshtastic --port COMx --set lora.bandwidth 125
meshtastic --port COMx --set lora.spread_factor 9
meshtastic --port COMx --set lora.coding_rate 5
meshtastic --port COMx --reboot
```

`LONG_FAST` in the US region does not work as a shared LLCC68/SX1262 profile on this build because the LLCC68 path rejects the wide/SF11 settings and falls back to a different effective bitrate. The custom profile above was verified both directions between the two boards.

## Checksums

| Firmware | SHA-256 |
| --- | --- |
| `esp32-s3-devkitc-n16r8-llcc68.bin` | `52C85F038DCC1FFF622D06F861A5FF6197525A203796DD4CA45148EA6D732E75` |
| `esp32-s3-devkitc-n16r8-sx1262.bin` | `88E36E44C175F7745FA8C0CDC51454D79F9EA2F2DF4EDD090F099A24960B56D0` |

## Radio Notes

These variants use explicit MCU-controlled RF switching for modules with `RXEN` and `TXEN` pins:

```c
#define SX126X_RXEN 5
#define SX126X_TXEN 6
```

DIO3 TCXO power is not enabled in these binaries:

```c
// DIO3 is not wired for TCXO power on this build.
```

The board definitions use UART serial (`ARDUINO_USB_CDC_ON_BOOT=0`) so `meshtastic --port COMx` works through the DevKitC USB-UART bridge.

## Build

This repository is mainly for flashing the included binaries. To rebuild from source, copy `boards/` and `variants/` into a Meshtastic firmware checkout with PlatformIO installed, then run one of:

```powershell
platformio run -e esp32-s3-devkitc-n16r8-llcc68
platformio run -e esp32-s3-devkitc-n16r8-sx1262
```
