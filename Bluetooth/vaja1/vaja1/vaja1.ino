// Vključimo knjižnice (če uporabljamo standardni analogni senzor, ni posebne knjižnice)
#include <Arduino.h>

// Pin, kamor je priključen senzor (lahko LDR ali drug analogni senzor)
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
