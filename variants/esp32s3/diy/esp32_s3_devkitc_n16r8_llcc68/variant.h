#define HAS_GPS 0
#undef GPS_RX_PIN
#undef GPS_TX_PIN

#define BUTTON_PIN 0
#define BUTTON_NEED_PULLUP

#define USE_LLCC68

#define LORA_CS 8
#define LORA_SCK 9
#define LORA_MOSI 10
#define LORA_MISO 11
#define LORA_RESET 12
#define LORA_DIO1 14
#define LORA_BUSY 13

#define SX126X_CS LORA_CS
#define SX126X_DIO1 LORA_DIO1
#define SX126X_BUSY LORA_BUSY
#define SX126X_RESET LORA_RESET

// Explicit RF switch control for modules with RXEN/TXEN pins.
// Wire RXEN to GPIO5 and TXEN to GPIO6. DIO2 is not connected to ESP32.
#define SX126X_RXEN 5
#define SX126X_TXEN 6

// DIO3 is not wired for TCXO power on this build.
#define SX126X_MAX_POWER 22
