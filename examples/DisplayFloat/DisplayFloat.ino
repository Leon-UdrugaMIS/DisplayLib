#include <DisplayLib.h>

const uint8_t kDigitPins[4] = {2, 3, 4, 5};
const uint8_t kSegmentPins[8] = {6, 7, 8, 9, 10, 11, 12, 13};

DisplayLib display(kDigitPins, kSegmentPins, false);
float values[] = {3.14f, -0.56f, 123.456f};
uint8_t index = 0;

void pumpDisplay(DisplayLib& display, unsigned long durationMs) {
  const unsigned long start = millis();
  while (millis() - start < durationMs) {
    display.refresh();
  }
}

void setup() {
  display.begin();
}

void loop() {
  display.displayFloat(values[index]);
  pumpDisplay(display, 1500);
  index = (index + 1) % (sizeof(values) / sizeof(values[0]));
}
