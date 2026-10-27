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

constexpr uint8_t I2C_SDA    = 27;
constexpr uint8_t I2C_SCL    = 14;
constexpr uint8_t PCF_ADDR   = 0x20; 

constexpr uint8_t PIXEL_PIN  = 13;
constexpr uint8_t PIXEL_NUM  = 9;

constexpr uint8_t DIRECT_BTN_PIN = 33; 
constexpr uint8_t NUM_BUTTONS    = 9;

// ==========================================
// SYSTEM TIMINGS
// ==========================================
constexpr uint32_t DEBOUNCE_DELAY_MS = 50;
constexpr uint32_t I2C_POLL_RATE_MS  = 20;

// ==========================================
// UI LAYOUT CONFIGURATION
// ==========================================
constexpr int GRID_COLS = 3;
constexpr int COL_WIDTH = 106;
constexpr int ROW_HEIGHT = 65;
constexpr int START_X = 5;
constexpr int START_Y = 40;

// ==========================================
// UI STRINGS & LABELS
// ==========================================
constexpr const char* APP_VERSION      = "Alpha 0.0.3";
constexpr const char* UI_STATE_PRESSED = "ON ";
constexpr const char* UI_STATE_IDLE    = "OFF";