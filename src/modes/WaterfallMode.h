#include "RazzleMode.h"

class WaterfallMode : public RazzleMode {
  public:
    virtual const char* name() { return "Waterfall"; }
    virtual void draw(RazzleMatrix* frame);
    virtual framerate_t fps() { return 15; }
    virtual bool canRun() { return _m->height() >= 4; }
    virtual bool dither() { return false; }
    virtual bool interpolate() { return true; }
  private:

};

WaterfallMode theWaterfallMode;

// here we go
void WaterfallMode::draw(RazzleMatrix* frame) {

  pixel_t h = frame->height();
  pixel_t w = frame->width();

  for (pixel_t x = 0; x <= w; x++) {
    for (pixel_t y = h-1; y > 0; y--) {
        frame->drawPixelCRGB(x, y, frame->getPixelCRGB(x, y-1));
    }
  }

  pixel_t y = 0;
  for (pixel_t x = 0; x <= w; x++) {
    frame->drawPixelCRGB(x,y, white(random(10) == 0 ? 255 : 0));
  }
}
