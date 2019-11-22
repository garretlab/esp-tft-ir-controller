#pragma once

#include "driver/rmt.h"

/* Generic Class for IR remote controller */
class rmtSendClass {
  public:
    rmtSendClass(uint8_t irPin, uint8_t channel, uint16_t customCode = 0);

  protected:
    int rmtDataLength;
    int leaderOnUs;
    int leaderOffUs;
    int dataOnUs;
    int data1OffUs;
    int data0OffUs;
    int stopbitOnUs;
    int stopbitOffUs;

    uint16_t customCode;
    static uint8_t channel;
    void rmtPack8BitData(int index, uint8_t data);
    rmt_item32_t *rmtData;
    rmt_config_t *rmtConfig;
};


