#include "ClockMode.h"

class DigitalClockMode : public ClockMode {
  public:
    virtual const char* name() { return "Digital"; }
    virtual void draw(RazzleMatrix* frame);
    virtual framerate_t fps() { return 0.5; }
    virtual bool canRun() { return _m->width() > 10 && _m->height() > 10 && theClock.hasBeenSet(); }
    virtual bool dither() { return false; }
  private:
    uint8_t _colorindex;

};

DigitalClockMode theDigitalClockMode;

// here we go
void DigitalClockMode::draw(RazzleMatrix* frame) {

  frame->fillScreen(LED_BLACK);

  pixel_t centerX = frame->width()/2;
  pixel_t centerY = frame->height()/2;

  int size = frame->width()/10;

  CRGB c = ColorFromPalette( HeatColors_p, random(16,240));
  if ( theClock.hourFormat12() > 9) {
    frame->drawChar(0, 0, (theClock.hourFormat12() / 10)+'0', RazzleMatrix::Color(c), LED_BLACK, size);
  }

  char d = (theClock.hourFormat12() % 10) + '0';
  if (d == '0') d = 'O';
  c = ColorFromPalette( HeatColors_p, random(16,240));
  frame->drawChar(centerX, 0, d, RazzleMatrix::Color(c), LED_BLACK, size);

  d = (theClock.minute()/10)+'0';
  if (d == '0') d = 'O';
  c = ColorFromPalette( HeatColors_p, random(16,240));
  frame->drawChar(0, centerY, d, RazzleMatrix::Color(c), LED_BLACK, size);

  d = (theClock.minute()%10)+'0';
  if (d == '0') d = 'O';
  c = ColorFromPalette( HeatColors_p, random(16,240));
  frame->drawChar(centerX, centerY, d, RazzleMatrix::Color(c), LED_BLACK, size);
}
