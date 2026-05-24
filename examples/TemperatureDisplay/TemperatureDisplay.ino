#include "../DisplayExampleCommon.h"

DisplayLib display(kDigitPins, kSegmentPins, false);
float temperature = 21.5f;

void setup() {
  display.begin();
}

void loop() {
  display.displayFloat(temperature);
  pumpDisplay(display, 1000);
  temperature += 0.3f;
  if (temperature > 25.0f) {
    temperature = 21.5f;
  }
}
