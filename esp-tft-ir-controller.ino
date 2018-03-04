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
const uint16_t yp0 = 0, yp1 = 32, yp2 = 80, yp3 = 128, yp4 = 176, yp5 = 224, yp6 = 272;

#if 0 /* not used */
const int irReceiverPin = 22;
#endif

Adafruit_ILI9341 tft = Adafruit_ILI9341(tftCS, tftDc);    // TFT
Adafruit_STMPE610 ts = Adafruit_STMPE610(stmpeCs);        // Touch

tftRmtClass buttons(&tft, &ts, ledPin, 0, ILI9341_WHITE);

void setControllerCommon1() {
  buttons.deleteAllButtons();
  buttons.setBgColor(0xffff);

  buttons.addButton(0, yp0, 32, 32, 60, 30, downArrow, 0x0000, 0xffff, NULL, 0, 0x0000, NULL, nec, 0x40bf, 1, 0x0f); // input up
  buttons.addButton(192, yp0, 32, 32, 60, 30, upArrow, 0x0000, 0xffff, NULL, 0, 0x0000, NULL, nec, 0x40bf, 1, 0x3a); // input down
}

void setControllerCommon2() {
  buttons.addButton(0, yp1, 240, 1, 100, 100, filledRectangle, 0x0000, 0x0000, NULL, 1, 0x0000, NULL, noRmt, 0, 0); // line
  buttons.addButton(164, yp4, 48, 48, 100, 100, text, 0xffff, 0xffff, "Vol", 1, 0x0000, NULL, noRmt, 0, 0); // Vol

  buttons.clearScreen();
  buttons.displayAllButtons();
}

void setTvControllerCommon1() {
  /* 1st row */
  buttons.addButton(0, yp1, 96, 48, 100, 100, rectangle, 0xffff, 0xffff, "EPG", 1, 0x0000, NULL, nec, 0x40bf, 1, 0x6e); // EPG
  buttons.addButton(96, yp1, 48, 48, 60, 30, upCaret, 0x0000, 0xffff, NULL, 3, 0x0000, NULL, nec, 0x40bf, 1, 0x3e); // up
  buttons.addButton(192, yp1, 48, 48, 100, 100, power, 0x0000, 0xffff, NULL, 0, 0x0000, NULL, nec, 0x40bf, 1, 0x12); // power

  /* 2nd row */
  buttons.addButton(12, yp2, 12, 48, 100, 60, leftCaret, 0x0000, 0xffff, NULL, 3, 0x0000, NULL, nec, 0x40be, 1, 0x22); // double left
  buttons.addButton(24, yp2, 12, 48, 100, 60, leftCaret, 0x0000, 0xffff, NULL, 3, 0x0000, NULL, nec, 0x40be, 1, 0x22); // double left
  buttons.addButton(48, yp2, 48, 48, 30, 60, leftCaret, 0x0000, 0xffff, NULL, 3, 0x0000, NULL, nec, 0x40bf, 1, 0x5f); // single left
  buttons.addButton(96, yp2, 48, 48, 40, 40, rectangle, 0x0000, 0xffff, NULL, 2, 0x0000, NULL, nec, 0x40bf, 1, 0x3d); // ok
  buttons.addButton(144, yp2, 48, 48, 30, 60, rightCaret, 0x0000, 0xffff, NULL, 3, 0x0000, NULL, nec, 0x40bf, 1, 0x5b); // single right
  buttons.addButton(218, yp2, 12, 48, 100, 60, rightCaret, 0x0000, 0xffff, NULL, 3, 0x0000, NULL, nec, 0x40be, 1, 0x23); // double right
  buttons.addButton(206, yp2, 12, 48, 100, 60, rightCaret, 0x0000, 0xffff, NULL, 3, 0x0000, NULL, nec, 0x40be, 1, 0x23); // double right

  /* 3rd row */
  buttons.addButton(0, yp3, 96, 48, 100, 100, rectangle, 0xffff, 0xffff, "Menu", 1, 0x0000, NULL, nec, 0x40be, 1, 0x34); // menu
  buttons.addButton(144, yp3, 96, 48, 100, 100, rectangle, 0xffff, 0xffff, "Back", 1, 0x0000, NULL, nec, 0x40bf, 1, 0x3b); // back
  buttons.addButton(96, yp3, 48, 48, 60, 30, downCaret, 0x0000, 0xffff, NULL, 3, 0x0000, NULL, nec, 0x40bf, 1, 0x3f); // down

  /* 4th row */
  buttons.addButton(132, yp4, 48, 48, 100, 100, rectangle, 0xffff, 0xffff, "-", 2, 0x0000, NULL, nec, 0x40bf, 1, 0x1e); // volume down
  buttons.addButton(196, yp4, 48, 48, 100, 100, rectangle, 0xffff, 0xffff, "+", 2, 0x0000, NULL, nec, 0x40bf, 1, 0x1a); // volume up
}

