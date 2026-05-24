#pragma once

#include <Arduino.h>
#include <DisplayLib.h>

constexpr uint8_t kDigitPins[4] = {2, 3, 4, 5};
constexpr uint8_t kSegmentPins[8] = {6, 7, 8, 9, 10, 11, 12, 13};

inline void pumpDisplay(DisplayLib& display, unsigned long durationMs) {
  const unsigned long start = millis();
  while ((millis() - start) < durationMs) {
    display.refresh();
  }
}
