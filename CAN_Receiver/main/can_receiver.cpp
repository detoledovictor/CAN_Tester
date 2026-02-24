#include "can_receiver.h"
#include "config.h"
#include "can_protocol.h"

// ===================== CAN =====================
static MCP_CAN CAN(CAN_CS_PIN);

// ===================== BUFFERS =====================
static uint8_t digitalValue[9];
static uint16_t analogValue[8];

// ===================== CONTROLE =====================
static bool canConnected = false;
static unsigned long lastMsg = 0;
static unsigned long lastPrint = 0;

static bool an0_valid = false;
static bool an1_valid = false;

// ===================== INTERNOS =====================
static void processCanFrame(uint32_t id, uint8_t len, uint8_t *buf);
static void printData();

// ===================== INIT =====================
void canReceiverInit() {

  while (CAN.begin(MCP_ANY, CAN_BAUDRATE, CAN_CLOCK) != CAN_OK) {
    Serial.println("[CAN] Falha ao inicializar...");
    delay(500);
  }

  Serial.println("[CAN] Inicializado");
  CAN.setMode(MCP_NORMAL);

  pinMode(CAN_INT_PIN, INPUT_PULLUP);

  for (uint8_t i = 0; i < 9; i++) digitalValue[i] = 0;
  for (uint8_t i = 0; i < 8; i++) analogValue[i] = 0;
}

// ===================== TASK =====================
void canReceiverTask() {
  unsigned long now = millis();

  if (now - lastMsg > CONNECTION_TIMEOUT) canConnected = false;

  if (!canConnected && now - lastPrint > CAN_STATUS_PERIOD) {
    lastPrint = now;
    Serial.println("[CAN] ...");
  }

  if (digitalRead(CAN_INT_PIN) == LOW && CAN.checkReceive() == CAN_MSGAVAIL) {

    long unsigned int rxId;
    unsigned char rxLen;
    unsigned char rxBuf[8];

    CAN.readMsgBuf(&rxId, &rxLen, rxBuf);

    if (!canConnected) {
      Serial.println("[CAN] Conectado");
      canConnected = true;
    }

    lastMsg = millis();

    processCanFrame(rxId, rxLen, rxBuf);
  }
}

// ===================== STATUS =====================
bool canIsConnected() {
  return canConnected;
}

// ===================== PROCESSAMENTO =====================
static void processCanFrame(uint32_t rxId, uint8_t rxLen, uint8_t *rxBuf) {

  switch (rxId) {

    case CAN_ID_DIG_0:
      if (rxLen >= 7) {
        for (uint8_t i = 0; i < 7; i++) {
          digitalValue[i] = rxBuf[i] ? 1 : 0;
        }
      }
      break;

    case CAN_ID_DIG_1:
      if (rxLen >= 2) {
        digitalValue[7] = rxBuf[0] ? 1 : 0;
        digitalValue[8] = rxBuf[1] ? 1 : 0;
      }
      break;

    case CAN_ID_AN_0:
      if (rxLen >= 8) {
        for (uint8_t i = 0; i < 4; i++) {
          analogValue[i] =
            (rxBuf[i * 2] << 8) | rxBuf[i * 2 + 1];
        }
        an0_valid = true;
      }
      break;

    case CAN_ID_AN_1:
      if (rxLen >= 8) {
        for (uint8_t i = 0; i < 4; i++) {
          analogValue[i + 4] =
            (rxBuf[i * 2] << 8) | rxBuf[i * 2 + 1];
        }
        an1_valid = true;
      }

      if (an0_valid && an1_valid) {
        printData();
        an0_valid = false;
        an1_valid = false;
      }
      break;
  }
}

// ===================== PRINT =====================
static void printData() {

  Serial.println("==============================");

  Serial.print("Digitais: ");
  for (uint8_t i = 0; i < 9; i++) {
    Serial.print("D");
    Serial.print(i);
    Serial.print("=");
    Serial.print(digitalValue[i]);
    if (i < 8) Serial.print(" | ");
  }
  Serial.println();

  Serial.print("Analogicas: ");
  for (uint8_t i = 0; i < 8; i++) {
    Serial.print("A");
    Serial.print(i);
    Serial.print(": ");
    Serial.print(analogValue[i]);
    Serial.print(" mV");
    if (i < 7) Serial.print(" | ");
  }

  Serial.println();
  Serial.println("==============================\n");
}