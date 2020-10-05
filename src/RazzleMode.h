#ifndef _RazzleMode_
#define _RazzleMode_

#include "RazzleMatrix.h"

class RazzleMode {
  public:
    RazzleMode();

    virtual void draw(RazzleMatrix* frame) = 0;
    virtual const char* name() = 0;

    virtual void begin() {}
    virtual void idle() {}
    virtual void end() {}

    virtual bool wantsToRun() { return false; }
    virtual bool canRun() { return true; }

    virtual bool dither() { return true; } // frames should be dithered
    virtual bool interpolate() { return true; }  // frames should be interpolated
    virtual framerate_t fps() { return 0; } // as fast as possible

    RazzleMode* next() { return _next; };
    void setNext(RazzleMode* next) { _next = next; }
    static RazzleMode* first() { return _first; }
    static RazzleMode* named(const char* find);
    static void defaultMatrix(RazzleMatrix* m) { _m = m; }
  private:
    RazzleMode* _next = nullptr;
    static RazzleMode* _first;
  protected:
    static RazzleMatrix* _m;
};

#endif
