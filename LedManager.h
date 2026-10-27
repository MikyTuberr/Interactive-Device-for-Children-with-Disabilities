#pragma once
#include <Adafruit_NeoPixel.h>
#include "ButtonManager.h"

void initLed();
void updateLedState(Button* btnArray);