#include <WiFi.h>
#include <esp_now.h>

// Callback funkcija ob prejemu sporočila
void onDataReceived(const uint8_t *mac, const uint8_t *incomingData, int len) {
  // Pretvori bajte v String
  String message = "";
  for (int i = 0; i < len; i++) {
    message += (char)incomingData[i];
  }

  // Izpis prejetega sporočila
  Serial.print("Prejeto sporočilo: ");
  Serial.println(message);
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Napaka pri inicializaciji ESP-NOW");
    return;
  }

  esp_now_register_recv_cb(onDataReceived);

  Serial.println("Receiver pripravljen");
}

void loop() {
  // Nič ne rabimo sem, vse dela callback
}
