#include "ClockMode.h"
  // TODO: make work with non 5x7 chars
  // TODO: center text (need to draw each character separately)

class WordClockMode : public ClockMode {
  public:
    const char* name() override { return "Word"; }
    void draw(RazzleMatrix* frame) override;
    framerate_t fps() override { return 2*_m->width(); }
    bool canRun() override { return _m->width() >= 5 && _m->height() >= 5 && theClock.hasBeenSet(); }
    bool dither() override { return false; }
    bool interpolate() override { return false; }
    void begin() override {
      RazzleMode::begin();
      _scrollPos = _m->width();
      _iterations = 0;
    }
    virtual String message();
  protected:
    pixel_t _scrollPos = 0;
    int _iterations = -1;
};

String WordClockMode::message() {
  char time[10];
  sprintf(time, "%d:%02d", theClock.hourFormat12(), theClock.minute());
  String m = time;
  return m;
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

  String m = message();
  frame->print(m);

  pixel_t totalw = m.length() * textsize * 6;
  // loop around
  if (-_scrollPos > totalw) {
    _scrollPos = _m->width();
    _iterations++;
  } else {
    _scrollPos--;
  }
}

WordClockMode theWordClockMode;

class VerticalWordClockMode : public WordClockMode {
  public:
    const char* name() override { return "VWord"; }
    void draw(RazzleMatrix* frame) override;
    framerate_t fps() override { return 2*_m->height(); }
    void begin() override {
      RazzleMode::begin();
      _scrollPos = _m->height();
      _iterations = 0;
    }
};

void VerticalWordClockMode::draw(RazzleMatrix* frame) {

  uint8_t textsize = frame->width()/5;
  if (textsize < 1) { textsize = 1; }
  pixel_t xoffset = (frame->width() - (textsize * 5))/2; 
  pixel_t lineheight = textsize * 8;
 
  frame->fillScreen(LED_BLACK);
  frame->setTextColor(LED_RED_HIGH, LED_BLACK);
  frame->setTextSize(textsize);
  frame->setTextWrap(false);

  String m = message();
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
    _scrollPos = _m->height();
    _iterations++;
  } else {
    _scrollPos--;
  }
}

VerticalWordClockMode theVerticalWordClockMode;

class MessageMode : public WordClockMode {
  public:
    const char* name() override { return "Msg"; }
    bool canRun() override { return true; }
    bool wantsToRun() override { return _iterations == 0; }
    bool isScreensaver() override { return _msg.length() > 0; }
    String message() override { return _msg; };
    virtual void setMessage(String& m) { _msg = m; };

  protected:
    String _msg = "Hello World!";

};
MessageMode theMessageMode;

class MessageCommand : public Command {
  public:
    const char* getName() override { return "msg"; }
    const char* getHelp() override { return ("<text> - display message"); }
    void execute(Console* c, uint8_t paramCount, char** params) {
      if (paramCount > 0) {
        String msg;
        for (int i = 1; i <= paramCount; i++) {
          msg += params[i];
          if (i < paramCount)
            msg += ' ';
        }
        theMessageMode.setMessage(msg);
      }
      RazzleMode::defaultMatrix()->setLEDMode(&theMessageMode);
    }
};
MessageCommand theMessageCommand;

class VMessageMode : public VerticalWordClockMode {
  public:
    const char* name() override { return "VMsg"; }
    bool canRun() override { return true; }
    bool wantsToRun() override { return _iterations == 0; }
    bool isScreensaver() override { return _msg.length() > 0; }

    String message() override { return _msg; };
    virtual void setMessage(String& m) { _msg = m; };

  protected:
    String _msg = "Hello World!";

};
VMessageMode theVMessageMode;

class VMessageCommand : public Command {
  public:
    const char* getName() override { return "vmsg"; }
    const char* getHelp() override { return ("<text> - display message vertically"); }
    void execute(Console* c, uint8_t paramCount, char** params) override {
      if (paramCount > 0) {
        String msg;
        for (int i = 1; i <= paramCount; i++) {
          msg += params[i];
          if (i < paramCount)
            msg += ' ';
        }
        theVMessageMode.setMessage(msg);
      }
      RazzleMode::defaultMatrix()->setLEDMode(&theVMessageMode);
    }
};
VMessageCommand theVMessageCommand;
