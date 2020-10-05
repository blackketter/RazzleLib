#include "RazzleMode.h"

class FlashesMode : public RazzleMode {
  public:
    virtual const char* name() { return "Flashes"; }
    virtual void draw(RazzleMatrix* frame) {
      fill_solid( frame->pixels(), frame->numPixels(), CRGB::Black);
      frame->pixels()[random(frame->numPixels())] = CRGB::White;
    };
  private:
};

FlashesMode theFlashesMode;



