#include "peripherals.h"
#include "config.h"

// ===================== PINOS =====================
static const uint8_t analog_pins[ANALOG_CHANNELS] = {
  A0, A1, A2, A3, A4, A5, A6, A7
};

// Pinos 0 e 1 são TX/RX da UART — usados como digitais mas sem INPUT_PULLUP
// para não interferir na linha serial durante boot/programação.
static const uint8_t digital_pins[DIGITAL_CHANNELS] = {
  3, 4, 5, 6, 7, 8, 9, 0, 1
};

void peripherals_init(void) {

  for (uint8_t i = 0; i < DIGITAL_CHANNELS; i++) {
    // Pinos 0 e 1 (TX/RX) não recebem INPUT_PULLUP para não interferir na UART
    if (digital_pins[i] == 0 || digital_pins[i] == 1) continue;
    pinMode(digital_pins[i], INPUT_PULLUP);
  }

  for (uint8_t i = 0; i < ANALOG_CHANNELS; i++) {
    pinMode(analog_pins[i], INPUT);
  }

  // Usa AREF externo de 3.0 V
  analogReference(EXTERNAL);
}

void peripherals_read_digitals(uint8_t *buffer) {

  for (uint8_t i = 0; i < DIGITAL_CHANNELS; i++) {
    buffer[i] = digitalRead(digital_pins[i]) ? 1 : 0;
  }
}

void peripherals_read_analogs(uint16_t *buffer) {

  for (uint8_t i = 0; i < ANALOG_CHANNELS; i++) {

    uint16_t adc_raw = analogRead(analog_pins[i]);

    float v_adc = ((float)adc_raw * ADC_VREF) / ADC_RESOLUTION;
    float v_in  = v_adc * DIV_GAIN;
    float v_mv  = v_in * 1000.0f;

    // Limita ao máximo de uint16_t antes de converter
    if (v_mv > 65535.0f) v_mv = 65535.0f;
    if (v_mv < 0.0f)     v_mv = 0.0f;

    buffer[i] = (uint16_t)v_mv;
  }
}
