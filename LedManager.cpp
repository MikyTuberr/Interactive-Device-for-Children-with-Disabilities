#include "LedManager.h"
#include "Config.h"

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(PIXEL_NUM, PIXEL_PIN, NEO_GRB + NEO_KHZ800);
uint32_t currentLedColor = 0; 

void initLed() {
  pixels.begin();
  pixels.setBrightness(50);
  currentLedColor = pixels.Color(0, 0, 0); // Start OFF
  pixels.setPixelColor(0, currentLedColor);
  pixels.show();
}

void updateLedState(const Button &b0, const Button &b1) {
  uint32_t targetColor;

  if (b0.isPressed && b1.isPressed) {
    uint8_t mixedR = ((uint16_t)b0.ledR + b1.ledR) > 255 ? 255 : (b0.ledR + b1.ledR);
    uint8_t mixedG = ((uint16_t)b0.ledG + b1.ledG) > 255 ? 255 : (b0.ledG + b1.ledG);
    uint8_t mixedB = ((uint16_t)b0.ledB + b1.ledB) > 255 ? 255 : (b0.ledB + b1.ledB);
    
    targetColor = pixels.Color(mixedR, mixedG, mixedB);
  } 
  else if (b0.isPressed) {
    targetColor = pixels.Color(b0.ledR, b0.ledG, b0.ledB);
  } 
  else if (b1.isPressed) {
    targetColor = pixels.Color(b1.ledR, b1.ledG, b1.ledB);
  } 
  else {
    targetColor = pixels.Color(0, 0, 0); // Off
  }

  if (currentLedColor != targetColor) {
    currentLedColor = targetColor;
    pixels.setPixelColor(0, currentLedColor);
    pixels.show();
  }
}