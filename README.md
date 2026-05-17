# DisplayLib: Complete & Advanced Tutorial

_DisplayLib_ is a robust Arduino library for driving 4-digit 7-segment LED displays (common cathode or anode). This guide covers everything—from installation and wiring to all API features, advanced tricks, and custom segment control!

---

## Table of Contents

1. [Wiring Guide](#wiring-guide)
2. [Installation](#installation)
3. [Getting Started: Basic Example](#getting-started-basic-example)
4. [API Reference](#api-reference)
    - [Constructor Options](#constructor-options)
    - [begin()](#begin)
    - [refresh()](#refresh)
    - [Displaying Integers](#displaying-integers)
    - [Displaying Floats](#displaying-floats)
    - [Text Display](#text-display)
    - [Special Outputs](#special-outputs)
    - [Clearing the Display](#clearing-the-display)
5. [Advanced: Custom Segment Control with `setRawDigit`](#advanced-custom-segment-control-with-setrawdigit)
   - [What is `setRawDigit`](#what-is-setrawdigit)
   - [Segment-to-Bit Mapping](#segment-to-bit-mapping)
   - [Examples: Drawing Custom Patterns](#examples-drawing-custom-patterns)
   - [Practical Use Tips](#practical-use-tips)
   - [Full Bitmask Table for Segment Reference](#full-bitmask-table-for-segment-reference)
6. [Advanced Usage](#advanced-usage)
   - [Multiplexing Optimizations](#multiplexing-optimizations)
   - [Animations and Effects](#animations-and-effects)
   - [Integration with Sensors](#integration-with-sensors)
7. [Troubleshooting](#troubleshooting)
8. [Best Practices & Tips](#best-practices-&-tips)
9. [License](#license)

---

## Wiring Guide

- **Digit Pins:** 4 Arduino pins, each connected to a digit control line on the display.
- **Segment Pins:** 8 Arduino pins, connected in the order:  
  **a, b, c, d, e, f, g, dp**
- **IMPORTANT:** Library assumes this exact pin order for segments.

<sub>Example segment layout for a single digit:</sub>

```
       a
     -----
  f |     | b
    |  g  |
     -----
  e |     | c
    |  d  |
     -----
           . dp
```

### Example Wiring Table

| Display Pin | Function | Arduino Pin (Example) |
|-------------|----------|-----------------------|
| D1          | Digit 1  | 2                     |
| D2          | Digit 2  | 3                     |
| D3          | Digit 3  | 4                     |
| D4          | Digit 4  | 5                     |
| SEG A       | Segment a| 6                     |
| SEG B       | Segment b| 7                     |
| SEG C       | Segment c| 8                     |
| SEG D       | Segment d| 9                     |
| SEG E       | Segment e| 10                    |
| SEG F       | Segment f| 11                    |
| SEG G       | Segment g| 12                    |
| SEG DP      | Decimal  | 13                    |

---

## Installation

1. **Download** the DisplayLib source from GitHub:  
   [Leon-UdrugaMIS/DisplayLib](https://github.com/Leon-UdrugaMIS/DisplayLib)
2. Copy the `DisplayLib.h` and `DisplayLib.cpp` files into your Arduino project's `lib` folder, or the global Arduino libraries directory.
3. In your `.ino` file, include the library:

    ```cpp
    #include <DisplayLib.h>
    ```

---

## Getting Started: Basic Example

```cpp
#include <DisplayLib.h>

const uint8_t digitPins[4] = {2, 3, 4, 5};
const uint8_t segmentPins[8] = {6, 7, 8, 9, 10, 11, 12, 13};

DisplayLib display(digitPins, segmentPins, false); // false = common cathode

void setup() {
  display.begin();
  display.displayFloat(3.14);
}

void loop() {
  display.refresh(); // This must be called repeatedly and as often as possible!
}
```

---

## API Reference

### Constructor Options

```cpp
DisplayLib display(digitPins, segmentPins, isCommonAnode);
```
- `digitPins`: array of 4 pins for digits
- `segmentPins`: array of 8 pins for segments (a,b,c,d,e,f,g,dp)
- `isCommonAnode`: `true` for common anode, `false` for common cathode

### begin()

Initializes the display. Call this in `setup()`.

```cpp
display.begin();
```

### refresh()

**IMPORTANT:** Call this as often as possible in your `loop()` for smooth multiplexing.

```cpp
void loop() {
  display.refresh();
}
```

### Displaying Integers

Display an integer value (up to 4 digits), optionally with leading zeros:

```cpp
display.displayInteger(42, false);   // Displays '42'
display.displayInteger(7, true);     // Displays '0007'
```

### Displaying Floats

Displays a float with decimal placement as appropriate:

```cpp
display.displayFloat(3.14);      // '3.14'
display.displayFloat(-0.56);     // '-0.56'
display.displayFloat(123.456);   // '123.5'
```

### Text Display

Display up to 4-character text (centered if shorter):

```cpp
display.displayText("AbCd");     // 'AbCd'
display.displayText("Hi!");      // 'Hi! '
```

### Special Outputs

**Temperature style:** Displays value and degree symbol (°), rounds floats

```cpp
display.displaySpecialInt(22.5);   // '23°'
```

### Clearing the Display

```cpp
display.clear();
```

---

## Advanced: Custom Segment Control with `setRawDigit`

### What is `setRawDigit`?

The `setRawDigit(index, mask)` function lets you control exactly which segments light up on a digit. This allows:
- Custom characters (including those not in the built-in font)
- Per-digit icons
- Segment-level animations

**Parameters:**
- `index`: The digit to set (0 = leftmost, 3 = rightmost)
- `mask`: An 8-bit value specifying which segments to light.

### Segment-to-Bit Mapping

The `mask` uses 8 bits:  
| Bit | Segment | Decimal | Binary    |
|-----|---------|---------|-----------|
| 0   | a       | 1       | 0b00000001|
| 1   | b       | 2       | 0b00000010|
| 2   | c       | 4       | 0b00000100|
| 3   | d       | 8       | 0b00001000|
| 4   | e       | 16      | 0b00010000|
| 5   | f       | 32      | 0b00100000|
| 6   | g       | 64      | 0b01000000|
| 7   | dp      | 128     | 0b10000000|

### Examples: Drawing Custom Patterns

#### Example 1: Lighting Only the Middle Segment ('g')
```cpp
display.setRawDigit(0, 0b01000000); // Only middle segment 'g' lit on the first digit
```

#### Example 2: Custom Letter 'E' (a, f, g, e, d)
```cpp
// a + f + g + e + d => 0b01111001
display.setRawDigit(1, 0b01111001);
```

#### Example 3: All Segments On
```cpp
display.setRawDigit(2, 0b11111111);
```

#### Example 4: Display a minus sign ('-')
```cpp
display.setRawDigit(2, 0b01000000); // Only segment g
```

#### Example 5: Show a custom pattern with decimal point
```cpp
// a + b + c + dp => 0b10000111
display.setRawDigit(3, 0b10000111);
```

### Practical Use Tips

1. **Combining Modes:**  
   You can mix automatic and manual control. For example, use `displayInteger()` for some digits and `setRawDigit()` for others—but avoid overwriting the same digit in the same cycle unless you clear or update intentionally.

2. **Custom Animations:**  
   Try animating a "running light" or special effect by updating masks over time:
   ```cpp
   uint8_t patterns[] = {
     0b00000001, 0b00000010, 0b00000100, 0b00001000,
     0b00010000, 0b00100000, 0b01000000, 0b10000000
   };
   for (int d = 0; d < 4; ++d) {
     for (int p = 0; p < 8; ++p) {
       display.setRawDigit(d, patterns[p]);
       unsigned long start = millis();
       while (millis() - start < 100) display.refresh();
     }
   }
   ```

3. **Approximating the Degree Symbol (°):**
   - Use segments: a, b, f, g, dp
   ```cpp
   // degree symbol: a + b + f + g + dp
   display.setRawDigit(3, 0b11000011);
   ```

### Full Bitmask Table for Segment Reference

| Segment(s)       | Binary (0b) | Hex   | Decimal |
|------------------|-------------|-------|---------|
| a only           | 00000001    | 0x01  | 1       |
| b only           | 00000010    | 0x02  | 2       |
| c only           | 00000100    | 0x04  | 4       |
| d only           | 00001000    | 0x08  | 8       |
| e only           | 00010000    | 0x10  | 16      |
| f only           | 00100000    | 0x20  | 32      |
| g only           | 01000000    | 0x40  | 64      |
| dp only          | 10000000    | 0x80  | 128     |
| All on           | 11111111    | 0xFF  | 255     |
| — combine bits for multiple segments!              |

**With `setRawDigit`, you can display anything from creative custom characters to full animated effects!**

---

## Advanced Usage

### Multiplexing Optimizations

- Call `display.refresh()` from a timer interrupt for absolute smoothness, or as frequently as possible in the main loop.
- Avoid delaying or blocking the `loop()`, otherwise you'll see flicker or dimming.

### Animations & Effects

- **Counting Animation:**
    ```cpp
    for (int i = 0; i <= 9999; ++i) {
      display.displayInteger(i, true);
      unsigned long start = millis();
      while (millis() - start < 40) display.refresh();
    }
    ```

- **Scrolling Text:**  
   For longer messages, slide across:
    ```cpp
    const char* msg = "HELP";
    char buf[5] = {};
    for (int i = 0; i <= strlen(msg) - 4; ++i) {
      strncpy(buf, &msg[i], 4);
      display.displayText(buf);
      unsigned long start = millis();
      while (millis() - start < 300) display.refresh();
    }
    ```

### Integration with Sensors

- Example: Live temperature display
    ```cpp
    float temperature = readTemperature();
    display.displayFloat(temperature);
    // or for degree output:
    display.displaySpecialInt(temperature);
    ```

---

## Troubleshooting

- **Flickering Display:**  
  `refresh()` not being called often enough; avoid `delay()` or blocking code in loop.
- **Segments Incorrect:**  
  Double-check `segmentPins` wiring (must match a,b,c,d,e,f,g,dp).
- **Digits or Segments Don't Match:**  
  Review `digitPins` ordering and common anode/cathode constructor argument.
- **No Output:**  
  Check wiring, Arduino I/O mode, power supply, and anode/cathode logic.

---

## Best Practices & Tips

- Always call `refresh()` as frequently as possible.
- Prefer non-blocking timing (using `millis()`) over `delay()` for smooth visuals.
- Use `display.clear()` before changing modes to avoid ghosting.
- Consider using transistors for digit lines if high brightness/current is needed.
- Double-check wiring for both digits and segments—order is vital!

---

## License

See the [DisplayLib GitHub repository](https://github.com/Leon-UdrugaMIS/DisplayLib) for license information and updates.

---

**Have fun experimenting and building awesome display projects with DisplayLib!**
