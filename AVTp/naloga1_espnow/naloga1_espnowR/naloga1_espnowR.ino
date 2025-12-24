#include <WiFi.h>
#include <esp_now.h>

// MAC naslov receiver ESP32
uint8_t receiverMAC[] = {0x24, 0x6F, 0x28, 0xAB, 0xCD, 0xEF}; //MAC naslovom receiverja

// Podatki za pošiljanje
const char* message = "Hello ESP-NOW";

void setup() {
  Serial.begin(115200);

  
  WiFi.mode(WIFI_STA);

 
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, receiverMAC, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }

  Serial.println("ESP-NOW Sender Ready");
}

void loop() {
  // Pošlji sporočilo receiverju
  esp_err_t result = esp_now_send(receiverMAC, (uint8_t *)message, strlen(message));
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  } else {
    Serial.println("Error sending message");
  }

  delay(2000); // pošlji vsaki 2 sekundi
}
