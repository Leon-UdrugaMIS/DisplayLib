#ifndef DISPLAY_LIB_H
#define DISPLAY_LIB_H

#include <Arduino.h>

class DisplayLib {
 public:
  DisplayLib(const uint8_t digitPins[4], const uint8_t segmentPins[8], bool commonAnode = false);

  void begin();
  void refresh();
  void clear();

  void displayInteger(int value, bool leadingZeros = false);
  void displayHex(uint16_t value, bool leadingZeros = false);
  void displayFloat(float value);
  void displayText(const char* text);
  void displaySpecialInt(float value);
  void setBrightness(uint8_t percent);

  // Extra helper for custom segment control (segments are a,b,c,d,e,f,g,dp)
  void setRawDigit(uint8_t digitIndex, uint8_t segmentMask);

 private:
  static const uint8_t kDigitCount = 4;
  static const uint8_t kSegmentCount = 8;
  static const uint8_t kBrightnessSteps = 100;

  uint8_t _digitPins[kDigitCount];
  uint8_t _segmentPins[kSegmentCount];
  uint8_t _buffer[kDigitCount];
  uint8_t _activeDigit;
  bool _commonAnode;
  uint8_t _brightness;
  uint8_t _brightnessPhase;

  void setAllDigitsOff();
  void writeDigit(uint8_t index, bool on);
  void writeSegments(uint8_t segmentMask);

  static uint8_t encodeChar(char c);
  static uint8_t degreeSymbolMask();
};

#endif
