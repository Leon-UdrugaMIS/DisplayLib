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
  display.clear();
  display.setRawDigit(0, 0b01000000);
  pumpDisplay(display, 1000);

  display.clear();
  display.setRawDigit(1, 0b01111001);
  pumpDisplay(display, 1000);

  display.clear();
  display.setRawDigit(2, 0b11111111);
  pumpDisplay(display, 1000);

  display.clear();
  display.setRawDigit(2, 0b01000000);
  pumpDisplay(display, 1000);

  display.clear();
  display.setRawDigit(3, 0b10000111);
  pumpDisplay(display, 1000);
}
