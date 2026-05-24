#include "../DisplayExampleCommon.h"

DisplayLib display(kDigitPins, kSegmentPins, false);

void setup() {
  display.begin();
  display.displayFloat(3.14f);
}

void loop() {
  display.refresh();
}
