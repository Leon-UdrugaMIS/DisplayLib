#include "../DisplayExampleCommon.h"

DisplayLib display(kDigitPins, kSegmentPins, false);
// displaySpecialInt() rounds these float inputs before showing the degree symbol.
float specialValues[] = {22.5f, -3.2f};
uint8_t index = 0;

void setup() {
  display.begin();
}

void loop() {
  display.displaySpecialInt(specialValues[index]);
  pumpDisplay(display, 1500);
  index = (index + 1) % (sizeof(specialValues) / sizeof(specialValues[0]));
}