void setTvControllerCommon2() {
}

void setTvController1 () {

  setControllerCommon1();
  setTvControllerCommon1();

  /* 4th row */
  buttons.addButton(0, yp4, 48, 48, 60, 30, downArrow, 0x0000, 0xffff, NULL, 0, 0x0000, NULL, nec, 0x40bf, 1, 0x1f); // channel down
  buttons.addButton(72, yp4, 48, 48, 60, 30, upArrow, 0x0000, 0xffff, NULL, 0, 0x0000, NULL, nec, 0x40bf, 1, 0x1b); // channel up

  /* 5th row */
  buttons.addButton(0, yp5, 48, 48, 40, 40, filledRectangle, 0x001f, 0xffff, NULL, 0, 0x0000, NULL, nec, 0x40bf, 1, 0x73); // blue
  buttons.addButton(36, yp5, 48, 48, 40, 40, filledRectangle, 0xf800, 0xffff, NULL, 0, 0x0000, NULL, nec, 0x40bf, 1, 0x74); // red
  buttons.addButton(72, yp5, 48, 48, 40, 40, filledRectangle, 0x03e0, 0xffff, NULL, 0, 0x0000, NULL, nec, 0x40bf, 1, 0x75); // green
  buttons.addButton(108, yp5, 48, 48, 40, 40, filledRectangle, 0xffe0, 0xffff, NULL, 0, 0x0000, NULL, nec, 0x40bf, 1, 0x76); // yellow
  buttons.addButton(144, yp5, 96, 48, 100, 100, rectangle, 0xffff, 0xffff, "Data", 1, 0x0000, NULL, nec, 0x43bc, 1, 0x14); // data

  /* 6th row */
  buttons.addButton(0, yp6, 48, 48, 50, 50, leftArrow, 0x0000, 0xffff, NULL, 0, 0x0000, setBrController, noRmt, 0, 0);
  buttons.addButton(192, yp6, 48, 48, 50, 50, rightArrow, 0x0000, 0xffff, NULL, 0, 0x0000, setTvController2, noRmt, 0, 0);

  buttons.addButton(111, 11, 10, 10, 100, 100, text, 0xffff, 0xffff, "TV", 1, 0x0000, NULL, noRmt, 0, 0);
  buttons.addButton(37, yp4, 48, 48, 100, 100, text, 0xffff, 0xffff, "Ch", 1, 0x0000, NULL, noRmt, 0, 0);

  setTvControllerCommon2();
  setControllerCommon2();
}

