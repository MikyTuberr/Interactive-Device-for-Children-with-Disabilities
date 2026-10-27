#include "DisplayManager.h"
#include "Config.h"
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <stdio.h> 

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

void initDisplay() {
  SPI.begin(TFT_SCK, -1, TFT_MOSI, TFT_CS);
  tft.begin(20000000); 
  tft.setRotation(1);
  tft.fillScreen(ILI9341_BLACK);
  
  drawStaticUI();
  
  for (uint8_t i = 0; i < NUM_BUTTONS; i++) {
    updateButtonUI(buttons[i]);
  }
}

void drawStaticUI() {
  tft.setCursor(10, 10);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.println(APP_VERSION); 
  tft.drawFastHLine(10, 30, 300, ILI9341_DARKGREY);
}

void updateButtonUI(const Button &btn) {
  // Draw State (ON/OFF)
  tft.setCursor(btn.uiPosX + 35, btn.uiPosY);
  tft.setTextSize(2);
  
  if (btn.isPressed) {
    tft.setTextColor(ILI9341_WHITE, btn.uiColor);
    tft.print(UI_STATE_PRESSED);
  } else {
    tft.setTextColor(ILI9341_LIGHTGREY, ILI9341_DARKGREY);
    tft.print(UI_STATE_IDLE);
  }

  // Draw Counter
  tft.setCursor(btn.uiPosX, btn.uiPosY + 20);
  tft.setTextColor(btn.uiColor, ILI9341_BLACK);
  tft.setTextSize(2);
  
  char buffer[6];
  snprintf(buffer, sizeof(buffer), "%-4lu", btn.clickCount);
  tft.print(buffer);
}