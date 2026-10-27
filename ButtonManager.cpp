#include "ButtonManager.h"
#include "Config.h"
#include "DisplayManager.h" 
#include <Wire.h>
#include <Adafruit_ILI9341.h> 

#define GRID_X(idx) (START_X + ((idx % GRID_COLS) * COL_WIDTH))
#define GRID_Y(idx) (START_Y + ((idx / GRID_COLS) * ROW_HEIGHT))

Button buttons[NUM_BUTTONS] = {
  // Source, HardwareID, LedIdx, Label, UIColor, R, G, B, X, Y, initial states...
  {ButtonSource::PCF8574_EXPANDER, 0, 0, "B0", ILI9341_RED,     255, 0, 0,   GRID_X(0), GRID_Y(0), false, true, 0, 0},
  {ButtonSource::PCF8574_EXPANDER, 1, 1, "B1", ILI9341_BLUE,    0, 0, 255,   GRID_X(1), GRID_Y(1), false, true, 0, 0},
  {ButtonSource::PCF8574_EXPANDER, 2, 2, "B2", ILI9341_GREEN,   0, 255, 0,   GRID_X(2), GRID_Y(2), false, true, 0, 0},
  {ButtonSource::PCF8574_EXPANDER, 3, 3, "B3", ILI9341_YELLOW,  255, 255, 0, GRID_X(3), GRID_Y(3), false, true, 0, 0},
  {ButtonSource::PCF8574_EXPANDER, 4, 4, "B4", ILI9341_CYAN,    0, 255, 255, GRID_X(4), GRID_Y(4), false, true, 0, 0},
  {ButtonSource::PCF8574_EXPANDER, 5, 5, "B5", ILI9341_MAGENTA, 255, 0, 255, GRID_X(5), GRID_Y(5), false, true, 0, 0},
  {ButtonSource::PCF8574_EXPANDER, 6, 6, "B6", ILI9341_ORANGE,  255, 128, 0, GRID_X(6), GRID_Y(6), false, true, 0, 0},
  {ButtonSource::PCF8574_EXPANDER, 7, 7, "B7", ILI9341_PINK,    255, 192, 203,GRID_X(7), GRID_Y(7), false, true, 0, 0},
  
  {ButtonSource::ESP32_GPIO, DIRECT_BTN_PIN, 8, "B8", ILI9341_WHITE, 255, 255, 255, GRID_X(8), GRID_Y(8), false, true, 0, 0}
};

void initButtons() {
  Wire.beginTransmission(PCF_ADDR); 
  Wire.write(0xFF); 
  Wire.endTransmission();

  for (uint8_t i = 0; i < NUM_BUTTONS; i++) {
    if (buttons[i].source == ButtonSource::ESP32_GPIO) {
      pinMode(buttons[i].hardwareId, INPUT_PULLUP);
    }
  }
}

void processButtons(uint8_t expanderState) {
  uint32_t currentTime = millis();

  for (uint8_t i = 0; i < NUM_BUTTONS; i++) {
    Button &btn = buttons[i];
    bool currentRawState;
    
    if (btn.source == ButtonSource::PCF8574_EXPANDER) {
      currentRawState = (expanderState & (1 << btn.hardwareId));
    } else {
      currentRawState = digitalRead(btn.hardwareId);
    }

    if (currentRawState != btn.lastRawState) {
      if ((currentTime - btn.lastDebounceTime) > DEBOUNCE_DELAY_MS) {
        btn.lastRawState = currentRawState;
        btn.lastDebounceTime = currentTime;

        bool isNowPressed = (currentRawState == 0);

        if (btn.isPressed != isNowPressed) {
          btn.isPressed = isNowPressed;
          
          if (btn.isPressed) {
            btn.clickCount++;
            Serial.print(btn.label); Serial.println(F(" PRESSED"));
          } else {
            Serial.print(btn.label); Serial.println(F(" RELEASED"));
          }
          
          updateButtonUI(btn); 
        }
      }
    }
  }
}