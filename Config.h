#pragma once
#include <stdint.h>

// ==========================================
// PINS & HARDWARE CONFIGURATION
// ==========================================
constexpr uint8_t TFT_MOSI = 23;
constexpr uint8_t TFT_SCK  = 18;
constexpr uint8_t TFT_CS   = 5;
constexpr uint8_t TFT_DC   = 21;
constexpr uint8_t TFT_RST  = 22;

constexpr uint8_t I2C_SDA  = 27;
constexpr uint8_t I2C_SCL  = 14;
constexpr uint8_t PCF_ADDR = 0x20;

constexpr uint8_t PIXEL_PIN = 13;
constexpr uint8_t PIXEL_NUM = 1;

// ==========================================
// SYSTEM TIMINGS
// ==========================================
constexpr uint32_t DEBOUNCE_DELAY_MS = 50;
constexpr uint32_t I2C_POLL_RATE_MS  = 20;

// ==========================================
// UI STRINGS & LABELS (No Magic Strings!)
// ==========================================
constexpr const char* APP_VERSION       = "ZPB | PRO 1.0.2";
constexpr const char* LBL_P0            = "P0:";
constexpr const char* LBL_P1            = "P1:";
constexpr const char* LBL_COUNTER_P0    = "Counter P0:";
constexpr const char* LBL_COUNTER_P1    = "Counter P1:";
constexpr const char* UI_STATE_PRESSED  = " PRESSED    ";
constexpr const char* UI_STATE_IDLE     = " UNPRESSED  ";