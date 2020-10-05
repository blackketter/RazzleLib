#include "Clock.h"
#include "Console.h"
#include "RazzleMatrix.h"
#include "RazzleMode.h"

class LEDModesCommand : public Command {
  public:
    const char* getName() { return "modes"; }
    const char* getHelp() { return ("list LED modes"); }
    void execute(Console* c, uint8_t paramCount, char** params) {
      RazzleMode* m = RazzleMode::first();
      c->printf("Valid LED modes:\n");
      while (m) {
        c->printf("  %s\n", m->name());
        m = m->next();
      }
    }
};
LEDModesCommand theLEDModesCommand;

class LEDModeCommand : public Command {
  public:
    const char* getName() { return "mode"; }
    const char* getHelp() { return ("set LED mode"); }
    void execute(Console* c, uint8_t paramCount, char** params) {
      if (paramCount == 1) {
        if (RazzleMode::named(params[1])) {
          RazzleMode::defaultMatrix()->setLEDMode(params[1]);
        } else {
          theLEDModesCommand.execute(c,paramCount,params);
        }
      }
      c->printf("LED Mode: %s\n", RazzleMode::defaultMatrix()->getLEDMode());
    }
};
LEDModeCommand theLEDModeCommand;


class BrightnessCommand : public Command {
  public:
    const char* getName() { return "bright"; }
    const char* getHelp() { return ("set global LED brightness"); }
    void execute(Console* c, uint8_t paramCount, char** params) {

      if (paramCount == 1) {
        uint8_t b = atoi(params[1]);
        RazzleMode::defaultMatrix()->setBrightness(b,b);
      } else if (paramCount == 2) {
        RazzleMode::defaultMatrix()->setBrightness(atoi(params[1]),atoi(params[2]));
      }

      c->printf("LED Brightness: day: %d, night: %d (It's %s!)\n", RazzleMode::defaultMatrix()->getDayBrightness(), RazzleMode::defaultMatrix()->getNightBrightness(), RazzleMode::defaultMatrix()->isDay() ? "day" : "night");
    }
};
BrightnessCommand theBrightnessCommand;

class NextCommand : public Command {
  public:
    const char* getName() { return "next"; }
    const char* getHelp() { return ("switch to next mode"); }
    void execute(Console* c, uint8_t paramCount, char** params) {
      RazzleMode::defaultMatrix()->setNextLEDMode(true);
      c->printf("Next LED Mode: %s\n", RazzleMode::defaultMatrix()->getLEDMode());
    }
};
NextCommand theNextCommand;
