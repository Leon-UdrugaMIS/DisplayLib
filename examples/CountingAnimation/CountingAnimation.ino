#include "../DisplayExampleCommon.h"

DisplayLib display(kDigitPins, kSegmentPins, false);

void setup() {
  display.begin();
}

void loop() {
  for (int i = 0; i <= 9999; ++i) {
    display.displayInteger(i, true);
    pumpDisplay(display, 40);
  }
}
