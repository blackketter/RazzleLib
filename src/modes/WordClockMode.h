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
      scrollPos = _m->width();
    }
  private:
    pixel_t scrollPos = 0;
};


// here we go
void WordClockMode::draw(RazzleMatrix* frame) {

  frame->fillScreen(LED_BLACK);
  frame->setTextColor(LED_RED_HIGH, LED_BLACK),
  frame->setCursor(scrollPos, 0);
  uint8_t size = frame->height()/7;
  frame->setTextSize(size);
  frame->setTextWrap(false);

  char time[100];

  sprintf(time, "  %d:%02d  ", theClock.hourFormat12(), theClock.minute());

  frame->print(time);

  // calculate string width
  // FIXME getTextBounds clips to screen :(  )
  int16_t x1,y1;
  uint16_t w,h;
  scrollPos--;
  uint16_t totalw = 0;
  totalw = strlen(time);
  int i = 0;
  // assumes we can fit a whole character on the screen width
  while (time[i] != 0) {
    char c[2];
    c[0] = time[i];
    c[1] = 0;
    frame->getTextBounds(c, 0, 0, &x1, &y1, &w, &h);
    totalw += w;
    i++;
  }

  // loop around
  if (-scrollPos > totalw) {
    scrollPos = 0;
  }

}

WordClockMode theWordClockMode;
/*
MOTDMode theMOTDMode;
SayMode theSayMode;

class SayCommand : public Command {
  public:
    const char* getName() { return "say"; }
    const char* getHelp() { return "Print text"; }
    void execute(Console* c, uint8_t paramCount, char** params) {
      c->println("Goodbye!");
      console.stop();
    }
};
ExitCommand theExitCommand;
*/
