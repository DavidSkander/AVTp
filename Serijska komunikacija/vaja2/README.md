# Vaja 2 – Serijska komunikacija med dvema Arduino mikrokrmilnikoma (SoftwareSerial)

## Namen vaje
Namen vaje je bil povezati dva Arduino mikrokrmilnika tako, da ukaz
`Serial.print()` na prvem mikrokrmilniku sproži izpis v serijskem monitorju
drugega mikrokrmilnika. Pri tem smo morali paziti, da strojna UART
priključka RX in TX ostaneta nepovezana, zato smo uporabili programsko
serijsko komunikacijo (SoftwareSerial).

## Vezava
Za programsko serijsko komunikacijo smo uporabili poljubna digitalna pina:

- Arduino 1 (oddajnik):
  - SoftwareSerial TX → Arduino 2 SoftwareSerial RX
- Arduino 2 (sprejemnik):
  - SoftwareSerial RX ← Arduino 1 SoftwareSerial TX
- Skupna masa (GND ↔ GND)

Strojna RX in TX priključka na obeh Arduino ploščah nista bila povezana.

## Program – Arduino 1 (oddajnik)
Arduino 1 pošilja podatke preko SoftwareSerial vmesnika.

```cpp
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX

void setup() {
  mySerial.begin(9600);
}

void loop() {
  mySerial.print("Pozdrav iz Arduino 1\n");
  delay(1000);
}
