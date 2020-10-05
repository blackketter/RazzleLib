#include "RazzleMode.h"

RazzleMatrix* RazzleMode::_m = nullptr;

RazzleMode::RazzleMode() {
  _next = _first;
  _first = this;
}

RazzleMode* RazzleMode::named(const char* find) {
  RazzleMode* r = first();
  while (r) {
    if (strcasecmp(r->name(), find) == 0) {
      break;
    }
    r = r->next();
  }
  return r;
}

RazzleMode* RazzleMode::_first = nullptr;
