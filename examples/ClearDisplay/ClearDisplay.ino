#include "../DisplayExampleCommon.h"

DisplayLib display(kDigitPins, kSegmentPins, false);

void setup() {
  display.begin();
}

void loop() {
  display.displayText("HELP");
  pumpDisplay(display, 1000);
  display.clear();
  pumpDisplay(display, 1000);
}
