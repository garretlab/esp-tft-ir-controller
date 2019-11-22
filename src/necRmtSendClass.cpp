#include "necRmtSendClass.h"

necRmtSendClass::necRmtSendClass(uint8_t irPin, uint8_t channel, uint16_t customCode) : rmtSendClass(irPin, channel, customCode) {
  rmtDataLength = 34;
  leaderOnUs = 9000;
  leaderOffUs = 4500;
  dataOnUs = 560;
  data1OffUs = 1690;
  data0OffUs = 560;
  stopbitOnUs = 560;
  stopbitOffUs = 0x7fff;

  rmtData = new rmt_item32_t[rmtDataLength];
}

void necRmtSendClass::sendData(uint8_t dataCode) {
  sendData(customCode, dataCode);
}

void necRmtSendClass::sendData(uint16_t customCode, uint8_t dataCode) {
  /* leader code 1bit: ON 9000us, OFF 4500us */
  rmtData[0].duration0 = leaderOnUs;
  rmtData[0].level0 = 1;
  rmtData[0].duration1 = leaderOffUs;
  rmtData[0].level1 = 0;

  rmtPack8BitData(1, customCode >> 8);
  rmtPack8BitData(9, customCode & 0xff);

  rmtPack8BitData(17, dataCode);
  rmtPack8BitData(25, ~dataCode);
  
  /* stop bit 1bit: ON 560 */
  rmtData[33].duration0 = stopbitOnUs;
  rmtData[33].level0 = 1;
  rmtData[33].duration1 = stopbitOffUs;
  rmtData[33].level1 = 0;

  rmt_write_items((rmt_channel_t)channel, rmtData, rmtDataLength, true);
}

