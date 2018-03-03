#include "tftRmtClass.h"
#include "Fonts/FreeSans12pt7b.h"
#include <WiFi.h>

const int stmpeCs = 25;  // to pin 8 of shield
const int tftDc = 33;    // to pin 9
const int tftCS = 32;    // to pin 10

#if 0 /* not used in the sketch */
const int sdCs = 26;     // to pin 4
const int mosiPin = 23;  // to pin 11
const int misoPin = 19;  // to pin 12
const int sckPin = 18;   // to pin 13
#endif

const int ledPin = 27;

#if 0 /* not used */
const int irReceiverPin = 22;
#endif

Adafruit_ILI9341 tft = Adafruit_ILI9341(tftCS, tftDc);    // TFT
Adafruit_STMPE610 ts = Adafruit_STMPE610(stmpeCs);        // Touch

tftRmtClass buttons(&tft, &ts, ledPin, 0, ILI9341_WHITE);

void setTvControllerCommon1() {
  /* 1st row */
  buttons.addButton(0, 28, 96, 48, 100, 100, rectangle, 0xffff, 0xffff, "EPG", 1, 0x0000, NULL, nec, 0x40bf, 1, 0x6e); // EPG
  buttons.addButton(96, 28, 48, 48, 60, 30, upCaret, 0x0000, 0xffff, NULL, 3, 0x0000, NULL, nec, 0x40bf, 1, 0x3e); // up
  buttons.addButton(192, 28, 48, 48, 100, 100, power, 0x0000, 0xffff, NULL, 0, 0x0000, NULL, nec, 0x40bf, 1, 0x12); // power

  /* 2nd row */
  buttons.addButton(12, 76, 12, 48, 100, 60, leftCaret, 0x0000, 0xffff, NULL, 3, 0x0000, NULL, nec, 0x40be, 1, 0x22); // double left
  buttons.addButton(24, 76, 12, 48, 100, 60, leftCaret, 0x0000, 0xffff, NULL, 3, 0x0000, NULL, nec, 0x40be, 1, 0x22); // double left
  buttons.addButton(48, 76, 48, 48, 30, 60, leftCaret, 0x0000, 0xffff, NULL, 3, 0x0000, NULL, nec, 0x40bf, 1, 0x5f); // single left
  buttons.addButton(96, 76, 48, 48, 40, 40, rectangle, 0x0000, 0xffff, NULL, 2, 0x0000, NULL, nec, 0x40bf, 1, 0x3d); // ok
  buttons.addButton(144, 76, 48, 48, 30, 60, rightCaret, 0x0000, 0xffff, NULL, 3, 0x0000, NULL, nec, 0x40bf, 1, 0x5b); // single right
  buttons.addButton(218, 76, 12, 48, 100, 60, rightCaret, 0x0000, 0xffff, NULL, 3, 0x0000, NULL, nec, 0x40be, 1, 0x23); // double right
  buttons.addButton(206, 76, 12, 48, 100, 60, rightCaret, 0x0000, 0xffff, NULL, 3, 0x0000, NULL, nec, 0x40be, 1, 0x23); // double right

  /* 3rd row */
  buttons.addButton(0, 124, 96, 48, 100, 100, rectangle, 0xffff, 0xffff, "Back", 1, 0x0000, NULL, nec, 0x40bf, 1, 0x3b); // back
  buttons.addButton(96, 124, 48, 48, 60, 30, downCaret, 0x0000, 0xffff, NULL, 3, 0x0000, NULL, nec, 0x40bf, 1, 0x3f); // down
  buttons.addButton(144, 124, 96, 48, 100, 100, rectangle, 0xffff, 0xffff, "Menu", 1, 0x0000, NULL, nec, 0x40be, 1, 0x34); // menu

  /* 4th row */
  buttons.addButton(132, 172, 48, 48, 100, 100, rectangle, 0xffff, 0xffff, "-", 2, 0x0000, NULL, nec, 0x40bf, 1, 0x1e); // volume down
  buttons.addButton(196, 172, 48, 48, 100, 100, rectangle, 0xffff, 0xffff, "+", 2, 0x0000, NULL, nec, 0x40bf, 1, 0x1a); // volume up
}

