#include <DisplayLib.h>

const uint8_t kDigitPins[4] = {2, 3, 4, 5};
const uint8_t kSegmentPins[8] = {6, 7, 8, 9, 10, 11, 12, 13};

DisplayLib display(kDigitPins, kSegmentPins, false);
const char message[] = "DISPLAY";

void pumpDisplay(DisplayLib& display, unsigned long durationMs) {
  const unsigned long start = millis();
  while (millis() - start < durationMs) {
    display.refresh();
  }
}

void setup() {
  display.begin();
}

void loop() {
  for (size_t i = 0; i + 4 <= sizeof(message) - 1; ++i) {
    char window[5] = {0};
    for (uint8_t j = 0; j < 4; ++j) {
      window[j] = message[i + j];
    }
    display.displayText(window);
    pumpDisplay(display, 300);
  }
}
