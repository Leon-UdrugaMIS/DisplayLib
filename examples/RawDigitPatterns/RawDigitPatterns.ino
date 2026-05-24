#include "../DisplayExampleCommon.h"

DisplayLib display(kDigitPins, kSegmentPins, false);

void setup() {
  display.begin();
}

void loop() {
  display.clear();
  display.setRawDigit(0, 0b01000000);
  refreshDisplayFor(display, 1000);

  display.clear();
  display.setRawDigit(1, 0b01111001);
  refreshDisplayFor(display, 1000);

  display.clear();
  display.setRawDigit(2, 0b11111111);
  refreshDisplayFor(display, 1000);

  display.clear();
  display.setRawDigit(2, 0b01000000);
  refreshDisplayFor(display, 1000);

  display.clear();
  display.setRawDigit(3, 0b10000111);
  refreshDisplayFor(display, 1000);
}
