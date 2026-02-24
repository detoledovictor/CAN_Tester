#ifndef CAN_DRV_H
#define CAN_DRV_H

#include <Arduino.h>
#include <mcp_can.h>

void can_init(void);
void can_send_digitals(uint8_t *dig);
void can_send_analogs(uint16_t *ana);

#endif