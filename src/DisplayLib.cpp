#include "DisplayLib.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

namespace {
constexpr uint8_t SEG_A = 1 << 0;
constexpr uint8_t SEG_B = 1 << 1;
constexpr uint8_t SEG_C = 1 << 2;
constexpr uint8_t SEG_D = 1 << 3;
constexpr uint8_t SEG_E = 1 << 4;
constexpr uint8_t SEG_F = 1 << 5;
constexpr uint8_t SEG_G = 1 << 6;
constexpr uint8_t SEG_DP = 1 << 7;
constexpr long kMaxScaledValueWithSign = 1000;
constexpr long kMaxScaledValueNoSign = 10000;
constexpr size_t kIntegerBufferSize = 6;
constexpr size_t kNumberBufferSize = 24;
constexpr size_t kFloatBufferSize = 26;
constexpr float kPowersOfTen[] = {1.0f, 10.0f, 100.0f, 1000.0f};
}

DisplayLib::DisplayLib(const uint8_t digitPins[4], const uint8_t segmentPins[8], bool commonAnode)
    : _activeDigit(0), _commonAnode(commonAnode) {
  for (uint8_t i = 0; i < kDigitCount; ++i) {
    _digitPins[i] = digitPins[i];
    _buffer[i] = 0;
  }
  for (uint8_t i = 0; i < kSegmentCount; ++i) {
    _segmentPins[i] = segmentPins[i];
  }
}

void DisplayLib::begin() {
  for (uint8_t i = 0; i < kDigitCount; ++i) {
    pinMode(_digitPins[i], OUTPUT);
  }
  for (uint8_t i = 0; i < kSegmentCount; ++i) {
    pinMode(_segmentPins[i], OUTPUT);
  }
  clear();
}

void DisplayLib::setAllDigitsOff() {
  for (uint8_t i = 0; i < kDigitCount; ++i) {
    writeDigit(i, false);
  }
}

void DisplayLib::writeDigit(uint8_t index, bool on) {
  const uint8_t activeLevel = _commonAnode ? HIGH : LOW;
  const uint8_t inactiveLevel = _commonAnode ? LOW : HIGH;
  digitalWrite(_digitPins[index], on ? activeLevel : inactiveLevel);
}

void DisplayLib::writeSegments(uint8_t segmentMask) {
  for (uint8_t i = 0; i < kSegmentCount; ++i) {
    const bool on = (segmentMask & (1 << i)) != 0;
    const uint8_t level = _commonAnode ? (on ? LOW : HIGH) : (on ? HIGH : LOW);
    digitalWrite(_segmentPins[i], level);
  }
}

void DisplayLib::refresh() {
  setAllDigitsOff();
  writeSegments(_buffer[_activeDigit]);
  writeDigit(_activeDigit, true);
  _activeDigit = (_activeDigit + 1) % kDigitCount;
}

void DisplayLib::clear() {
  for (uint8_t i = 0; i < kDigitCount; ++i) {
    _buffer[i] = 0;
  }
  setAllDigitsOff();
  writeSegments(0);
}

uint8_t DisplayLib::encodeChar(char c) {
  if (c >= '0' && c <= '9') {
    static const uint8_t kDigits[] = {
        SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,
        SEG_B | SEG_C,
        SEG_A | SEG_B | SEG_D | SEG_E | SEG_G,
        SEG_A | SEG_B | SEG_C | SEG_D | SEG_G,
        SEG_B | SEG_C | SEG_F | SEG_G,
        SEG_A | SEG_C | SEG_D | SEG_F | SEG_G,
        SEG_A | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G,
        SEG_A | SEG_B | SEG_C,
        SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G,
        SEG_A | SEG_B | SEG_C | SEG_D | SEG_F | SEG_G,
    };
    return kDigits[c - '0'];
  }

  switch (c) {
    case '-':
      return SEG_G;
    case ' ':
      return 0;
    case 'A':
    case 'a':
      return SEG_A | SEG_B | SEG_C | SEG_E | SEG_F | SEG_G;
    case 'B':
    case 'b':
      return SEG_C | SEG_D | SEG_E | SEG_F | SEG_G;
    case 'C':
    case 'c':
      return SEG_A | SEG_D | SEG_E | SEG_F;
    case 'D':
    case 'd':
      return SEG_B | SEG_C | SEG_D | SEG_E | SEG_G;
    case 'E':
    case 'e':
      return SEG_A | SEG_D | SEG_E | SEG_F | SEG_G;
    case 'F':
    case 'f':
      return SEG_A | SEG_E | SEG_F | SEG_G;
    case 'H':
    case 'h':
      return SEG_B | SEG_C | SEG_E | SEG_F | SEG_G;
    case 'I':
    case 'i':
      return SEG_E | SEG_F;
    case 'J':
    case 'j':
      return SEG_B | SEG_C | SEG_D | SEG_E;
    case 'L':
    case 'l':
      return SEG_D | SEG_E | SEG_F;
    case 'N':
    case 'n':
      return SEG_C | SEG_E | SEG_G;
    case 'O':
    case 'o':
      return SEG_C | SEG_D | SEG_E | SEG_G;
    case 'P':
    case 'p':
      return SEG_A | SEG_B | SEG_E | SEG_F | SEG_G;
    case 'R':
    case 'r':
      return SEG_E | SEG_G;
    case 'S':
    case 's':
      return SEG_A | SEG_C | SEG_D | SEG_F | SEG_G;
    case 'T':
    case 't':
      return SEG_D | SEG_E | SEG_F | SEG_G;
    case 'U':
    case 'u':
      return SEG_B | SEG_C | SEG_D | SEG_E | SEG_F;
    case 'Y':
    case 'y':
      return SEG_B | SEG_C | SEG_D | SEG_F | SEG_G;
    default:
      return 0;
  }
}

