#include <WiFi.h>
#include <esp_now.h>

// Callback funkcija, ki se sproži ob prejemu podatkov
void onDataReceived(const uint8_t *mac, const uint8_t *incomingData, int len) {
  if (len != 2) return; // preveri dolžino sporočila

  // Združi dva bajta nazaj v celotno vrednost
  int potValue = (incomingData[0] << 8) | incomingData[1];

  // Izpiši vrednost na serijski monitor
  Serial.print("Prejeto: ");
  Serial.println(potValue);
}

void setup() {
  Serial.begin(115200);

  // Nastavi ESP32 v WiFi STA mode
  WiFi.mode(WIFI_STA);

  // Inicializacija ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Napaka pri inicializaciji ESP-NOW");
    return;
  }

  // Registracija callback funkcije za prejem podatkov
  esp_now_register_recv_cb(onDataReceived);

  Serial.println("Receiver je pripravljen");
}

void loop() {
  // Ni potrebno, vse deluje preko callback funkcije
}
