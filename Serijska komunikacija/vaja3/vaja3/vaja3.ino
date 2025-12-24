#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX

const int tipkaA = 4;
const int tipkaB = 5;
const int tipkaC = 6;
const int tipkaSend = 7;

String sporocilo = "";

void setup() {
  pinMode(tipkaA, INPUT_PULLUP);
  pinMode(tipkaB, INPUT_PULLUP);
  pinMode(tipkaC, INPUT_PULLUP);
  pinMode(tipkaSend, INPUT_PULLUP);

  Serial.begin(9600);
  mySerial.begin(9600);
}

void loop() {
  // Branje tipk
  if (digitalRead(tipkaA) == LOW) {
    sporocilo += "A";
    delay(200);
  }

  if (digitalRead(tipkaB) == LOW) {
    sporocilo += "B";
    delay(200);
  }

  if (digitalRead(tipkaC) == LOW) {
    sporocilo += "C";
    delay(200);
  }

  // Pošiljanje sporočila
  if (digitalRead(tipkaSend) == LOW) {
    mySerial.println(sporocilo);
    sporocilo = "";
    delay(300);
  }

  // Sprejem podatkov v realnem času
  if (mySerial.available()) {
    Serial.write(mySerial.read());
  }
}
