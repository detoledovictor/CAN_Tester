#ifndef CAN_RECEIVER_H
#define CAN_RECEIVER_H

#include <Arduino.h>
#include <mcp_can.h>

// ===================== API =====================
void canReceiverInit();
void canReceiverTask();
bool canIsConnected();

#endif