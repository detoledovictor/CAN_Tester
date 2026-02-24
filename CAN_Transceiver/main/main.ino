#include "config.h"
#include "peripherals.h"
#include "can.h"

static uint8_t  digitalBuffer[DIGITAL_CHANNELS];
static uint16_t analogBuffer[ANALOG_CHANNELS];

static uint32_t lastTxMs = 0;

void setup() {
  peripherals_init();
  can_init();
}

void loop() {

  uint32_t now = millis();

  if ((now - lastTxMs) >= CAN_TX_PERIOD_MS) {
    lastTxMs = now;

    peripherals_read_digitals(digitalBuffer);
    peripherals_read_analogs(analogBuffer);

    can_send_digitals(digitalBuffer);
    can_send_analogs(analogBuffer);
  }
}
