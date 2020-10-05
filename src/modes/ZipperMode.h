#include "RazzleMode.h"

class ZipperMode : public RazzleMode {
  public:
    virtual const char* name() { return "Zipper"; }
    virtual void draw(RazzleMatrix* frame) {
      _zipper = _zipper % frame->numPixels();
      fill_solid( frame->pixels(), frame->numPixels(), CRGB::Black);
      frame->pixels()[_zipper++] = CRGB::White;
    };
  private:
    led_t _zipper = 0;
};

ZipperMode theZipperMode;
