#include "../DisplayExampleCommon.h"

DisplayLib display(kDigitPins, kSegmentPins, false);

void setup() {
  display.begin();
}

void loop() {
  display.displayText("HELP");
  refreshDisplayFor(display, 1000);
  display.clear();
  refreshDisplayFor(display, 1000);
}