void setTvControllerCommon2 () {
  buttons.addButton(0, 32, 240, 1, 100, 100, filledRectangle, 0x0000, 0x0000, NULL, 1, 0x0000, NULL, noRmt, 0, 0); // line
  buttons.addButton(164, 172, 48, 48, 100, 100, text, 0xffff, 0xffff, "Vol", 1, 0x0000, NULL, noRmt, 0, 0); // Vol
}

void setTvController1 () {
  buttons.deleteAllButtons();
  buttons.setBgColor(0xffff);

  setTvControllerCommon1();

  /* 4th row */
  buttons.addButton(0, 172, 48, 48, 60, 30, downArrow, 0x0000, 0xffff, NULL, 0, 0x0000, NULL, nec, 0x40bf, 1, 0x1f); // channel down
  buttons.addButton(72, 172, 48, 48, 60, 30, upArrow, 0x0000, 0xffff, NULL, 0, 0x0000, NULL, nec, 0x40bf, 1, 0x1b); // channel up

  /* 5th row */
  buttons.addButton(0, 220, 48, 48, 40, 40, filledRectangle, 0x001f, 0xffff, NULL, 0, 0x0000, NULL, nec, 0x40bf, 1, 0x73); // blue
  buttons.addButton(36, 220, 48, 48, 40, 40, filledRectangle, 0xf800, 0xffff, NULL, 0, 0x0000, NULL, nec, 0x40bf, 1, 0x74); // red
  buttons.addButton(72, 220, 48, 48, 40, 40, filledRectangle, 0x03e0, 0xffff, NULL, 0, 0x0000, NULL, nec, 0x40bf, 1, 0x75); // green
  buttons.addButton(108, 220, 48, 48, 40, 40, filledRectangle, 0xffe0, 0xffff, NULL, 0, 0x0000, NULL, nec, 0x40bf, 1, 0x76); // yellow
  buttons.addButton(144, 220, 96, 48, 100, 100, rectangle, 0xffff, 0xffff, "Data", 1, 0x0000, NULL, nec, 0x43bc, 1, 0x14); // data

  /* 6th row */
  buttons.addButton(0, 268, 48, 48, 50, 50, leftArrow, 0x0000, 0xffff, NULL, 0, 0x0000, setCatvController, noRmt, 0, 0);
  buttons.addButton(192, 268, 48, 48, 50, 50, rightArrow, 0x0000, 0xffff, NULL, 0, 0x0000, setTvController2, noRmt, 0, 0);

  buttons.addButton(111, 11, 10, 10, 100, 100, text, 0xffff, 0xffff, "TV", 1, 0x0000, NULL, noRmt, 0, 0);
  buttons.addButton(37, 172, 48, 48, 100, 100, text, 0xffff, 0xffff, "Ch", 1, 0x0000, NULL, noRmt, 0, 0);
  setTvControllerCommon2();

  buttons.clearScreen();
  buttons.displayAllButtons();
}

