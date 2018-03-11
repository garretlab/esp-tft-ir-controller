#include "tftRmtClass.h"

static const int longInterval = 500;
static const int measurementInterval = 35;
static const int pointsClose = 100;

static const int tsMinX = 150;
static const int tsMinY = 130;
static const int tsMaxX = 3600;
static const int tsMaxY = 3600;

/* constructor: not tested. */
tftRmtClass::tftRmtClass(uint8_t tftCsPin, uint8_t tftDcPin, uint8_t stmpeCsPin, uint8_t irPin, uint8_t channel, uint16_t bgColor) {
  tft = new Adafruit_ILI9341(tftCsPin, tftDcPin);
  ts = new Adafruit_STMPE610(stmpeCsPin);

  init(tft, ts, irPin, channel, bgColor);
}

/* constructor */
tftRmtClass::tftRmtClass(Adafruit_ILI9341 *tft, Adafruit_STMPE610 *ts, uint8_t irPin, uint8_t channel, uint16_t bgColor) {
  this->tft = tft;
  this->ts = ts;

  init(tft, ts, irPin, channel, bgColor);
}

/* set background color */
void tftRmtClass::setBgColor(uint16_t bgColor) {
  this->bgColor = bgColor;
}

/* clear screen: write background color to the screen */
void tftRmtClass::clearScreen() {
  tft->fillScreen(bgColor);
}

/* set font */
void tftRmtClass::setFont(const GFXfont *font) {
  this->font = const_cast<GFXfont *>(font);
  tft->setFont(font);
  fontHeight = font->yAdvance;
}

/* collectively add buttons: not tested */
int tftRmtClass::addButtons(button_t *buttons, uint8_t numButtons) {
  this->buttons = buttons;
  this->numButtons = numButtons;

  return numButtons;
}

/* add button */
int tftRmtClass::addButton(uint16_t x, uint16_t y, uint16_t w, int16_t h, int16_t xMag, int16_t yMag, tftRmtFigure_t figureType, uint16_t figureColor, uint16_t outlineColor, const char *text, int size, uint16_t textColor,
                           void (*function)(void), tftRmtType_t rmtType, uint16_t customCode, uint8_t numDataCode, ...) {
  va_list ap;

  if ((buttons = (button_t *)realloc(buttons, sizeof(button_t) * (numButtons + 1)))) {
    buttons[numButtons].x = x;
    buttons[numButtons].y = y;
    buttons[numButtons].w = w;
    buttons[numButtons].h = h;
    buttons[numButtons].xMag = xMag;
    buttons[numButtons].yMag = yMag;
    buttons[numButtons].figureType = figureType;
    buttons[numButtons].size = size;
    buttons[numButtons].textColor = textColor;
    buttons[numButtons].figureColor = figureColor;
    buttons[numButtons].outlineColor = outlineColor;
    if (text) {
      strncpy(buttons[numButtons].text, text, maxTextLength - 1);
    } else {
      buttons[numButtons].text[0] = 0;
    }
    buttons[numButtons].rmtType = rmtType;
    buttons[numButtons].customCode = customCode;
    buttons[numButtons].numDataCode = numDataCode;
    buttons[numButtons].function = function;

    va_start(ap, numDataCode);
    for (int i = 0; i < numDataCode; i++) {
      buttons[numButtons].dataCode[i] = va_arg(ap, int);
    }
    va_end(ap);
    numButtons++;
  } else {
    return 0;
  }
  return numButtons;
}

/* Delete all registered buttons */
void tftRmtClass::deleteAllButtons() {
  free(buttons);
  buttons = NULL;
  numButtons = 0;
}

