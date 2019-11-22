#include "rmtSendClass.h"

uint8_t rmtSendClass::channel;

rmtSendClass::rmtSendClass(uint8_t irPin, uint8_t channel, uint16_t customCode) {
  static int initialized = 0;
  rmt_config_t rmtConfig;

  this->customCode = customCode;

  if (!initialized) {
    this->channel = channel;
    
    rmtConfig.rmt_mode = RMT_MODE_TX;  // transmit mode
    rmtConfig.channel = (rmt_channel_t)channel;  // channel to use 0 - 7
    rmtConfig.clk_div = 80;  // clock divider 1 - 255. source clock is 80MHz -> 80MHz/80 = 1MHz -> 1 tick = 1 us
    rmtConfig.gpio_num = (gpio_num_t)irPin; // pin to use
    rmtConfig.mem_block_num = 1; // memory block size

    rmtConfig.tx_config.loop_en = 0; // no loop
    rmtConfig.tx_config.carrier_freq_hz = 38000;  // IR remote controller uses 38kHz carrier frequency
    rmtConfig.tx_config.carrier_duty_percent = 33; // duty
    rmtConfig.tx_config.carrier_level =  RMT_CARRIER_LEVEL_HIGH; // carrier level
    rmtConfig.tx_config.carrier_en = 1;  // carrier enable
    rmtConfig.tx_config.idle_level =  RMT_IDLE_LEVEL_LOW ; // signal level at idle
    rmtConfig.tx_config.idle_output_en = 0;  // output if idle

    rmt_config(&rmtConfig);
    rmt_driver_install(rmtConfig.channel, 0, 0);
    initialized = 1;
  }
}

/*
   data code 8bit
   INPUT series: b7 b6 b5 b4 b3 b2 b1 b0
   SEND  series: b0 b1 b2 b3 b4 b5 b6 b7
*/
void rmtSendClass::rmtPack8BitData(int index, uint8_t data) {
  for (int i = 0; i < 8; i++) {
    rmtData[i + index].duration0 = dataOnUs;
    rmtData[i + index].level0 = 1;
    if (data & (1 << i)) {
      rmtData[i + index].duration1 = data1OffUs;
    } else {
      rmtData[i + index].duration1 = data0OffUs;
    }
    rmtData[i + index].level1 = 0;
  }

}
