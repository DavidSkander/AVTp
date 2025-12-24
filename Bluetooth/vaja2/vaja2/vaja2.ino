#include <Arduino.h>
#include "BluetoothSerial.h"

BluetoothSerial SerialBT; // inicializacija Bluetooth Serial

const int sensorPin = 34; // analogni vhod za senzor
int prejsnjaVrednost = 0;
int trenutnaVrednost = 0;
const int prag = 2;       // prag za zaznavo spremembe

void setup() {
  Serial.begin(115200);        // serijski monitor
  SerialBT.begin("ESP32_BT");  // ime Bluetooth naprave
  Serial.println("Bluetooth naprava pripravljena. Poveži se z ESP32_BT");
  pinMode(sensorPin, INPUT);
}

void loop() {
  // preberi trenutno vrednost senzorja
  trenutnaVrednost = analogRead(sensorPin);

  // preveri, ali je sprememba večja od praga
  if (abs(trenutnaVrednost - prejsnjaVrednost) > prag) {
    String msg = "Sprememba zaznana! Nova vrednost: " + String(trenutnaVrednost);
    Serial.println(msg);      // izpis na serijski monitor
    SerialBT.println(msg);    // pošlji preko Bluetooth na telefon
    prejsnjaVrednost = trenutnaVrednost; // posodobi prejšnjo vrednost
  }

  delay(100); // majhna zakasnitev
}
