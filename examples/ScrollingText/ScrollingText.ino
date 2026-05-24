#include "../DisplayExampleCommon.h"

DisplayLib display(kDigitPins, kSegmentPins, false);
const char message[] = "DISPLAY";

void setup() {
  display.begin();
}

void loop() {
  for (size_t i = 0; i + 4 < sizeof(message); ++i) {
    char window[5] = {0};
    for (uint8_t j = 0; j < 4; ++j) {
      window[j] = message[i + j];
    }
    display.displayText(window);
    pumpDisplay(display, 300);
  }
}
