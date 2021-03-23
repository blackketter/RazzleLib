#include "RazzleMatrix.h"
#include "RazzleCommands.h"
#include "Clock.h"
#include "TimeZones.h"

extern Console console;

#include "Commands/FPSCommand.h"
FPSCommand theFPSCommand;

///////////////////////////////////////////////////////////////////////////////
// setupLeds
///////////////////////////////////////////////////////////////////////////////
RazzleMatrix* setupLeds(const RazzleMatrixConfig* info) {
  RazzleMatrix* matrix;
  led_t num_leds = info->width*info->height;
  uint32_t milliAmpsMax =  info->powerSupplyMilliAmps;
  EOrder order = info->colorOrder;


  CRGB* leds = new CRGB[num_leds];
  CRGB* frameled0 = new CRGB[num_leds];
  CRGB* frameled1 = new CRGB[num_leds];
  matrix = new RazzleMatrix(leds, info->width, info->height, info->matrixType);
  matrix->frames[0] = new RazzleMatrix(frameled0, info->width, info->height, info->matrixType);
  matrix->frames[1] = new RazzleMatrix(frameled1, info->width, info->height, info->matrixType);

  matrix->enableGamma(true);
  if (!leds || !frameled0 || !frameled1 || !matrix->frames[0] || !matrix->frames[1]) {
    //console.debugln("Error allocating LED buffers");
    return nullptr;
  }
  fill_solid(leds, num_leds, CRGB::Black);
  matrix->frames[0]->fillScreen(LED_BLACK);
  matrix->frames[1]->fillScreen(LED_BLACK);

  led_t offset = 0;
  led_t c;
  int i = 0;

  switch (order) {
    case RGB:
      // fucking templates mean that this needs to be hardcoded
      c = info->segment[i++];
      if (c) {
        FastLED.addLeds<CHIPSET, LED_DATA_PIN0, RGB>(leds, offset, c).setCorrection( RazzleMatrix::defaultCorrection );
        offset += c;
        c = info->segment[i++];
        if (c) {
          FastLED.addLeds<CHIPSET, LED_DATA_PIN1, RGB>(leds, offset, c).setCorrection( RazzleMatrix::defaultCorrection );
          offset += c;
          c = info->segment[i++];
          if (c) {
            FastLED.addLeds<CHIPSET, LED_DATA_PIN2, RGB>(leds, offset, c).setCorrection( RazzleMatrix::defaultCorrection );
            offset += c;
            c = info->segment[i++];
            if (c) {
              FastLED.addLeds<CHIPSET, LED_DATA_PIN3, RGB>(leds, offset, c).setCorrection( RazzleMatrix::defaultCorrection );
              offset += c;
              c = info->segment[i++];
              if (c) {
                FastLED.addLeds<CHIPSET, LED_DATA_PIN4, RGB>(leds, offset, c).setCorrection( RazzleMatrix::defaultCorrection );
                offset += c;
                c = info->segment[i++];
                if (c) {
                  FastLED.addLeds<CHIPSET, LED_DATA_PIN5, RGB>(leds, offset, c).setCorrection( RazzleMatrix::defaultCorrection );
                  offset += c;
                  c = info->segment[i++];
                  if (c) {
                    c = info->segment[i++];
                    FastLED.addLeds<CHIPSET, LED_DATA_PIN6, RGB>(leds, offset, c).setCorrection( RazzleMatrix::defaultCorrection );
                    offset += c;
                    if (c) {
                      FastLED.addLeds<CHIPSET, LED_DATA_PIN7, RGB>(leds, offset, c).setCorrection( RazzleMatrix::defaultCorrection );
                    }
                  }
                }
              }
            }
          }
        }
      }
      break;
    case GRB:
      // fucking templates mean that this needs to be hardcoded
      c = info->segment[i++];
      if (c) {
        FastLED.addLeds<CHIPSET, LED_DATA_PIN0, GRB>(leds, offset, c).setCorrection( RazzleMatrix::defaultCorrection );
        offset += c;
        c = info->segment[i++];
        if (c) {
          FastLED.addLeds<CHIPSET, LED_DATA_PIN1, GRB>(leds, offset, c).setCorrection( RazzleMatrix::defaultCorrection );
          offset += c;
          c = info->segment[i++];
          if (c) {
            FastLED.addLeds<CHIPSET, LED_DATA_PIN2, GRB>(leds, offset, c).setCorrection( RazzleMatrix::defaultCorrection );
            offset += c;
            c = info->segment[i++];
            if (c) {
              FastLED.addLeds<CHIPSET, LED_DATA_PIN3, GRB>(leds, offset, c).setCorrection( RazzleMatrix::defaultCorrection );
              offset += c;
              c = info->segment[i++];
              if (c) {
                FastLED.addLeds<CHIPSET, LED_DATA_PIN4, GRB>(leds, offset, c).setCorrection( RazzleMatrix::defaultCorrection );
                offset += c;
                c = info->segment[i++];
                if (c) {
                  FastLED.addLeds<CHIPSET, LED_DATA_PIN5, GRB>(leds, offset, c).setCorrection( RazzleMatrix::defaultCorrection );
                  offset += c;
                  c = info->segment[i++];
                  if (c) {
                    FastLED.addLeds<CHIPSET, LED_DATA_PIN6, GRB>(leds, offset, c).setCorrection( RazzleMatrix::defaultCorrection );
                    offset += c;
                    c = info->segment[i++];
                    if (c) {
                      FastLED.addLeds<CHIPSET, LED_DATA_PIN7, GRB>(leds, offset, c).setCorrection( RazzleMatrix::defaultCorrection );
                    }
                  }
                }
              }
            }
          }
        }
      }
      break;
    default:
      break;
      //console.debugln("ERROR: Bad color order");
  }

  FastLED.setMaxPowerInVoltsAndMilliamps  ( 5, milliAmpsMax);

  FastLED.setCorrection(RazzleMatrix::defaultCorrection);
  FastLED.setTemperature(RazzleMatrix::defaultTemperature);
  FastLED.show(matrix->getBrightness());

  RazzleMode::defaultMatrix(matrix);

  return matrix;
}