void setTvController2 () {
  buttons.deleteAllButtons();
  buttons.setBgColor(0xffff);

  setTvControllerCommon1();

  /* 4th row */
  buttons.addButton(0, 172, 96, 48, 100, 100, rectangle, 0xffff, 0xffff, "Video", 1, 0x0000, NULL, nec, 0x40be, 1, 0x28); // video
  buttons.addButton(96, 172, 48, 48, 40, 40, filledRectangle, 0x0000, 0xffff, NULL, 0, 0x0000, NULL, nec, 0x40be, 1, 0x2b); // stop

  /* 5th row */
  buttons.addButton(12, 220, 2, 48, 100, 60, filledRectangle, 0x0000, 0xffff, NULL, 0, 0x0000, NULL, nec, 0x40be, 1, 0x27); // skip back
  buttons.addButton(24, 220, 12, 48, 100, 60, leftArrow, 0x0000, 0xffff, NULL, 0, 0x0000, NULL, nec, 0x40be, 1, 0x27); // skip back
  buttons.addButton(12, 220, 12, 48, 100, 60, leftArrow, 0x0000, 0xffff, NULL, 0, 0x0000, NULL, nec, 0x40be, 1, 0x27); // skip back
  buttons.addButton(72, 220, 12, 48, 100, 60, leftArrow, 0x0000, 0xffff, NULL, 0, 0x0000, NULL, nec, 0x40be, 1, 0x2c); // rewind
  buttons.addButton(60, 220, 12, 48, 100, 60, leftArrow, 0x0000, 0xffff, NULL, 0, 0x0000, NULL, nec, 0x40be, 1, 0x2c); // rewind
  buttons.addButton(96, 220, 48, 48, 60, 50, rightArrow, 0x0000, 0xffff, NULL, 0, 0x0000, NULL, nec, 0x40be, 1, 0x2d); // play
  buttons.addButton(168, 220, 12, 48, 100, 60, rightArrow, 0x0000, 0xffff, NULL, 0, 0x0000, NULL, nec, 0x40be, 1, 0x2e); // fast forward
  buttons.addButton(156, 220, 12, 48, 100, 60, rightArrow, 0x0000, 0xffff, NULL, 0, 0x0000, NULL, nec, 0x40be, 1, 0x2e); // fast forward
  buttons.addButton(204, 220, 12, 48, 100, 60, rightArrow, 0x0000, 0xffff, NULL, 0, 0x0000, NULL, nec, 0x40be, 1, 0x26); // skip forward
  buttons.addButton(216, 220, 12, 48, 100, 60, rightArrow, 0x0000, 0xffff, NULL, 0, 0x0000, NULL, nec, 0x40be, 1, 0x26); // skip forward
  buttons.addButton(228, 220, 2, 48, 100, 60, filledRectangle, 0x0000, 0xffff, NULL, 0, 0x0000, NULL, nec, 0x40be, 1, 0x26); // skip forward

  buttons.addButton(111, 11, 10, 10, 100, 100, text, 0xffff, 0xffff, "TV(Video)", 1, 0x0000, NULL, noRmt, 0, 0);
  buttons.addButton(0, 268, 48, 48, 50, 50, leftArrow, 0x0000, 0xffff, NULL, 0, 0x0000, setTvController1, noRmt, 0, 0);
  buttons.addButton(192, 268, 48, 48, 50, 50, rightArrow, 0x0000, 0xffff, NULL, 0, 0x0000, setCatvController, noRmt, 0, 0);

  setTvControllerCommon2();
  
  buttons.clearScreen();
  buttons.displayAllButtons();
}

