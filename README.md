# DisplayLib

DisplayLib is an Arduino library for 4-digit 7-segment displays.

## Features

- Works with **common cathode** and **common anode** displays
- `refresh()` for multiplex refresh (call frequently in `loop()`)
- `clear()` to clear the full display
- `displayInteger(value, leadingZeros)`
- `displayFloat(value)` with automatic decimal-point placement
- `displayText(text)` for text up to 4 characters (auto-centered)
- `displaySpecialInt(value)` for temperature-like output (`123°`), rounds float input
- `setRawDigit(index, mask)` for custom segment patterns

## Wiring assumptions

- 4 digit-select pins (one per digit)
- 8 segment pins in this order: **a, b, c, d, e, f, g, dp**

## Example

```cpp
#include <DisplayLib.h>

const uint8_t digitPins[4] = {2, 3, 4, 5};
const uint8_t segmentPins[8] = {6, 7, 8, 9, 10, 11, 12, 13};

DisplayLib display(digitPins, segmentPins, false); // false = common cathode

void setup() {
  display.begin();
  display.displayFloat(0.25f);
}

void loop() {
  display.refresh();
}
```