/* Display all buttons on the screen */
void tftRmtClass::displayAllButtons() {
  int r, rx, dx, ry, dy;

  for (int i = 0; i < numButtons; i++) {
    switch (buttons[i].figureType) {
      case rectangle:
      case filledRectangle:
        rx = buttons[i].x + buttons[i].w / 2 - (buttons[i].w / 2) * buttons[i].xMag / 100 ;
        dx = buttons[i].w * buttons[i].xMag / 100;
        ry = buttons[i].y + buttons[i].h / 2 - (buttons[i].h / 2) * buttons[i].yMag / 100;
        dy = buttons[i].h * buttons[i].yMag / 100;
        tft->fillRect(rx, ry, dx, dy, buttons[i].figureColor);
        if (buttons[i].figureType == rectangle) {
          tft->fillRect(rx + buttons[i].size, ry + buttons[i].size, dx - 2 * buttons[i].size, dy - 2 * buttons[i].size, bgColor);
        }
        break;
      case power:
        if (buttons[i].w > buttons[i].h) {
          r = buttons[i].h * 35 / 100;
        } else {
          r = buttons[i].w * 35 / 100;
        }
        rx = buttons[i].x + buttons[i].w * 50 / 100;
        ry = buttons[i].y + buttons[i].h * 50 / 100 + r * 10 / 100;
        tft->fillCircle(rx, ry, r, buttons[i].figureColor);
        tft->fillCircle(rx, ry, r * 3 / 4, bgColor);

        dx = r * 25 / 100;
        ry = buttons[i].y + r * 25 / 100;
        dy = r * 130 / 100;
        tft->fillRect(rx - dx, ry, 2 * dx, dy, bgColor);

        dx = r * 18 / 100;
        tft->fillRect(rx - dx, ry, 2 * dx, dy, buttons[i].figureColor);
        break;
      case upArrow:
      case upCaret:
        rx = buttons[i].x + buttons[i].w * 50 / 100;
        dx = buttons[i].w / 2 * buttons[i].xMag / 100;
        ry = buttons[i].y + buttons[i].h / 2 * (100 - buttons[i].yMag) / 100;
        dy = buttons[i].h * buttons[i].yMag / 100;
        tft->fillTriangle(rx, ry, rx - dx, ry + dy, rx + dx, ry + dy, buttons[i].figureColor);
        tft->fillTriangle(rx, ry, rx - dx, ry + dy, rx + dx, ry + dy, buttons[i].figureColor);
        if (buttons[i].figureType == upCaret) {
          tft->fillTriangle(rx, ry + buttons[i].size, rx - dx, ry + dy + buttons[i].size, rx + dx, ry + dy + buttons[i].size, bgColor);
        }
        break;
      case downArrow:
      case downCaret:
        rx = buttons[i].x + buttons[i].w * 50 / 100;
        dx = buttons[i].w / 2 * buttons[i].xMag / 100;
        ry = buttons[i].y + buttons[i].h * (100 - buttons[i].xMag) / 100;
        dy = buttons[i].h * buttons[i].yMag / 100;
        tft->fillTriangle(rx, ry + dy, rx - dx, ry, rx + dx, ry, buttons[i].figureColor);
        tft->fillTriangle(rx, ry + dy, rx - dx, ry, rx + dx, ry, buttons[i].figureColor);
        if (buttons[i].figureType == downCaret) {
          tft->fillTriangle(rx, ry + dy - buttons[i].size, rx - dx, ry - buttons[i].size, rx + dx, ry - buttons[i].size, bgColor);
        }
        break;
      case leftArrow:
      case leftCaret:
        rx = buttons[i].x + buttons[i].w / 2 * (100 - buttons[i].xMag) / 100;
        dx = buttons[i].w * buttons[i].xMag / 100;
        ry = buttons[i].y + buttons[i].h * 50 / 100;
        dy = buttons[i].h / 2 * buttons[i].yMag / 100;
        tft->fillTriangle(rx, ry, rx + dx, ry - dy, rx + dx, ry + dy, buttons[i].figureColor);
        tft->fillTriangle(rx, ry, rx + dx, ry - dy, rx + dx, ry + dy, buttons[i].figureColor);
        if (buttons[i].figureType == leftCaret) {
          tft->fillTriangle(rx + buttons[i].size, ry, rx + dx + buttons[i].size, ry - dy, rx + dx + buttons[i].size, ry + dy, bgColor);
        }
        break;
      case rightArrow:
      case rightCaret:
        rx = buttons[i].x + buttons[i].w / 2 * (100 - buttons[i].xMag) / 100;
        dx = buttons[i].w * buttons[i].xMag / 100;
        ry = buttons[i].y + buttons[i].h * 50 / 100;
        dy = buttons[i].h / 2 * buttons[i].yMag / 100;
        tft->fillTriangle(rx + dx, ry, rx, ry - dy, rx, ry + dy, buttons[i].figureColor);
        tft->fillTriangle(rx + dx, ry, rx, ry - dy, rx, ry + dy, buttons[i].figureColor);
        if (buttons[i].figureType == rightCaret) {
          tft->fillTriangle(rx + dx - buttons[i].size, ry, rx - buttons[i].size, ry - dy, rx - buttons[i].size, ry + dy, bgColor);
        }
        break;
      case filledCircle:
        if (buttons[i].w > buttons[i].h) {
          buttons[i].h = buttons[i].w;
        } else {
          buttons[i].w = buttons[i].h;
        }
        tft->fillCircle(buttons[i].x + buttons[i].w / 2, buttons[i].y + buttons[i].h / 2, buttons[i].w / 2 * buttons[i].xMag / 100, buttons[i].figureColor);
        tft->fillCircle(buttons[i].x + buttons[i].w / 2, buttons[i].y + buttons[i].h / 2, buttons[i].w / 2 * buttons[i].xMag / 100, buttons[i].figureColor);
        break;
      default:
        break;
    }

    if (buttons[i].outlineColor != bgColor) {
      tft->drawRect(buttons[i].x, buttons[i].y, buttons[i].w, buttons[i].h, buttons[i].outlineColor);
    }
  }

  for (int i = 0; i < numButtons; i++) {
    if (buttons[i].text[0]) {
      int16_t x, y, x1, y1;
      uint16_t w, h;

      if (fontHeight) {
        y = buttons[i].y + (buttons[i].h + (fontHeight - 8) ) / 2;
      } else {
        y = buttons[i].y + (buttons[i].h - buttons[i].size * 8) / 2;
      }
      tft->setFont(font);
      tft->setTextSize(buttons[i].size);
      tft->setCursor(buttons[i].x, y);
      tft->getTextBounds(buttons[i].text, buttons[i].x, y, &x1, &y1, &w, &h);
      x = buttons[i].x + (buttons[i].w - w) / 2.5;
      tft->setTextColor(buttons[i].textColor, bgColor);
      tft->fillRect(x, y1, w, h, buttons[i].figureColor);
      tft->setCursor(x, y);
      tft->print(buttons[i].text);
    }
  }
}

