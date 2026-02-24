#ifndef CAN_PROTOCOL_H
#define CAN_PROTOCOL_H

#include <Arduino.h>

// ===================== IDs CAN =====================
enum CanId : uint32_t {
  CAN_ID_DIG_0 = 0x100, // Digitais D0–D6
  CAN_ID_DIG_1 = 0x101, // Digitais D7–D8
  CAN_ID_AN_0  = 0x200, // Analógicas A0–A3 [mV]
  CAN_ID_AN_1  = 0x201  // Analógicas A4–A7 [mV]
};

/*
CAN_ID_DIG_0
Byte 0–6: D0–D6 (0 ou 1)

CAN_ID_DIG_1
Byte 0–1: D7–D8 (0 ou 1)

CAN_ID_AN_0
Byte 0–1: A0 [mV]
Byte 2–3: A1 [mV]
Byte 4–5: A2 [mV]
Byte 6–7: A3 [mV]

CAN_ID_AN_1
Byte 0–1: A4 [mV]
Byte 2–3: A5 [mV]
Byte 4–5: A6 [mV]
Byte 6–7: A7 [mV]
*/

#endif