void setTvController2 () {
  setControllerCommon1();
  setTvControllerCommon1();

  /* 4th row */
  buttons.addButton(0, yp4, 96, 48, 100, 100, rectangle, 0xffff, 0xffff, "Video", 1, 0x0000, NULL, nec, 0x40be, 1, 0x28); // video
  buttons.addButton(96, yp4, 48, 48, 40, 40, filledRectangle, 0x0000, 0xffff, NULL, 0, 0x0000, NULL, nec, 0x40be, 1, 0x2b); // stop

  /* 5th row */
  buttons.addButton(12, yp5, 2, 48, 100, 60, filledRectangle, 0x0000, 0xffff, NULL, 0, 0x0000, NULL, nec, 0x40be, 1, 0x27); // skip back
  buttons.addButton(24, yp5, 12, 48, 100, 60, leftArrow, 0x0000, 0xffff, NULL, 0, 0x0000, NULL, nec, 0x40be, 1, 0x27); // skip back
  buttons.addButton(12, yp5, 12, 48, 100, 60, leftArrow, 0x0000, 0xffff, NULL, 0, 0x0000, NULL, nec, 0x40be, 1, 0x27); // skip back
  buttons.addButton(72, yp5, 12, 48, 100, 60, leftArrow, 0x0000, 0xffff, NULL, 0, 0x0000, NULL, nec, 0x40be, 1, 0x2c); // rewind
  buttons.addButton(60, yp5, 12, 48, 100, 60, leftArrow, 0x0000, 0xffff, NULL, 0, 0x0000, NULL, nec, 0x40be, 1, 0x2c); // rewind
  buttons.addButton(96, yp5, 48, 48, 60, 50, rightArrow, 0x0000, 0xffff, NULL, 0, 0x0000, NULL, nec, 0x40be, 1, 0x2d); // play
  buttons.addButton(168, yp5, 12, 48, 100, 60, rightArrow, 0x0000, 0xffff, NULL, 0, 0x0000, NULL, nec, 0x40be, 1, 0x2e); // fast forward
  buttons.addButton(156, yp5, 12, 48, 100, 60, rightArrow, 0x0000, 0xffff, NULL, 0, 0x0000, NULL, nec, 0x40be, 1, 0x2e); // fast forward
  buttons.addButton(204, yp5, 12, 48, 100, 60, rightArrow, 0x0000, 0xffff, NULL, 0, 0x0000, NULL, nec, 0x40be, 1, 0x26); // skip forward
  buttons.addButton(216, yp5, 12, 48, 100, 60, rightArrow, 0x0000, 0xffff, NULL, 0, 0x0000, NULL, nec, 0x40be, 1, 0x26); // skip forward
  buttons.addButton(228, yp5, 2, 48, 100, 60, filledRectangle, 0x0000, 0xffff, NULL, 0, 0x0000, NULL, nec, 0x40be, 1, 0x26); // skip forward

  buttons.addButton(111, 11, 10, 10, 100, 100, text, 0xffff, 0xffff, "TV(Video)", 1, 0x0000, NULL, noRmt, 0, 0);
  buttons.addButton(0, yp6, 48, 48, 50, 50, leftArrow, 0x0000, 0xffff, NULL, 0, 0x0000, setTvController1, noRmt, 0, 0);
  buttons.addButton(192, yp6, 48, 48, 50, 50, rightArrow, 0x0000, 0xffff, NULL, 0, 0x0000, setCatvController, noRmt, 0, 0);

  setTvControllerCommon2();
  setControllerCommon2();
}

