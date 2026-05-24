#include "../DisplayExampleCommon.h"

DisplayLib display(kDigitPins, kSegmentPins, false);
uint8_t brightnessLevels[] = {100, 40, 10, 0};
uint8_t index = 0;

void setup() {
  display.begin();
}

void loop() {
  display.displayText("bri");
  display.setBrightness(brightnessLevels[index]);
  pumpDisplay(display, 1500);
  index = (index + 1) % (sizeof(brightnessLevels) / sizeof(brightnessLevels[0]));
}
