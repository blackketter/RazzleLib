#include "RazzleMode.h"

class NoiseMode : public RazzleMode {
  public:
    virtual const char* name() { return "Noise"; }
    virtual void draw(RazzleMatrix* frame) {
      frame->pixels()[random(frame->numPixels())] = random(0x00ffffff);
    };
  private:
};

NoiseMode theNoiseMode;

class WhiteNoiseMode : public RazzleMode {
  public:
    virtual const char* name() { return "WhiteNoise"; }
    virtual void draw(RazzleMatrix* frame) {
      for (led_t i = 0; i < frame->numPixels(); i++) {
        uint8_t y = random(256);
        frame->pixels()[i] = white(y);
      }
    };
  private:
};

WhiteNoiseMode theWhiteNoiseMode;

