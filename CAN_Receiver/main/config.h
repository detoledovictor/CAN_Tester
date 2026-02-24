#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// ===================== CAN HARDWARE =====================
#define CAN_INT_PIN 2
#define CAN_CS_PIN  10

// ===================== CAN TIMING =====================
#define CAN_BAUDRATE CAN_500KBPS
#define CAN_CLOCK    MCP_16MHZ

// ===================== CONEXÃO =====================
#define CONNECTION_TIMEOUT 3000   // ms
#define CAN_STATUS_PERIOD  1000   // ms

#endif