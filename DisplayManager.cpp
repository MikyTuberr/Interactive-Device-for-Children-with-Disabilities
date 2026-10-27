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
  updateButtonUI(btn0);
  updateButtonUI(btn1);
}

void drawStaticUI() {
  tft.setCursor(15, 10);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.println(APP_VERSION); 
  tft.drawFastHLine(10, 32, 300, ILI9341_BLUE);

  tft.setTextColor(ILI9341_LIGHTGREY);
  tft.setCursor(15, 45);  tft.print(LBL_P0);
  tft.setCursor(15, 80);  tft.print(LBL_P1);
  tft.setCursor(15, 125); tft.print(LBL_COUNTER_P0);
  tft.setCursor(15, 175); tft.print(LBL_COUNTER_P1);
}

void updateButtonUI(const Button &btn) {
  tft.setCursor(60, btn.yPosStatus);
  tft.setTextSize(2);
  
  if (btn.isPressed) {
    tft.setTextColor(ILI9341_WHITE, btn.uiColor);
    tft.print(UI_STATE_PRESSED);
  } else {
    tft.setTextColor(ILI9341_LIGHTGREY, ILI9341_DARKGREY);
    tft.print(UI_STATE_IDLE);
  }

  tft.setCursor(160, btn.yPosCounter);
  tft.setTextColor(btn.uiColor, ILI9341_BLACK);
  tft.setTextSize(3);
  
  char buffer[8];
  snprintf(buffer, sizeof(buffer), "%-5lu", btn.clickCount);
  tft.print(buffer);
}