uint8_t DisplayLib::degreeSymbolMask() { return SEG_A | SEG_B | SEG_F | SEG_G; }

void DisplayLib::displayInteger(int value, bool leadingZeros) {
  for (uint8_t i = 0; i < kDigitCount; ++i) {
    _buffer[i] = 0;
  }

  long asLong = static_cast<long>(value);
  if (asLong > 9999 || asLong < -999) {
    displayText("Err");
    return;
  }

  char repr[kIntegerBufferSize];
  if (leadingZeros) {
    if (asLong < 0) {
      snprintf(repr, sizeof(repr), "-%03ld", labs(asLong));
    } else {
      snprintf(repr, sizeof(repr), "%04ld", asLong);
    }
  } else {
    snprintf(repr, sizeof(repr), "%ld", asLong);
  }

  size_t len = strlen(repr);
  if (len > kDigitCount) {
    displayText("Err");
    return;
  }

  uint8_t start = static_cast<uint8_t>(kDigitCount - len);
  for (size_t i = 0; i < len; ++i) {
    _buffer[start + i] = encodeChar(repr[i]);
  }
}

void DisplayLib::displayFloat(float value) {
  for (uint8_t i = 0; i < kDigitCount; ++i) {
    _buffer[i] = 0;
  }

  bool negative = value < 0.0f;
  float absValue = negative ? -value : value;
  int bestDecimals = -1;
  long scaled = 0;

  for (int decimals = 3; decimals >= 0; --decimals) {
    float factor = kPowersOfTen[decimals];
    long candidate = lroundf(absValue * factor);
    long maxDigits = negative ? kMaxScaledValueWithSign : kMaxScaledValueNoSign;
    if (candidate >= maxDigits) {
      continue;
    }
    bestDecimals = decimals;
    scaled = candidate;
    break;
  }

  if (bestDecimals < 0) {
    displayText("Err");
    return;
  }

  while (bestDecimals > 0 && (scaled % 10) == 0) {
    scaled /= 10;
    --bestDecimals;
  }

  long divisor = 1;
  for (int i = 0; i < bestDecimals; ++i) {
    divisor *= 10;
  }

  long integerPart = scaled / divisor;
  long fractionPart = scaled % divisor;

  char numberPart[kNumberBufferSize];
  if (bestDecimals == 0) {
    snprintf(numberPart, sizeof(numberPart), "%ld", integerPart);
  } else {
    snprintf(numberPart, sizeof(numberPart), "%ld.%0*ld", integerPart, bestDecimals, fractionPart);
  }

  char repr[kFloatBufferSize];
  if (negative) {
    snprintf(repr, sizeof(repr), "-%s", numberPart);
  } else {
    snprintf(repr, sizeof(repr), "%s", numberPart);
  }

  size_t len = strlen(repr);
  if (len > 5) {
    displayText("Err");
    return;
  }

  uint8_t visibleCount = 0;
  for (size_t i = 0; i < len; ++i) {
    if (repr[i] != '.') {
      ++visibleCount;
    }
  }

  if (visibleCount > kDigitCount) {
    displayText("Err");
    return;
  }

  uint8_t cursor = static_cast<uint8_t>(kDigitCount - visibleCount);
  uint8_t lastDigit = 0;
  bool hasLastDigit = false;
  for (size_t i = 0; i < len; ++i) {
    if (repr[i] == '.') {
      if (hasLastDigit) {
        _buffer[lastDigit] |= SEG_DP;
      }
      continue;
    }
    _buffer[cursor] = encodeChar(repr[i]);
    lastDigit = cursor;
    hasLastDigit = true;
    ++cursor;
  }
}

void DisplayLib::displayText(const char* text) {
  for (uint8_t i = 0; i < kDigitCount; ++i) {
    _buffer[i] = 0;
  }

  if (text == nullptr) {
    return;
  }

  size_t len = strlen(text);
  bool wasTruncated = false;
  if (len > kDigitCount) {
    len = kDigitCount;
    wasTruncated = true;
  }

  // Integer division intentionally favors left-center for odd padding widths.
  uint8_t start = wasTruncated ? 0 : static_cast<uint8_t>((kDigitCount - len) / 2);

  for (size_t i = 0; i < len; ++i) {
    _buffer[start + i] = encodeChar(text[i]);
  }
}

void DisplayLib::displaySpecialInt(float value) {
  long roundedValue = lroundf(value);
  if (roundedValue > 999 || roundedValue < -99) {
    displayText("Err");
    return;
  }

  for (uint8_t i = 0; i < kDigitCount; ++i) {
    _buffer[i] = 0;
  }

  char repr[kIntegerBufferSize];
  snprintf(repr, sizeof(repr), "%ld", roundedValue);
  size_t len = strlen(repr);
  if (len > 3) {
    displayText("Err");
    return;
  }

  uint8_t start = static_cast<uint8_t>(3 - len);
  for (size_t i = 0; i < len; ++i) {
    _buffer[start + i] = encodeChar(repr[i]);
  }

  _buffer[3] = degreeSymbolMask();
}

void DisplayLib::setRawDigit(uint8_t digitIndex, uint8_t segmentMask) {
  if (digitIndex >= kDigitCount) {
    return;
  }
  _buffer[digitIndex] = segmentMask;
}
