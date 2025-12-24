# Vaja – ESP32: Pošiljanje povprečja senzorja preko Bluetooth

## Namen vaje
Namen vaje je bil povezati dve ESP32 napravi preko **Bluetooth-a**, tako da prva
meri vrednosti senzorja, izračuna aktivno povprečje zadnjih 10 meritev in
to vrednost pošlje drugi napravi. Druga naprava deluje kot obveščevalnik
in pridobljene podatke izpiše na **serijski monitor**.

## Koncept
- **Sender ESP32** bere analogni senzor, shranjuje zadnjih 10 meritev, računa
  povprečje in pošilja vrednost preko Bluetooth Serial.  
- **Receiver ESP32** sprejema podatke preko Bluetooth Serial in jih izpiše
  na serijski monitor.  
- Bluetooth povezava omogoča prenos podatkov brez žične povezave, primeren
  za mobilne ali prenosne sisteme.

## Ključni del programa

### Sender ESP32

```cpp
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
  int trenutno = analogRead(sensorPin);
  vrednosti[indexMeritev] = trenutno;
  indexMeritev = (indexMeritev + 1) % N;

  long vsota = 0;
  for(int i = 0; i < N; i++) vsota += vrednosti[i];
  int povprecje = vsota / N;

  SerialBT.println(povprecje);
  Serial.print("Poslano povprečje: ");
  Serial.println(povprecje);

  delay(500);
}
```
### Receiver ESP32
```cpp
#include <Arduino.h>
#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_Receiver"); // ime Bluetooth naprave
  Serial.println("Receiver Bluetooth pripravljen");
}

void loop() {
  if (SerialBT.available()) {
    String prejeto = SerialBT.readStringUntil('\n');
    Serial.print("Prejeto povprecje: ");
    Serial.println(prejeto);
  }
}
```
## Ugotovitve
-Povprečje zadnjih 10 meritev omogoča zglajenje nihanj senzorja.
-Bluetooth Serial omogoča enostavno brezžično komunikacijo med dvema ESP32.
-Receiver uspešno prikazuje podatke v realnem času na serijskem monitorju.
-Ta pristop je osnova za razvoj IoT sistemov, kjer senzorji zbirajo podatke in jih pošiljajo centralni napravi ali obveščevalcu.

## Zaključek

V vaji sem uspešno povezal dve ESP32 napravi preko Bluetooth-a. Prva naprava
meri senzor in pošilja povprečne vrednosti, druga naprava pa jih sprejema in
prikazuje. Spoznal sem uporabo Bluetooth Serial knjižnice, upravljanje
krogla za povprečje in prenos podatkov v realnem času brez kabla.