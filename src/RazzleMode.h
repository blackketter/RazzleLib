#ifndef _RazzleMode_
#define _RazzleMode_

#include "RazzleMatrix.h"

class RazzleMode {
  public:
    RazzleMode();

    virtual void draw(RazzleMatrix* frame) = 0;
    virtual const char* name() = 0;

    virtual void begin() { _beginTime = Uptime::millis(); }
    virtual void end() { _beginTime = 0; }

    virtual bool wantsToRun() { return false; }
    virtual bool canRun() { return true; }

    virtual bool dither() { return true; } // frames should be dithered
    virtual bool interpolate() { return true; }  // frames should be interpolated
    virtual framerate_t fps() { return 0; } // as fast as possible

    millis_t beginTime() { return _beginTime; }

    CRGB white(uint8_t y) {
      uint32_t y32 = y;
      return y32 + (y32 << 8) + (y32 << 16);
    }

    CRGB red(uint8_t y) {
      uint32_t y32 = y;
      return y32 << 16;
    }
    RazzleMode* next() { return _next; };
    static RazzleMode* first() { return _first; }
    static RazzleMode* named(const char* find);

    static void defaultMatrix(RazzleMatrix* m) { _m = m; }
    static RazzleMatrix* defaultMatrix() { return _m; }

    virtual bool isScreensaver() { return true; }

  protected:
    static RazzleMatrix* _m;

  private:
    RazzleMode* _next = nullptr;
    static RazzleMode* _first;

    millis_t _beginTime = 0;
};

#endif
