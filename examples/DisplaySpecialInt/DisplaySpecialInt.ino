#include "../DisplayExampleCommon.h"

DisplayLib display(kDigitPins, kSegmentPins, false);
float specialIntValues[] = {22.5f, -3.2f};
uint8_t index = 0;

void setup() {
  display.begin();
}

void loop() {
  display.displaySpecialInt(specialIntValues[index]);
  pumpDisplay(display, 1500);
  index = (index + 1) % (sizeof(specialIntValues) / sizeof(specialIntValues[0]));
}
