#pragma once

#include <Adafruit_GFX.h>      // Core graphics library
#include <SPI.h>
#include <Wire.h>              // this is needed even tho we aren't using it
#include <Adafruit_ILI9341.h>  // Hardware-specific library
#include "Adafruit_STMPE610.h" // Touch library
#include "rmtSendClass.h"      // RMT Class
#include "necRmtSendClass.h"   // NEC Format IR Remote Controller
#include "panasonicRmtSendClass.h"  // AEHA Format(Panasonic) IR Remote Controller

/* figure of the buttons */
typedef enum {
  rectangle, filledRectangle, text,
  upArrow, downArrow, leftArrow, rightArrow,
  upCaret, downCaret, leftCaret, rightCaret,
  circle, filledCircle, bitmap, power, none,
} tftRmtFigure_t;

/* remote controller type */
typedef enum {
  nec,
  panasonic,
  noRmt,
} tftRmtType_t;

static const int maxTextLength = 12;
/* button information */
typedef struct {
  uint16_t x, y, w, h;
  int16_t xMag, yMag;
  uint16_t figureType;
  uint16_t figureColor;
  uint16_t outlineColor;
  char text[maxTextLength];
  int size;
  uint16_t textColor;
  tftRmtType_t rmtType;
  uint16_t customCode;
  uint8_t numDataCode;
  uint8_t dataCode[3];
  void (*function)(void);
} button_t;

class tftRmtClass {
  public:

    tftRmtClass(uint8_t tftCsPin, uint8_t tftDcPin, uint8_t stmpeCsPin, uint8_t irPin, uint8_t channel, uint16_t bgColor);
    tftRmtClass(Adafruit_ILI9341 *tft, Adafruit_STMPE610 *ts, uint8_t irPin, uint8_t channel, uint16_t bgColor);

    void setBgColor(uint16_t bgColor);
    void clearScreen();
    void setFont(const GFXfont *font);

    int addButtons(button_t *buttons, uint8_t numButtons);
    int addButton(uint16_t x, uint16_t y, uint16_t w, int16_t h, int16_t xMag, int16_t yMag, tftRmtFigure_t figureType, uint16_t figureColor, uint16_t outlineColor, const char *text, int size, uint16_t textColor,
                  void (*function)(void), tftRmtType_t rmtType, uint16_t customCode, uint8_t numDataCode, ...);
    void deleteAllButtons();
    void displayAllButtons();
    void checkButtons();
    void setScreenSaver(void (*screenSaver)(void), long timeout);

  private:
    Adafruit_ILI9341 *tft;  /* TFT */
    Adafruit_STMPE610 *ts;  /* Touch Shield */
    necRmtSendClass *necRmt;  /* NEC Format Remote Controller */
    panasonicRmtSendClass *panasonicRmt; /* AEHA(Panasonic) Format Remote Controller */
    static int screenSaverEntered;

    uint16_t bgColor;
    uint8_t numButtons;
    button_t *buttons;
    GFXfont *font;
    uint16_t fontHeight;

    static void IRAM_ATTR onTimer();
    void (*screenSaver)(void);
    long timeout;
    hw_timer_t *timer;

    void init(Adafruit_ILI9341 *tft, Adafruit_STMPE610 *ts, uint8_t irPin, uint8_t channel, uint16_t bgColor);
    int pointsAreClose(TS_Point *point1, TS_Point *point2);
    int getButtonIndexNearPoint(TS_Point *point);
    void sendCodeOrCallFunction(TS_Point *point);
};
