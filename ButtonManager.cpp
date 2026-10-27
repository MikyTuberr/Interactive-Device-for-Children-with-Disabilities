#include "ButtonManager.h"
#include "Config.h"
#include "DisplayManager.h" 
#include <Wire.h>
#include <Adafruit_ILI9341.h> 

Button btn0 = {0, "P0", ILI9341_RED,  255, 0, 0,   45, 125, false, true, 0, 0};
Button btn1 = {1, "P1", ILI9341_BLUE, 0, 0, 255,   80, 175, false, true, 0, 0};

void initButtons() {
  Wire.beginTransmission(PCF_ADDR);
  Wire.write(0xFF);
  Wire.endTransmission();
}

static void handleDebounce(Button &btn, bool currentRawState) {
  uint32_t currentTime = millis();

  if (currentRawState != btn.lastRawState) {
    if ((currentTime - btn.lastDebounceTime) > DEBOUNCE_DELAY_MS) {
      btn.lastRawState = currentRawState;
      btn.lastDebounceTime = currentTime;

      bool isNowPressed = (currentRawState == 0); 

      if (btn.isPressed != isNowPressed) {
        btn.isPressed = isNowPressed;
        
        if (btn.isPressed) {
          btn.clickCount++;
          Serial.print(btn.label);
          Serial.println(F(" PRESSED"));
        } else {
          Serial.print(btn.label);
          Serial.println(F(" RELEASED"));
        }
        
        updateButtonUI(btn);
      }
    }
  }
}

void processButtons(uint8_t portState) {
  bool rawStateP0 = (portState & (1 << btn0.bitIndex));
  bool rawStateP1 = (portState & (1 << btn1.bitIndex));

  handleDebounce(btn0, rawStateP0);
  handleDebounce(btn1, rawStateP1);
}