#include "LedManager.h"
#include "Config.h"

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(PIXEL_NUM, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

static uint32_t ledColorBuffer[PIXEL_NUM] = {0};

void initLed() {
  pixels.begin();
  pixels.setBrightness(50);
  
  for (uint8_t i = 0; i < PIXEL_NUM; i++) {
    ledColorBuffer[i] = 0;
    pixels.setPixelColor(i, 0);
  }
  pixels.show();
}

void updateLedState(Button* btnArray) {
  bool stateChanged = false;

  for (uint8_t i = 0; i < NUM_BUTTONS; i++) {
    const Button &btn = btnArray[i];
    uint32_t targetColor;

    if (btn.isPressed) {

      targetColor = pixels.Color(btn.ledR, btn.ledG, btn.ledB);
    } else {
      targetColor = pixels.Color(0, 0, 0); // Wyłączona
    }

    if (ledColorBuffer[btn.ledIndex] != targetColor) {
      ledColorBuffer[btn.ledIndex] = targetColor;
      pixels.setPixelColor(btn.ledIndex, targetColor);
      stateChanged = true;
    }
  }

  if (stateChanged) {
    pixels.show();
  }
}