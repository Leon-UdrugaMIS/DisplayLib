#include "../DisplayExampleCommon.h"

DisplayLib display(kDigitPins, kSegmentPins, false);
bool showLeadingZeros = false;

void setup() {
  display.begin();
}

void loop() {
  display.displayInteger(showLeadingZeros ? 7 : 42, showLeadingZeros);
  pumpDisplay(display, 2000);
  showLeadingZeros = !showLeadingZeros;
}
