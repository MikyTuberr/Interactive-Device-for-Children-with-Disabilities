#pragma once
#include <stdint.h>

struct Button {
  // Configuration (Immutable - Stored in Flash/Const RAM)
  const uint8_t bitIndex;          
  const char* label;               // Raw pointer, NO String class!
  const uint16_t uiColor;          
  const uint8_t ledR;              
  const uint8_t ledG;              
  const uint8_t ledB;              
  const int yPosStatus;            
  const int yPosCounter;           

  // State Variables (Mutable)
  bool isPressed;            
  bool lastRawState;         
  uint32_t lastDebounceTime; 
  uint32_t clickCount;            
};

extern Button btn0;
extern Button btn1;

void initButtons();
void processButtons(uint8_t portState);