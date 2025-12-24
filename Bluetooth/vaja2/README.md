# Vaja – ESP32: Spremljanje senzorja in pošiljanje sprememb preko Bluetooth

## Namen vaje
Namen vaje je bil spoznati uporabo **Bluetooth tehnologije na ESP32** in
prilagoditi prejšnji program tako, da se ob občutni spremembi senzorja
trenutna vrednost pošlje na telefon. Cilj je bil omogočiti **real-time
prikaz sprememb** preko Bluetooth povezave.

## Koncept
ESP32 bere analogno vrednost senzorja (potenciometer, LDR ali senzor kakovosti
zraka). Če je sprememba vrednosti večja od določenega praga, se sprememba
posreduje na telefon preko **Bluetooth Serial**. Telefon mora imeti nameščeno
aplikacijo za prejem sporočil, npr. **Serial Bluetooth Terminal**.

## Ključni del programa

```cpp
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
```
## Ugotovitve
- ESP32 omogoča enostavno pošiljanje podatkov preko Bluetooth Serial.
- Prag spremembe preprečuje stalno pošiljanje sporočil zaradi manjših nihanj senzorja.
- Pošiljanje preko Bluetooth omogoča, da podatke spremljamo brez kabla, kar je uporabno za mobilne aplikacije ali prenosne sisteme.
- Aplikacija na telefonu (npr. Serial Bluetooth Terminal) uspešno sprejema in prikazuje vrednosti v realnem času.

## Zaključek
V vaji sem uspešno razširil prejšnji program tako, da ESP32 ob zaznani
občutni spremembi senzorja pošlje vrednost preko Bluetooth-a na telefon.
Spoznal sem, kako uporabiti Bluetooth Serial knjižnico na ESP32,
nastaviti ime naprave in pošiljati podatke brez žične povezave, kar
omogoča razvoj mobilnih in IoT aplikacij v realnem času.