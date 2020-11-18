#include "RazzleMode.h"


class MathMode : public RazzleMode {
  public:
    virtual const char* name() override { return "Math"; }

    virtual void begin() override {
      beginMicros = Uptime::micros();
    }

    virtual void draw(RazzleMatrix* frame) {
      int w = frame->width();
      int h = frame->height();
      float d = 1.0f / max(w,h);
      int i = 0;
      float t = (float)(Uptime::micros() - beginMicros)/(float)Clock::microsPerSec;
      for (int x = 0; x < w; x++) {
        for (int y = 0; y < h; y++) {
          frame->drawPixelCRGB(x, y, color(t,x*d,y*d,i));
          i++;
        }
      }
    }

    virtual CRGB color(float t, float x, float y, float i) {
      float intensity = pixel( t,  x,  y,  i);
      CRGB c = 0;
      if (intensity < 0) {
        c = red(-intensity * 255);
      } else if (intensity > 0) {
        c = white(intensity * 255);
      }
      return c;
    }

    virtual float pixel(float t, float x, float y, float i) = 0;

   private:
    micros_t beginMicros;
};

//////////////////////////////////////////////////////////////////////////////

class SineMode : public MathMode {
  public:
    virtual const char* name() override { return "Sine"; }
    virtual float pixel(float t, float x, float y, float i) override {
        return sinf(y+t*4);
    }
};

SineMode theSineMode;

class SplashMode : public MathMode {
  public:
    virtual const char* name() override { return "Splash"; }
    virtual float pixel(float t, float x, float y, float i) override {
        return sinf((t/2.0f-sqrtf(powf((x-0.5f),2.0f)+powf((y-0.25f),2.0f)))*8.0f);
    }
};

SplashMode theSplashMode;