void setCatvController() {
  buttons.deleteAllButtons();
  buttons.setBgColor(0xffff);

  /* 1st row */
  buttons.addButton(0, 28, 96, 48, 100, 100, rectangle, 0xffff, 0xffff, "EPG", 1, 0x0000, NULL, panasonic, 0x0220, 3, 0x08, 0x26, 0x55); // EPG
  buttons.addButton(96, 28, 48, 48, 60, 30, upCaret, 0x0000, 0xffff, NULL, 3, 0x0000, NULL, panasonic, 0x0220, 3, 0x08, 0x26, 0x5a); // up
  buttons.addButton(192, 28, 48, 48, 100, 100, power, 0x0000, 0xffff, NULL, 0, 0x0000, NULL, panasonic, 0x0220, 3, 0x08, 0x26, 0x8d); // power

  /* 2nd row */
  buttons.addButton(48, 76, 48, 48, 30, 60, leftCaret, 0x0000, 0xffff, NULL, 3, 0x0000, NULL, panasonic, 0x0220, 3, 0x08, 0x26, 0x5d); // single left
  buttons.addButton(96, 76, 48, 48, 40, 40, rectangle, 0x0000, 0xffff, NULL, 2, 0x0000, NULL, panasonic, 0x0220, 3, 0x08, 0x26, 0x53); // ok
  buttons.addButton(144, 76, 48, 48, 30, 60, rightCaret, 0x0000, 0xffff, NULL, 3, 0x0000, NULL, panasonic, 0x0220, 3, 0x08, 0x26, 0x5e); // single right

  /* 3rd row */
  buttons.addButton(0, 124, 96, 48, 100, 100, rectangle, 0xffff, 0xffff, "Back", 1, 0x0000, NULL, panasonic, 0x0220, 3, 0x08, 0x26, 0x52); // back
  buttons.addButton(96, 124, 48, 48, 60, 30, downCaret, 0x0000, 0xffff, NULL, 3, 0x0000, NULL, panasonic, 0x0220, 3, 0x08, 0x26, 0x5b); // down
  buttons.addButton(144, 124, 96, 48, 100, 100, rectangle, 0xffff, 0xffff, "Menu", 1, 0x0000, NULL, panasonic, 0x0220, 0x03, 0x08, 0x26, 0x85); // menu

  /* 4th row */
  buttons.addButton(0, 172, 48, 48, 60, 30, downArrow, 0x0000, 0xffff, NULL, 0, 0x0000, NULL, panasonic, 0x0220, 3, 0x08, 0x26, 0x75); // channel down
  buttons.addButton(72, 172, 48, 48, 60, 30, upArrow, 0x0000, 0xffff, NULL, 0, 0x0000, NULL, panasonic, 0x0220, 3, 0x08, 0x26, 0x74); // channel up
  buttons.addButton(132, 172, 48, 48, 100, 100, rectangle, 0xffff, 0xffff, "-", 2, 0x0000, NULL, nec, 0x40bf, 1, 0x1e); // volume down
  buttons.addButton(196, 172, 48, 48, 100, 100, rectangle, 0xffff, 0xffff, "+", 2, 0x0000, NULL, nec, 0x40bf, 1, 0x1a); // volume up

  /* 5th row */
  buttons.addButton(0, 220, 80, 48, 60, 30, rectangle, 0xffff, 0xffff, "DTV", 1, 0x0000, NULL, panasonic, 0x0220, 3, 0x08, 0x26, 0x6a);
  buttons.addButton(80, 220, 80, 48, 60, 30, rectangle, 0xffff, 0xffff, "BS", 1, 0x0000, NULL, panasonic, 0x0220, 3, 0x08, 0x26, 0x6b);
  buttons.addButton(160, 220, 80, 48, 60, 30, rectangle, 0xffff, 0xffff, "CATV", 1, 0x0000, NULL, panasonic, 0x0220, 3, 0x08, 0x26, 0x6c);

  buttons.addButton(0, 268, 48, 48, 50, 50, leftArrow, 0x0000, 0xffff, NULL, 0, 0x0000, setTvController2, noRmt, 0, 0);
  buttons.addButton(192, 268, 48, 48, 50, 50, rightArrow, 0x0000, 0xffff, NULL, 0, 0x0000, setTvController1, noRmt, 0, 0);

  buttons.addButton(111, 11, 10, 10, 100, 100, text, 0xffff, 0xffff, "CATV", 1, 0x0000, NULL, noRmt, 0, 0);
  buttons.addButton(0, 32, 240, 1, 100, 100, filledRectangle, 0x0000, 0x0000, NULL, 1, 0x0000, NULL, noRmt, 0, 0); // line
  buttons.addButton(164, 172, 48, 48, 100, 100, text, 0xffff, 0xffff, "Vol", 1, 0x0000, NULL, noRmt, 0, 0); // Vol
  buttons.addButton(37, 172, 48, 48, 100, 100, text, 0xffff, 0xffff, "Ch", 1, 0x0000, NULL, noRmt, 0, 0);

  buttons.clearScreen();
  buttons.displayAllButtons();
}

void screenSaver () {
  static long last = 0;
  static int n = 0;
  int length = 20;

  if ((millis() - last) > 100) {
    last = millis();
    tft.fillRect(random(tft.width() - length), random(tft.height() - length), length, length, 0x0000);
    if (n++ > 500) {
      tft.fillScreen(random(0xffff));
      n = 0;
    }
  }
}

void setup(void) {
  Serial.begin(115200);

  buttons.setFont(&FreeSans12pt7b);
  setTvController1();
  buttons.setScreenSaver(screenSaver, 300000);
}

void loop() {
  buttons.checkButtons();
}