void setCatvController() {
  setControllerCommon1();

  /* 1st row */
  buttons.addButton(0, yp1, 96, 48, 100, 100, rectangle, 0xffff, 0xffff, "EPG", 1, 0x0000, NULL, panasonic, 0x0220, 3, 0x08, 0x26, 0x55); // EPG
  buttons.addButton(96, yp1, 48, 48, 60, 30, upCaret, 0x0000, 0xffff, NULL, 3, 0x0000, NULL, panasonic, 0x0220, 3, 0x08, 0x26, 0x5a); // up
  buttons.addButton(192, yp1, 48, 48, 100, 100, power, 0x0000, 0xffff, NULL, 0, 0x0000, NULL, panasonic, 0x0220, 3, 0x08, 0x26, 0x8d); // power

  /* 2nd row */
  buttons.addButton(48, yp2, 48, 48, 30, 60, leftCaret, 0x0000, 0xffff, NULL, 3, 0x0000, NULL, panasonic, 0x0220, 3, 0x08, 0x26, 0x5d); // single left
  buttons.addButton(96, yp2, 48, 48, 40, 40, rectangle, 0x0000, 0xffff, NULL, 2, 0x0000, NULL, panasonic, 0x0220, 3, 0x08, 0x26, 0x53); // ok
  buttons.addButton(144, yp2, 48, 48, 30, 60, rightCaret, 0x0000, 0xffff, NULL, 3, 0x0000, NULL, panasonic, 0x0220, 3, 0x08, 0x26, 0x5e); // single right

  /* 3rd row */
  buttons.addButton(0, yp3, 96, 48, 100, 100, rectangle, 0xffff, 0xffff, "Menu", 1, 0x0000, NULL, panasonic, 0x0220, 0x03, 0x08, 0x26, 0x85); // menu
  buttons.addButton(96, yp3, 48, 48, 60, 30, downCaret, 0x0000, 0xffff, NULL, 3, 0x0000, NULL, panasonic, 0x0220, 3, 0x08, 0x26, 0x5b); // down
  buttons.addButton(144, yp3, 96, 48, 100, 100, rectangle, 0xffff, 0xffff, "Back", 1, 0x0000, NULL, panasonic, 0x0220, 3, 0x08, 0x26, 0x52); // back

  /* 4th row */
  buttons.addButton(0, yp4, 48, 48, 60, 30, downArrow, 0x0000, 0xffff, NULL, 0, 0x0000, NULL, panasonic, 0x0220, 3, 0x08, 0x26, 0x75); // channel down
  buttons.addButton(72, yp4, 48, 48, 60, 30, upArrow, 0x0000, 0xffff, NULL, 0, 0x0000, NULL, panasonic, 0x0220, 3, 0x08, 0x26, 0x74); // channel up
  buttons.addButton(132, yp4, 48, 48, 100, 100, rectangle, 0xffff, 0xffff, "-", 2, 0x0000, NULL, nec, 0x40bf, 1, 0x1e); // volume down
  buttons.addButton(196, yp4, 48, 48, 100, 100, rectangle, 0xffff, 0xffff, "+", 2, 0x0000, NULL, nec, 0x40bf, 1, 0x1a); // volume up

  /* 5th row */
  buttons.addButton(0, yp5, 80, 48, 60, 30, rectangle, 0xffff, 0xffff, "DTV", 1, 0x0000, NULL, panasonic, 0x0220, 3, 0x08, 0x26, 0x6a);
  buttons.addButton(80, yp5, 80, 48, 60, 30, rectangle, 0xffff, 0xffff, "BS", 1, 0x0000, NULL, panasonic, 0x0220, 3, 0x08, 0x26, 0x6b);
  buttons.addButton(160, yp5, 80, 48, 60, 30, rectangle, 0xffff, 0xffff, "CATV", 1, 0x0000, NULL, panasonic, 0x0220, 3, 0x08, 0x26, 0x6c);

  buttons.addButton(0, yp6, 48, 48, 50, 50, leftArrow, 0x0000, 0xffff, NULL, 0, 0x0000, setTvController2, noRmt, 0, 0);
  buttons.addButton(192, yp6, 48, 48, 50, 50, rightArrow, 0x0000, 0xffff, NULL, 0, 0x0000, setBrController, noRmt, 0, 0);

  buttons.addButton(111, 11, 10, 10, 100, 100, text, 0xffff, 0xffff, "CATV", 1, 0x0000, NULL, noRmt, 0, 0);
  buttons.addButton(164, yp4, 48, 48, 100, 100, text, 0xffff, 0xffff, "Vol", 1, 0x0000, NULL, noRmt, 0, 0); // Vol
  buttons.addButton(37, yp4, 48, 48, 100, 100, text, 0xffff, 0xffff, "Ch", 1, 0x0000, NULL, noRmt, 0, 0);

  setControllerCommon2();
}

