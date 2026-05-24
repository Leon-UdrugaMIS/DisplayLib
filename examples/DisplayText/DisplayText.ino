#include "../DisplayExampleCommon.h"

DisplayLib display(kDigitPins, kSegmentPins, false);
const char* messages[] = {"AbCd", "Hi!"};
uint8_t index = 0;

void setup() {
  display.begin();
}

void loop() {
  display.displayText(messages[index]);
  refreshDisplayFor(display, 1500);
  index = (index + 1) % (sizeof(messages) / sizeof(messages[0]));
}
