#include "can.h"
#include "config.h"
#include "can_protocol.h"

static MCP_CAN CAN(CAN_CS_PIN);

void can_init(void) {

  // Tenta inicializar até 10 vezes (~5 s) antes de continuar mesmo assim
  uint8_t attempts = 0;
  while (CAN.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ) != CAN_OK) {
    delay(500);
    if (++attempts >= 10) break;   // Evita loop infinito
  }

  CAN.setMode(MCP_NORMAL);
  pinMode(CAN_INT_PIN, INPUT);
}

void can_send_digitals(uint8_t *dig) {

  uint8_t buf0[7];
  uint8_t buf1[2];

  for (uint8_t i = 0; i < 7; i++) {
    buf0[i] = dig[i];
  }

  buf1[0] = dig[7];
  buf1[1] = dig[8];

  // Verifica retorno — CAN_OK = 0
  (void)CAN.sendMsgBuf(CAN_ID_DIG_0, 0, 7, buf0);
  (void)CAN.sendMsgBuf(CAN_ID_DIG_1, 0, 2, buf1);
}

void can_send_analogs(uint16_t *ana) {

  uint8_t buf0[8];
  uint8_t buf1[8];

  for (uint8_t i = 0; i < 4; i++) {
    buf0[i * 2]     = (uint8_t)((ana[i] >> 8) & 0xFF);
    buf0[i * 2 + 1] = (uint8_t)(ana[i] & 0xFF);
  }

  for (uint8_t i = 0; i < 4; i++) {
    buf1[i * 2]     = (uint8_t)((ana[i + 4] >> 8) & 0xFF);
    buf1[i * 2 + 1] = (uint8_t)(ana[i + 4] & 0xFF);
  }

  (void)CAN.sendMsgBuf(CAN_ID_AN_0, 0, 8, buf0);
  (void)CAN.sendMsgBuf(CAN_ID_AN_1, 0, 8, buf1);
}
