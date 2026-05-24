#include "../DisplayExampleCommon.h"

DisplayLib display(kDigitPins, kSegmentPins, false);
bool showPaddedHex = false;

void setup() {
  display.begin();
}

void loop() {
  display.displayHex(showPaddedHex ? 0x00FF : 0x2A, showPaddedHex);
  refreshDisplayFor(display, 1500);
  showPaddedHex = !showPaddedHex;
}