/* Check if a button was pressed */
void tftRmtClass::checkButtons() {
  static TS_Point pFirst, pCurrent;
  static long tFirst = 0;
  static long tPrevious, tCurrent;
  static int first = 1;
  static int longCount = longInterval;

  if (screenSaverEntered) {
    screenSaver();
  }

  tCurrent = millis();
  if (! ts->bufferEmpty()) { /* data exists in the buffer */
    if (timer) { /* reset timer */
      timerWrite(timer, 0);
    }

    if (screenSaverEntered) {
      screenSaverEntered = 0;
      Serial.printf("Screensaver end\n");
      clearScreen();
      displayAllButtons();
      return;
    }

    pCurrent = ts->getPoint();
    if (first) { /* new */
      pFirst = pCurrent;
      tFirst = tPrevious = millis();
      first = 0;
      sendCodeOrCallFunction(&pCurrent);
    } else { /* continue */
      if ((tCurrent - tFirst) > longCount) { /* long enough */
        if (pointsAreClose(&pCurrent, &pFirst)) { /* close to previous point */
          longCount += longInterval;
        }
      }
      tPrevious = tCurrent;
    }
  } else {
    if (first == 0) { /* released */
      if ((tCurrent - tPrevious) > measurementInterval) { /* it takes some time */
        first = 1;
        longCount = longInterval;
      }
    }
  }
}

void tftRmtClass::setScreenSaver(void (*screenSaver)(void), long timeout) {
  screenSaverEntered = 0;
  this->screenSaver = screenSaver;
  this->timeout = timeout;

  timer = timerBegin(0, 8000, true);
  timerAttachInterrupt(timer, &tftRmtClass::onTimer, true);
  timerAlarmWrite(timer, timeout, true);
  timerAlarmEnable(timer);
}

int tftRmtClass::screenSaverEntered;

/* private */

void IRAM_ATTR tftRmtClass::onTimer() {
  screenSaverEntered = 1;
}

/* initialize */
void tftRmtClass::init(Adafruit_ILI9341 * tft, Adafruit_STMPE610 * ts, uint8_t irPin, uint8_t channel, uint16_t bgColor) {
  necRmt = new necRmtSendClass(irPin, channel);
  panasonicRmt = new panasonicRmtSendClass(irPin, channel);

  screenSaverEntered = 0;
  this->bgColor = bgColor;
  fontHeight = 0;
  numButtons = 0;
  buttons = NULL;
  timeout = 0;

  ts->begin();
  tft->begin();
  tft->fillScreen(this->bgColor);
}

/* Check if the two points are close */
int tftRmtClass::pointsAreClose(TS_Point *point1, TS_Point *point2) {
  if ((abs(point1->x - point2->x) < pointsClose) && ((abs(point1->y - point2->y)) < pointsClose)) {
    return 1;
  } else {
    return 0;
  }
}

/* Check if a button exists near the touched point */
int tftRmtClass::getButtonIndexNearPoint(TS_Point * point) {
  int x = map(point->x, tsMinX, tsMaxX, 0, tft->width());
  int y = map(point->y, tsMinY, tsMaxY, 0, tft->height());

  for (int i = 0; i < numButtons; i++) {
    if ((buttons[i].rmtType != noRmt) || buttons[i].function) {
      if ((x > buttons[i].x) && (x < buttons[i].x + buttons[i].w) &&
          (y > buttons[i].y) && (y < buttons[i].y + buttons[i].h)) {
        return i;
      }
    }
  }

  return -1;
}

void tftRmtClass::sendCodeOrCallFunction(TS_Point *point) {
  int index;
  if ((index = getButtonIndexNearPoint(point)) != -1) {
    switch (buttons[index].rmtType) {
      case nec:
        necRmt->sendData(buttons[index].customCode, buttons[index].dataCode[0]);
        break;
      case panasonic:
        panasonicRmt->sendData(buttons[index].customCode, buttons[index].dataCode);
        break;
      default:
        break;
    }
    
    if (buttons[index].function) {
      buttons[index].function();
    }
  }
}
