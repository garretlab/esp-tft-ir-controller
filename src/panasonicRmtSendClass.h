#pragma once

#include "driver/rmt.h"
#include "rmtSendClass.h"

class panasonicRmtSendClass : public rmtSendClass {
  public:
    panasonicRmtSendClass(uint8_t irPin, uint8_t channel, uint16_t customCode = 0);
    void sendData(uint8_t *dataCode);
    void sendData(uint16_t customCode, uint8_t *dataCode);
};
