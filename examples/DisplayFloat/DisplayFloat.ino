#include "../DisplayExampleCommon.h"

DisplayLib display(kDigitPins, kSegmentPins, false);
float values[] = {3.14f, -0.56f, 123.456f};
uint8_t index = 0;

void setup() {
  display.begin();
}

void loop() {
  display.displayFloat(values[index]);
  refreshDisplayFor(display, 1500);
  index = (index + 1) % (sizeof(values) / sizeof(values[0]));
}
