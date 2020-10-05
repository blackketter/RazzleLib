#ifndef _CLOCKMODE_
#define _CLOCKMODE_
#include "RazzleMode.h"
#include "Timezones.h"

class ClockMode : public RazzleMode {
  public:
    virtual bool wantsToRun() { return theClock.hour() > 22 || theClock.hour() < 7; }
    ClockMode() { theClock.setZone(&usPT); }
  protected:
    Clock theClock;

};

#endif
