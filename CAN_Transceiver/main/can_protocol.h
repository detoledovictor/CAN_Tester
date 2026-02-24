#ifndef CAN_PROTOCOL_H
#define CAN_PROTOCOL_H

/*

DIGITAL INPUTS
---------------------------------------
ID 0x100
Byte 0..6 : D0..D6 (0 ou 1)

ID 0x101
Byte 0 : D7
Byte 1 : D8


ANALOG INPUTS (VALOR REAL EM mV)
---------------------------------------
ID 0x200
Byte 0-1 : A0 (uint16_t, mV)
Byte 2-3 : A1
Byte 4-5 : A2
Byte 6-7 : A3

ID 0x201
Byte 0-1 : A4
Byte 2-3 : A5
Byte 4-5 : A6
Byte 6-7 : A7
*/

#define CAN_ID_DIG_0  0x100
#define CAN_ID_DIG_1  0x101
#define CAN_ID_AN_0   0x200
#define CAN_ID_AN_1   0x201

#endif