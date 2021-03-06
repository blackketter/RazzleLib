#include "RazzleMode.h"

class LinesMode : public RazzleMode {
  public:
    virtual const char* name() { return "Lines"; }
    virtual bool canRun(const RazzleMatrixConfig* m) { return m->width > 2 && m->height > 2; }
    virtual framerate_t fps() { return 5; }

    virtual void draw(RazzleMatrix* frame) {
      uint16_t w = frame->width();
      uint16_t h = frame->height();
      uint16_t x = _lastx;
      uint16_t y = _lasty;
      _lastx = random(w);
      _lasty = random(h);
      CRGB rgb = ColorFromPalette( HeatColors_p, _color++);
      frame->drawLine(x, y, _lastx, _lasty, RazzleMatrix::Color(rgb));
    };
  private:
    uint16_t _lastx, _lasty;
    uint8_t _color;
};

LinesMode theLinesMode;




