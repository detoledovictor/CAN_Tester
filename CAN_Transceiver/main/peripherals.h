#ifndef PERIPHERALS_H
#define PERIPHERALS_H

#include <Arduino.h>

#define ANALOG_CHANNELS   8
#define DIGITAL_CHANNELS  9

void peripherals_init(void);
void peripherals_read_digitals(uint8_t *buffer);
void peripherals_read_analogs(uint16_t *buffer);

#endif