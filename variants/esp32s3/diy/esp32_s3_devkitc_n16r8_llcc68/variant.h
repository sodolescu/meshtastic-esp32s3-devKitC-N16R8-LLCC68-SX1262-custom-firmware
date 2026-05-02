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

// Many SX126x/LLCC68 modules use DIO2 internally for RF TX/RX switching.
// TCXO_OPTIONAL lets Meshtastic try TCXO power and fall back for XTAL modules.
#define SX126X_DIO2_AS_RF_SWITCH
#define SX126X_DIO3_TCXO_VOLTAGE 1.8
#define TCXO_OPTIONAL
#define SX126X_MAX_POWER 22
