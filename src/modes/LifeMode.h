#include "RazzleMode.h"

class LifeMode : public RazzleMode {
  public:
    virtual const char* name() { return "Life"; }
    virtual void draw(RazzleMatrix* frame);
    virtual framerate_t fps() { return 1; };
    virtual bool canRun() { return _m->numPixels() > 10; }
  private:
};

LifeMode theLifeMode;

void LifeMode::draw(RazzleMatrix* frame) {
  int count = 0;

  static int iterations = 0;
  for (led_t i = 0; i < frame->numPixels(); i++) {
    if (frame->pixels()[i]) { count++; }
  };

  led_t seed_width = 3;
  if (count == 0 || iterations > 100) {
    fill_solid( frame->pixels(), frame->numPixels(), CRGB::Black);
    for (led_t i = ((frame->numPixels()/2) - seed_width/2); i < ((frame->numPixels()/2)+seed_width/2); i++) {
      if (random(2)) { frame->pixels()[i] = CRGB::White; }
    }
    iterations = 0;
  } else {
    uint8_t rule = 110;
    CRGB temp[frame->numPixels()+2];
    for (led_t i = 0; i < frame->numPixels(); i++) {
      uint8_t cur_pattern = (frame->pixels()[i-1]!=(CRGB)CRGB::Black)*4 + (frame->pixels()[i]!=(CRGB)CRGB::Black)*2 + (frame->pixels()[i+1]!=(CRGB)CRGB::Black);
      temp[i] = ((rule >> cur_pattern)&0x01) ? CRGB::White : CRGB::Black;
    }
    memmove( frame->pixels(), temp, frame->numPixels() * sizeof( CRGB) );
    iterations++;
  }
}