///////////////////////////////////////////////////////////////////////////////
// Brightness
///////////////////////////////////////////////////////////////////////////////

void RazzleMatrix::setBrightness(uint8_t day, uint8_t night) { dayBrightness = day; nightBrightness = night; }

uint8_t RazzleMatrix::getBrightness() { return isDay() ? dayBrightness : nightBrightness; }
uint8_t RazzleMatrix::getNightBrightness() { return nightBrightness; }
uint8_t RazzleMatrix::getDayBrightness() { return dayBrightness; }

bool RazzleMatrix::isDay() {
  Clock theClock(&usPT);
  uint8_t hour = theClock.hour();
  return theClock.hasBeenSet() && (hour >= 8) && (hour < 17);  // daytime is 8 to 5.  if the clock hasn't been set, it's night for safety
}

///////////////////////////////////////////////////////////////////////////////
// Rendering
///////////////////////////////////////////////////////////////////////////////

void RazzleMatrix::idle() {

  nowMillis = Uptime::millis();
  if ( autoSwitchEnabled() && autoSwitchInterval() &&
        (nowMillis > _nextAutoSwitch) ) {
      setRandomScreensaverMode();
      _nextAutoSwitch = nowMillis + autoSwitchInterval();
      //console.debugf("Autoswitched to mode %s\n", getLEDMode());
  }

  if (nowMillis >= nextFrameMillis) {
    uint8_t temp = lastFrame;
    lastFrame = nextFrame;
    nextFrame = temp;
    lastFrameMillis = nextFrameMillis;
    nextFrameMillis = nowMillis + frameIntervalMillis;
    frames[lastFrame]->copy(frames[nextFrame]);
    render(frames[nextFrame]);
  }

  interpolateFrame();
  FastLED.show(getBrightness());
}

void RazzleMatrix::interpolateFrame() {
  uint8_t fract8;
  CRGB* leds = pixels();
  led_t num_leds = numPixels();
  if (nextFrameMillis == lastFrameMillis) {
    fract8 = 0;
  } else {
    fract8 = ((nowMillis - lastFrameMillis) * 256) / (nextFrameMillis - lastFrameMillis);
  }

  if (fract8 == 0 || (currMode && !currMode->interpolate())) {
    frames[lastFrame]->copy(this);
  } else {
    for (led_t i = 0; i < num_leds; i++) {
      leds[i].r = lerp8by8( frames[lastFrame]->getLeds()[i].r, frames[nextFrame]->getLeds()[i].r, fract8 );
      leds[i].g = lerp8by8( frames[lastFrame]->getLeds()[i].g, frames[nextFrame]->getLeds()[i].g, fract8 );
      leds[i].b = lerp8by8( frames[lastFrame]->getLeds()[i].b, frames[nextFrame]->getLeds()[i].b, fract8 );
    }
  }
}

void RazzleMatrix::render(RazzleMatrix* frame) {
  if (currMode) {
    fps(currMode->fps());
    theFPSCommand.newFrame();
    currMode->draw(frame);
  } else {
    //console.debugln("No currMode!");
  }
}

///////////////////////////////////////////////////////////////////////////////
// Mode management
///////////////////////////////////////////////////////////////////////////////
const char* RazzleMatrix::getLEDMode() {
  return currMode->name();
}

bool RazzleMatrix::setLEDMode(const char* newMode) {
  return setLEDMode(RazzleMode::named(newMode));
}

bool RazzleMatrix::setLEDMode(RazzleMode* newMode) {
  if (newMode == nullptr) return false;
  if (!newMode->canRun()) return false;
  if (currMode == newMode) return true;

  if (currMode) { currMode->end(); }
  currMode = newMode;

 // 120 led long string is about 100fps, dithering at about 50fps
//  console.debugln("setDither");
//  if (maxSegmentLen() > 120) {
    FastLED.setDither( 0 );
//  } else {
//    FastLED.setDither(currMode->dither());
//  }
  currMode->begin();
  lastFrame = 0;
  lastFrameMillis = nowMillis;

  frames[lastFrame]->fillScreen(LED_BLACK);
  render(frames[lastFrame]);

  nextFrame = 1;
  nextFrameMillis = nowMillis + frameIntervalMillis;
  frames[nextFrame]->fillScreen(LED_BLACK);
  render(frames[nextFrame]);

  return true;
}

bool RazzleMatrix::isLEDMode(const char* isMode) {
  return strcasecmp(getLEDMode(), isMode) == 0;
}

void RazzleMatrix::setRandomScreensaverMode() {
  RazzleMode* m = RazzleMode::first();

  // see if anybody wants to run.  first wins
  while (m) {
    if (m->wantsToRun() && m->canRun() && m->isScreensaver()) {
      console.debugf("%s wants to run\n",m->name());
      break;
    }
    m = m->next();
  }
  if (!m) {
    // count the modes
    m = RazzleMode::first();
    int count = 0;
    while (m) {
      if (m->canRun() && m->isScreensaver()) {
        count++;
      }
      m = m->next();
    }

    // choose a random one
    m = RazzleMode::first();
    count = random(count);
    while (m) {
      if (m->canRun() && m->isScreensaver()) {
        count--;
      }
      if (count == 0) { break; }
      m = m->next();
    }
  }

  if (m) {
    console.debugf("%s runs randomly\n",m->name());
    setLEDMode(m);
  }
}

