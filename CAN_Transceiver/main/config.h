#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// ===================== ADC =====================
// 1024.0 garante escala linear correta: 0 -> 0 V, 1023 -> (1023/1024)*VREF
#define ADC_RESOLUTION   1024.0
#define ADC_VREF         3.0     // AREF externo (V)

// ===================== DIVISOR RESISTIVO =====================
#define DIV_R_TOP        39000.0
#define DIV_R_BOTTOM     15000.0
#define DIV_GAIN ((DIV_R_TOP + DIV_R_BOTTOM) / DIV_R_BOTTOM)

// ===================== CAN =====================
#define CAN_INT_PIN      2
#define CAN_CS_PIN       10

// ===================== TIMING =====================
#define CAN_TX_PERIOD_MS 1000UL

#endif
