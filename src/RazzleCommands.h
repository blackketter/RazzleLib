#include "Clock.h"
#include "Console.h"
#include "RazzleMatrix.h"
#include "RazzleMode.h"

class LEDModeCommand : public Command {
  public:
    const char* getName() { return "mode"; }
    const char* getHelp() { return ("set LED mode"); }
    void execute(Console* c, uint8_t paramCount, char** params) {
      if ((paramCount == 1) && RazzleMode::named(params[1])) {
        RazzleMode::defaultMatrix()->setLEDMode(params[1]);
        RazzleMode::defaultMatrix()->resetAutoSwitch();
      } else {
        RazzleMode* m = RazzleMode::first();
        c->printf("Valid LED modes:\n");
        while (m) {
          c->printf("  %s %s\n", m->name(), m->canRun() ? "":"(disabled)");
          m = m->next();
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

class SwitchCommand : public Command {
  public:
    const char* getName() { return "switch"; }
    const char* getHelp() { return ("set autoswitch begin delay and switch interval in seconds (0 to disable)"); }
    void execute(Console* c, uint8_t paramCount, char** params) {
      uint32_t b = 0;
      if (paramCount >= 1) {
        b = atoi(params[1]);
        if (b) {
          RazzleMode::defaultMatrix()->autoSwitchBegin(b*1000);
        }
        RazzleMode::defaultMatrix()->autoSwitchEnable(b != 0);
      }
      if (paramCount >= 2) {
        b = atoi(params[2]);
        RazzleMode::defaultMatrix()->autoSwitchInterval(b*1000);
      }
      c->printf("autoswitch begin: %d, interval: %d seconds\n",
          (int)RazzleMode::defaultMatrix()->autoSwitchBegin()/1000,
          (int)RazzleMode::defaultMatrix()->autoSwitchInterval()/1000);
    }
};
SwitchCommand theSwitchCommand;
