#pragma once
#include <Adafruit_NeoPixel.h>
#include "ButtonManager.h"

void initLed();
void updateLedState(const Button &b0, const Button &b1);