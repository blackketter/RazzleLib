#ifndef _RazzleLeds_
#define _RazzleLeds_


// suppress extraneous warnings
#define FASTLED_INTERNAL
#define FASTLED_ALLOW_INTERRUPTS 0
#include <FastLED.h>
#include "FastLED_NeoMatrix.h"
#include <Clock.h>

typedef uint16_t led_t;
typedef float framerate_t;
typedef int16_t pixel_t;
const int MAX_SEGMENTS = 16;

struct RazzleMatrixConfig {
  led_t width;
  led_t height;
  EOrder colorOrder;
  uint32_t powerSupplyMilliAmps;
  uint8_t matrixType;
  led_t segment[MAX_SEGMENTS];
};

class RazzleMatrix : public FastLED_NeoMatrix {
  public:
    RazzleMatrix(CRGB *p, uint8_t w, uint8_t h, uint8_t matrixType = NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_ROWS)
      : FastLED_NeoMatrix(p,w,h,matrixType) {}
    led_t numPixels() { return width() * height(); }
    CRGB* pixels() { return (CRGB*)getLeds(); }
};


bool setLEDMode(const char* newmode);
const char* getLEDMode();
bool isLEDMode(const char* ismode);

void setNextLEDMode(bool allowWants = false);
void setNextLEDModeSet();

bool shouldAutoSwitch();

millis_t lastModeSwitch();
void resetLastModeSwitch();

uint8_t getBrightness();  // depends on whether it's day or night
uint8_t getNightBrightness();
uint8_t getDayBrightness();
void setBrightness(uint8_t day, uint8_t night);

bool isDay();

void setLEDMatrix(const RazzleMatrixConfig* m);
void  loopLeds();

CRGB white(uint8_t y);

#endif
