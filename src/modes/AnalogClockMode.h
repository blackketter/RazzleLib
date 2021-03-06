#include "ClockMode.h"

class AnalogClockMode : public ClockMode {
  public:
    virtual const char* name() { return "Analog"; }
    virtual void draw(RazzleMatrix* frame);
    virtual framerate_t fps() { return 1.0; }
    virtual bool canRun() { return _m->width() > 7 && _m->height() > 7 && theClock.hasBeenSet(); }
    virtual bool dither() { return false; }
  private:

};

AnalogClockMode theAnalogClockMode;

// here we go
void AnalogClockMode::draw(RazzleMatrix* frame) {

  frame->fillScreen(LED_BLACK);

  pixel_t centerX = frame->width()/2;
  pixel_t centerY = frame->height()/2;
  pixel_t r = (centerX > centerY ? centerY : centerX);
  // draw face circle
  // frame->drawCircle(centerX, centerY, r, LED_WHITE_HIGH);

  float len;
  pixel_t endX, endY;
  float hour, minute, second;
  second = (float)theClock.second() + (float)theClock.fracMillis()/1000.0;
  minute = theClock.minute() + second/60.0;

  hour = theClock.hour();
    if (hour > 11) {
    hour = hour - 12;
  }
  hour = hour+minute/60.0;

  // draw minute hand
  len = r;
  endX = sin(minute / 60.0 * M_PI * 2.0)*len;
  endY = -cos(minute / 60.0 * M_PI * 2.0)*len;
  frame->drawLine(centerX, centerY, centerX+endX, centerY+endY, LED_ORANGE_HIGH);
  frame->drawLine(centerX-1, centerY, centerX+endX, centerY+endY, LED_ORANGE_HIGH);
  frame->drawLine(centerX, centerY-1, centerX+endX, centerY+endY, LED_ORANGE_HIGH);
  frame->drawLine(centerX-1, centerY-1, centerX+endX, centerY+endY, LED_ORANGE_HIGH);

  // draw hour hand
  len = (r*1)/2;
  endX = sin(hour / 12.0 * M_PI * 2.0)*len;
  endY = -cos(hour / 12.0 * M_PI * 2.0)*len;
  frame->drawLine(centerX, centerY, centerX+endX, centerY+endY, LED_RED_HIGH);
  frame->drawLine(centerX, centerY-1, centerX+endX, centerY+endY-1, LED_RED_HIGH);
  frame->drawLine(centerX-1, centerY, centerX+endX-1, centerY+endY, LED_RED_HIGH);
  frame->drawLine(centerX-1, centerY-1, centerX+endX-1, centerY+endY-1, LED_RED_HIGH);

  // draw second hand
  len = r;
  endX = sin(second / 60.0 * M_PI * 2.0)*len;
  endY = -cos(second / 60.0 * M_PI * 2.0)*len;
    frame->drawPixel(centerX+endX, centerY+endY, LED_WHITE_HIGH);
//  frame->drawLine(centerX, centerY, centerX+endX, centerY+endY, LED_WHITE_HIGH);


  // draw am/pm indicator
  if (!theClock.isAM()) {
    frame->drawPixel(frame->width()-1, frame->height()-1, LED_RED_HIGH);
  }
}
