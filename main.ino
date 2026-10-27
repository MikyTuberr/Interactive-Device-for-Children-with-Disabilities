#include <Wire.h>
#include "Config.h"
#include "LedManager.h"
#include "DisplayManager.h"
#include "ButtonManager.h"

uint32_t lastI2CPollTime = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial && millis() < 2000) {} 
  
  Serial.println(F("System starting...")); 

  Wire.begin(I2C_SDA, I2C_SCL);
  
  initLed();
  initDisplay();
  initButtons();
}

void loop() {
  uint32_t currentTime = millis();

  if (currentTime - lastI2CPollTime >= I2C_POLL_RATE_MS) {
    lastI2CPollTime = currentTime;

    if (Wire.requestFrom(PCF_ADDR, (uint8_t)1) == 1) {
      uint8_t portState = Wire.read();

      processButtons(portState);
      updateLedState(btn0, btn1);
    }
  }
}