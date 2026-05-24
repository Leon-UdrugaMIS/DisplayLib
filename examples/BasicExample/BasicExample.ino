#include <DisplayLib.h>

const uint8_t kDigitPins[4] = {2, 3, 4, 5};
const uint8_t kSegmentPins[8] = {6, 7, 8, 9, 10, 11, 12, 13};

DisplayLib display(kDigitPins, kSegmentPins, false);

void setup() {
  display.begin();
  display.displayFloat(3.14f);
}

void loop() {
  display.refresh();
}
