#include <Arduino.h>
#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_Receiver"); // ime Bluetooth naprave
  Serial.println("Receiver Bluetooth pripravljen");
}

void loop() {
  // preveri, ali so na voljo podatki
  if (SerialBT.available()) {
    String prejeto = SerialBT.readStringUntil('\n');
    Serial.print("Prejeto povprečje: ");
    Serial.println(prejeto);
  }
}
