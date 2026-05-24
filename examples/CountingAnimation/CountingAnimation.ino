#include <DisplayLib.h>

const uint8_t kDigitPins[4] = {2, 3, 4, 5};
const uint8_t kSegmentPins[8] = {6, 7, 8, 9, 10, 11, 12, 13};

DisplayLib display(kDigitPins, kSegmentPins, false);

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
  for (int i = 0; i <= 9999; ++i) {
    display.displayInteger(i, true);
    pumpDisplay(display, 40);
  }
}
