#include "config.h"
#include "can_receiver.h"

void setup() {
  Serial.begin(115200);
  canReceiverInit();
}

void loop() {
  canReceiverTask();
}