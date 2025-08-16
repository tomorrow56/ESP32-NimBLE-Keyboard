#include "BleConnectionStatus.h"

BleConnectionStatus::BleConnectionStatus(void) {
}

void BleConnectionStatus::onConnect(NimBLEServer* pServer)
{
  this->connected = true;
  Serial.println("BLE Device Connected!");
}

void BleConnectionStatus::onDisconnect(NimBLEServer* pServer)
{
  this->connected = false;
  Serial.println("BLE Device Disconnected!");
}
