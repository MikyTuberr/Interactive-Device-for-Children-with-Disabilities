#pragma once
#include <Arduino.h>
#include "Config.h"

enum class ButtonSource {
  PCF8574_EXPANDER,
  ESP32_GPIO
};

struct Button {
  const ButtonSource source;       
  const uint8_t hardwareId;        
  const uint8_t ledIndex;          
  
  const char* label;               
  const uint16_t uiColor;          
  const uint8_t ledR;              
  const uint8_t ledG;              
  const uint8_t ledB;              
  const int uiPosX;                
  const int uiPosY;                

  bool isPressed;            
  bool lastRawState;         
  uint32_t lastDebounceTime; 
  uint32_t clickCount;            
};

extern Button buttons[NUM_BUTTONS];

void initButtons();
void processButtons(uint8_t expanderState);