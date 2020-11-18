#ifndef _RazzleMatrix_
#define _RazzleMatrix_

#include <Clock.h>

// configure FastLED
#define FASTLED_ALLOW_INTERRUPTS 0
#define CHIPSET         WS2811

// suppress extraneous warnings
#define FASTLED_INTERNAL

#include <FastLED.h>
#include <FastLED_NeoMatrix.h>

typedef uint16_t led_t;
typedef float framerate_t;
typedef int16_t pixel_t;
const int MAX_SEGMENTS = 16;

// These need to be statically defined so as to work with the FastLED templates
#ifdef ESP8266
const uint8_t LED_DATA_PIN0 = D2;
const uint8_t LED_DATA_PIN1 = D2;
const uint8_t LED_DATA_PIN2 = D2;
const uint8_t LED_DATA_PIN3 = D2;
const uint8_t LED_DATA_PIN4 = D2;
const uint8_t LED_DATA_PIN5 = D2;
const uint8_t LED_DATA_PIN6 = D2;
const uint8_t LED_DATA_PIN7 = D2;
#endif

#if defined(ESP32)
// 5 is no good
const uint8_t LED_DATA_PIN0 = 23;
const uint8_t LED_DATA_PIN1 = 16;
const uint8_t LED_DATA_PIN2 = 17;
const uint8_t LED_DATA_PIN3 = 19;
const uint8_t LED_DATA_PIN4 = 4;
const uint8_t LED_DATA_PIN5 = 18;
const uint8_t LED_DATA_PIN6 = 13;
const uint8_t LED_DATA_PIN7 = 15;
const uint8_t LED_DATA_PIN8 = 0;
const uint8_t LED_DATA_PIN9 = 2;
#endif

#if defined(CORE_TEENSY)
const uint8_t LED_DATA_PIN0 = 17;
const uint8_t LED_DATA_PIN1 = 17;
const uint8_t LED_DATA_PIN2 = 17;
const uint8_t LED_DATA_PIN3 = 17;
const uint8_t LED_DATA_PIN4 = 17;
const uint8_t LED_DATA_PIN5 = 17;
const uint8_t LED_DATA_PIN6 = 17;
const uint8_t LED_DATA_PIN7 = 17;
#endif

class RazzleMode;

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

    uint8_t getBrightness();  // depends on whether it's day or night
    uint8_t getNightBrightness();
    uint8_t getDayBrightness();
    void setBrightness(uint8_t day, uint8_t night);
    bool isDay();

    bool setLEDMode(const char* newmode);
    bool setLEDMode(RazzleMode* newmode);
    const char* getLEDMode();
    bool isLEDMode(const char* ismode);

    void  idle();

    static const LEDColorCorrection defaultCorrection = TypicalSMD5050; // TypicalLEDStrip;
    static const ColorTemperature defaultTemperature = DirectSunlight;

    RazzleMatrix* frames[2];

    RazzleMode* currentMode() { return currMode; };

    void setRandomScreensaverMode();

    void resetAutoSwitch() { _nextAutoSwitch = _autoSwitchBeginTimeout + Uptime::millis(); };

    void autoSwitchEnable(bool enabled) { _autoSwitchEnable = enabled; }
    bool autoSwitchEnabled() { return _autoSwitchEnable; }

    void autoSwitchInterval(millis_t interval) { _autoSwitchInterval = interval; }
    millis_t autoSwitchInterval() { return _autoSwitchInterval; }

    void autoSwitchBegin(millis_t timeout) { _autoSwitchBeginTimeout = timeout; }
    millis_t autoSwitchBegin() { return _autoSwitchBeginTimeout; }

  private:
    void render(RazzleMatrix* frame);
    void interpolateFrame();

    RazzleMode* currMode = nullptr;

    millis_t lastFrameMillis = 0;
    uint8_t nextFrame = 1;

    millis_t nextFrameMillis = 1;
    uint8_t lastFrame = 0;
    const millis_t defaultFrameInterval = 0;  // as fast as possible
    millis_t frameIntervalMillis = defaultFrameInterval;

    inline void fps(framerate_t f)  { frameIntervalMillis = f ? 1000/f : 0; };
    millis_t nowMillis = 0;

    uint8_t dayBrightness = 128;
    uint8_t nightBrightness = 10;

    millis_t _nextAutoSwitch = 0;
    millis_t _autoSwitchEnable = true;

    millis_t _autoSwitchInterval = 1000 * 30;
    millis_t _autoSwitchBeginTimeout = 1000 * 5;
};

RazzleMatrix* setupLeds(const RazzleMatrixConfig* info);

#endif
