#include <Arduino.h>
#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

const int sensorPin = 34;
const int N = 10;          // število meritev za povprečje
int vrednosti[N] = {0};    // krogla za shranjevanje zadnjih N meritev
int indexMeritev = 0;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_Sender"); // ime Bluetooth naprave
  Serial.println("Sender Bluetooth pripravljen");
  pinMode(sensorPin, INPUT);
}

void loop() {
  // preberi trenutno vrednost senzorja
  int trenutno = analogRead(sensorPin);
  
  // shrani v kroglo zadnjih N meritev
  vrednosti[indexMeritev] = trenutno;
  indexMeritev = (indexMeritev + 1) % N;

  // izračunaj povprečje
  long vsota = 0;
  for(int i = 0; i < N; i++) {
    vsota += vrednosti[i];
  }
  int povprecje = vsota / N;

  // pošlji povprečje preko Bluetooth
  SerialBT.println(povprecje);
  Serial.print("Poslano povprečje: ");
  Serial.println(povprecje);

  delay(500); // meritev vsakih 0.5s
}
