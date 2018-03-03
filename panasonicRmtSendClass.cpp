#include "panasonicRmtSendClass.h"

panasonicRmtSendClass::panasonicRmtSendClass(uint8_t irPin, uint8_t channel, uint16_t customCode) : rmtSendClass(irPin, channel, customCode) {
  rmtDataLength = 50;
  leaderOnUs = 3400;
  leaderOffUs = 1700;
  dataOnUs = 425;
  data1OffUs = 1275;
  data0OffUs = 425;
  stopbitOnUs = 425;
  stopbitOffUs = 0x7fff;

  rmtData = new rmt_item32_t[rmtDataLength];
}

void panasonicRmtSendClass::sendData(uint8_t *dataCode) {
  sendData(customCode, dataCode);
}

void panasonicRmtSendClass::sendData(uint16_t customCode, uint8_t *dataCode) {
  /* leader code 1bit: ON 3400us, OFF 1700us */
  rmtData[0].duration0 = leaderOnUs;
  rmtData[0].level0 = 1;
  rmtData[0].duration1 = leaderOffUs;
  rmtData[0].level1 = 0;

  rmtPack8BitData(1, customCode >> 8);
  rmtPack8BitData(9, customCode & 0xff);

  int parity = 0;

  for (int i = 0; i < 4; i++) {
    parity ^= ((customCode >> (i * 4)) & 0xf);
  }

  uint8_t parityAndData0 = (parity & 0xf) | (dataCode[0] << 4);

  rmtPack8BitData(17, parityAndData0);
  rmtPack8BitData(25, dataCode[1]);
  rmtPack8BitData(33, dataCode[2]);
  rmtPack8BitData(41, parityAndData0 ^ dataCode[1] ^ dataCode[2]);

  /* stop bit 1bit: ON 425 */
  rmtData[49].duration0 = stopbitOnUs;
  rmtData[49].level0 = 1;
  rmtData[49].duration1 = stopbitOffUs;
  rmtData[49].level1 = 0;

  rmt_write_items((rmt_channel_t)channel, rmtData, rmtDataLength, true);
}