void setBrController() {
  setControllerCommon1();

  /* 1st row */
  buttons.addButton(0, yp1, 96, 48, 100, 100, rectangle, 0xffff, 0xffff, "EPG", 1, 0x0000, NULL, nec, 0x45bc, 1, 0x6d); // EPG
  buttons.addButton(96, yp1, 48, 48, 60, 30, upCaret, 0x0000, 0xffff, NULL, 3, 0x0000, NULL, nec, 0x45bc, 1, 0xc0); // up
  buttons.addButton(192, yp1, 48, 48, 100, 100, power, 0x0000, 0xffff, NULL, 0, 0x0000, NULL, nec, 0x45bc, 1, 0x12); // power

  /* 2nd row */
  buttons.addButton(12, yp2, 12, 48, 100, 60, leftCaret, 0x0000, 0xffff, NULL, 3, 0x0000, NULL, nec, 0x45bc, 1, 0x55); // double left
  buttons.addButton(24, yp2, 12, 48, 100, 60, leftCaret, 0x0000, 0xffff, NULL, 3, 0x0000, NULL, nec, 0x45bc, 1, 0x55); // double left
  buttons.addButton(48, yp2, 48, 48, 30, 60, leftCaret, 0x0000, 0xffff, NULL, 3, 0x0000, NULL, nec, 0x45bc, 1, 0xcc); // single left
  buttons.addButton(96, yp2, 48, 48, 40, 40, rectangle, 0x0000, 0xffff, NULL, 2, 0x0000, NULL, nec, 0x45bc, 1, 0x44); // ok
  buttons.addButton(144, yp2, 48, 48, 30, 60, rightCaret, 0x0000, 0xffff, NULL, 3, 0x0000, NULL, nec, 0x45bc, 1, 0xc4); // single right
  buttons.addButton(218, yp2, 12, 48, 100, 60, rightCaret, 0x0000, 0xffff, NULL, 3, 0x0000, NULL, nec, 0x45bc, 1, 0x5b); // double right
  buttons.addButton(206, yp2, 12, 48, 100, 60, rightCaret, 0x0000, 0xffff, NULL, 3, 0x0000, NULL, nec, 0x45bc, 1, 0x5b); // double right

  /* 3rd row */
  buttons.addButton(0, yp3, 96, 48, 100, 100, rectangle, 0xffff, 0xffff, "Menu", 1, 0x0000, NULL, nec, 0x45bc, 1, 0x46); // menu
  buttons.addButton(144, yp3, 96, 48, 100, 100, rectangle, 0xffff, 0xffff, "Back", 1, 0x0000, NULL, nec, 0x45bc, 1, 0x4b); // back
  buttons.addButton(96, yp3, 48, 48, 60, 30, downCaret, 0x0000, 0xffff, NULL, 3, 0x0000, NULL, nec, 0x45bc, 1, 0xc8); // down

  /* 4th row */
  buttons.addButton(132, yp4, 48, 48, 100, 100, rectangle, 0xffff, 0xffff, "-", 2, 0x0000, NULL, nec, 0x40bf, 1, 0x1e); // volume down
  buttons.addButton(196, yp4, 48, 48, 100, 100, rectangle, 0xffff, 0xffff, "+", 2, 0x0000, NULL, nec, 0x40bf, 1, 0x1a); // volume up
  buttons.addButton(0, yp4, 96, 48, 100, 100, rectangle, 0xffff, 0xffff, "Sub", 1, 0x0000, NULL, nec, 0x45bc, 1, 0xba); // sub menu
  buttons.addButton(96, yp4, 48, 48, 40, 40, filledRectangle, 0x0000, 0xffff, NULL, 0, 0x0000, NULL, nec, 0x45bc, 1, 0x16); // stop

  /* 5th row */
  buttons.addButton(12, yp5, 2, 48, 100, 60, filledRectangle, 0x0000, 0xffff, NULL, 0, 0x0000, NULL, nec, 0x45bc, 1, 0x84); // skip back
  buttons.addButton(24, yp5, 12, 48, 100, 60, leftArrow, 0x0000, 0xffff, NULL, 0, 0x0000, NULL, nec, 0x45bc, 1, 0x84); // skip back
  buttons.addButton(12, yp5, 12, 48, 100, 60, leftArrow, 0x0000, 0xffff, NULL, 0, 0x0000, NULL, nec, 0x45bc, 1, 0x84); // skip back
  buttons.addButton(72, yp5, 12, 48, 100, 60, leftArrow, 0x0000, 0xffff, NULL, 0, 0x0000, NULL, nec, 0x45bc, 1, 0x4b); // rewind
  buttons.addButton(60, yp5, 12, 48, 100, 60, leftArrow, 0x0000, 0xffff, NULL, 0, 0x0000, NULL, nec, 0x45bc, 1, 0x4b); // rewind
  buttons.addButton(96, yp5, 48, 48, 60, 50, rightArrow, 0x0000, 0xffff, NULL, 0, 0x0000, NULL, nec, 0x45bc, 1, 0x13); // play
  buttons.addButton(168, yp5, 12, 48, 100, 60, rightArrow, 0x0000, 0xffff, NULL, 0, 0x0000, NULL, nec, 0x45bc, 1, 0x9a); // fast forward
  buttons.addButton(156, yp5, 12, 48, 100, 60, rightArrow, 0x0000, 0xffff, NULL, 0, 0x0000, NULL, nec, 0x45bc, 1, 0x9a); // fast forward
  buttons.addButton(204, yp5, 12, 48, 100, 60, rightArrow, 0x0000, 0xffff, NULL, 0, 0x0000, NULL, nec, 0x45bc, 1, 0x80); // skip forward
  buttons.addButton(216, yp5, 12, 48, 100, 60, rightArrow, 0x0000, 0xffff, NULL, 0, 0x0000, NULL, nec, 0x45bc, 1, 0x80); // skip forward
  buttons.addButton(228, yp5, 2, 48, 100, 60, filledRectangle, 0x0000, 0xffff, NULL, 0, 0x0000, NULL, nec, 0x45bc, 1, 0x80); // skip forward

  buttons.addButton(100, yp6, 24, 48, 30, 40, filledRectangle, 0x0000, 0xffff, NULL, 0, 0x0000, NULL, nec, 0x45bc, 1, 0x17); // pause
  buttons.addButton(114, yp6, 24, 48, 30, 40, filledRectangle, 0x0000, 0xffff, NULL, 0, 0x0000, NULL, nec, 0x45bc, 1, 0x17); // pause

  buttons.addButton(110, 11, 10, 10, 100, 100, text, 0xffff, 0xffff, " Blu-ray ", 1, 0x0000, NULL, noRmt, 0, 0);
  buttons.addButton(164, yp4, 48, 48, 100, 100, text, 0xffff, 0xffff, "Vol", 1, 0x0000, NULL, noRmt, 0, 0); // Vol
  buttons.addButton(0, yp6, 48, 48, 50, 50, leftArrow, 0x0000, 0xffff, NULL, 0, 0x0000, setCatvController, noRmt, 0, 0);
  buttons.addButton(192, yp6, 48, 48, 50, 50, rightArrow, 0x0000, 0xffff, NULL, 0, 0x0000, setTvController1, noRmt, 0, 0);

  setControllerCommon2();
}

void screenSaver () {
  static long lastTime = 0;
  int figureSize;
  int color = random(0xffff);
  static int n = 0;
  const int maxRepeat = 500;

  if ((millis() - lastTime) > 100) {
    lastTime = millis();
    figureSize = random(40);
    tft.fillRect(random(tft.width() - figureSize), random(tft.height() - figureSize), figureSize, figureSize, color);
    if (++n > maxRepeat) {
      buttons.clearScreen();
      buttons.displayAllButtons();
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
