# Vaja – ESP32: Spremljanje senzorja in detekcija spremembe

## Namen vaje
Namen vaje je bil sestaviti program za ESP32, ki spremlja senzor
(osvetljenosti ali kakovosti zraka), shranjuje trenutno vrednost v
spremenljivko in poroča o **spremembi stanja**. Sprememba se sporoči le,
če je razlika med prejšnjo in trenutno vrednostjo dovolj velika, da se
izogne nenehnim manjšim nihanjem (npr. ±2).

## Koncept
ESP32 bere analogno vrednost senzorja, primerja prejšnjo in trenutno vrednost
in, če je sprememba večja od praga, izpiše sporočilo na **serijski monitor**.
Na ta način je mogoče zaznati občutne spremembe okolja brez prekomernega
izpisa podatkov.

## Ključni del programa

```cpp
#include <Arduino.h>

// Pin, kamor je priključen senzor (LDR ali senzor kakovosti zraka)
const int sensorPin = 34;

// Spremenljivke za spremljanje senzorja
int prejsnjaVrednost = 0;
int trenutnaVrednost = 0;

// Prag za zaznavo spremembe
const int prag = 2;

void setup() {
  Serial.begin(115200);        // inicializacija serijskega monitorja
  pinMode(sensorPin, INPUT);   // nastavi pin kot vhod
}

void loop() {
  // Preberi trenutno vrednost senzorja
  trenutnaVrednost = analogRead(sensorPin);

  // Preveri, ali je sprememba večja od praga
  if (abs(trenutnaVrednost - prejsnjaVrednost) > prag) {
    Serial.print("Sprememba zaznana! Nova vrednost: ");
    Serial.println(trenutnaVrednost);
    prejsnjaVrednost = trenutnaVrednost;  // osveži prejšnjo vrednost
  }

  delay(100);  // kratka zakasnitev, da ne preobremenimo serijskega monitorja
}
```
## Ugotovitve
- Program uspešno zaznava spremembe vrednosti senzorja in poroča le o
pomembnih spremembah.
- Prag preprečuje stalno nihanje in prekomerni izpis na serijski monitor.
- ESP32 omogoča enostavno spremljanje senzorjev preko analognih vhodov.
- Tak pristop je osnova za nadaljnje obdelave in pošiljanje podatkov (npr. Bluetooth, WiFi).

## Zaključek
V vaji sem izdelal program, ki spremlja senzor osvetljenosti ali kakovosti
zraka na ESP32. Spoznal sem, kako primerjati prejšnjo in trenutno vrednost
ter zaznati občutne spremembe, ki se nato izpišejo na serijski monitor.
To znanje omogoča razvoj sistemov za detekcijo sprememb v realnem času.