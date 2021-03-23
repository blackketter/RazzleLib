#include "ClockMode.h"

class WordClockMode : public ClockMode {
  public:
    virtual const char* name() { return "Word"; }
    virtual void draw(RazzleMatrix* frame);
    virtual framerate_t fps() { return 2*_m->width(); }
    virtual bool canRun() { return _m->width() >= 5 && _m->height() >= 5 && theClock.hasBeenSet(); }
    virtual bool dither() { return false; }
    virtual bool interpolate() { return false; }
    virtual void begin() {
      RazzleMode::begin();
      _scrollPos = _m->width();
    }
    virtual void message(String& m);
  protected:
    pixel_t _scrollPos = 0;
};

void WordClockMode::message(String& m) {
  char time[10];
  sprintf(time, "  %d:%02d  ", theClock.hourFormat12(), theClock.minute());
  m = time;
}

// here we go
void WordClockMode::draw(RazzleMatrix* frame) {

  frame->fillScreen(LED_BLACK);
  frame->setTextColor(LED_RED_HIGH, LED_BLACK),
  frame->setCursor(_scrollPos, 0);
  uint8_t textsize = frame->height()/7;
  if (textsize < 1) { textsize = 1; }
  frame->setTextSize(textsize);
  frame->setTextWrap(false);

  String m;
  message(m);
  frame->print(m);

  pixel_t totalw = m.length() * textsize * 6;
  // loop around
  if (-_scrollPos > totalw) {
    _scrollPos = 0;
  } else {
    _scrollPos--;
  }
}

WordClockMode theWordClockMode;

class VerticalWordClockMode : public WordClockMode {
  public:
    virtual const char* name() { return "VWord"; }
    virtual void draw(RazzleMatrix* frame);
    virtual framerate_t fps() { return 30; }
   virtual void begin() {
      RazzleMode::begin();
      _scrollPos = _m->height();
    }
};

  // TODO: make work with non 5x7 chars
  // TODO: center text (need to draw each character separately)
void VerticalWordClockMode::draw(RazzleMatrix* frame) {

  uint8_t textsize = frame->width()/5;
  if (textsize < 1) { textsize = 1; }
  pixel_t xoffset = (frame->width() - (textsize * 5))/2; 
  pixel_t lineheight = textsize * 8;
 
  frame->fillScreen(LED_BLACK);
  frame->setTextColor(LED_RED_HIGH, LED_BLACK);
  frame->setTextSize(textsize);
  frame->setTextWrap(false);

  String m;
  message(m);
  int i = 0;
  pixel_t ypos = _scrollPos;
  while (m[i]) {
    frame->setCursor(xoffset, ypos);
    frame->print(m[i]);
    i++;
    ypos += lineheight;
  }
  
  pixel_t totalheight = lineheight * m.length();
  // loop around
  if (-_scrollPos > totalheight) {
    _scrollPos = 0;
  } else {
    _scrollPos--;
  }
}

VerticalWordClockMode theVerticalWordClockMode;
