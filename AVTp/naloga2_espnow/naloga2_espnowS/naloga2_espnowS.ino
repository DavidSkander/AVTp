#include <WiFi.h>
#include <esp_now.h>

#define POT_PIN 34  // analogni pin, kamor je priključen potenciometer

// MAC naslov receiverja (zamenjajte z MAC naslovom vašega Receiverja)
uint8_t receiverMAC[] = {0x24, 0x6F, 0x28, 0xAB, 0xCD, 0xEF};

void setup() {
  Serial.begin(115200);

  // Nastavi ESP32 v WiFi STA mode
  WiFi.mode(WIFI_STA);

  // Inicializacija ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Napaka pri inicializaciji ESP-NOW");
    return;
  }

  // Nastavitev peer naprave (Receiver)
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, receiverMAC, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Napaka pri dodajanju peer naprave");
    return;
  }

  Serial.println("Sender je pripravljen");
}

void loop() {
  // Preberi analogno vrednost potenciometra (0-4095)
  int potValue = analogRead(POT_PIN);

  // Pretvori vrednost v bajte
  uint8_t data[2];
  data[0] = potValue >> 8;    // višji bajt
  data[1] = potValue & 0xFF;  // nižji bajt

  // Pošlji podatke Receiverju
  esp_err_t result = esp_now_send(receiverMAC, data, 2);
  if (result == ESP_OK) {
    Serial.print("Poslano: ");
    Serial.println(potValue);
  } else {
    Serial.println("Napaka pri pošiljanju");
  }

  delay(500); // pošlji vsaki pol sekunde
}

