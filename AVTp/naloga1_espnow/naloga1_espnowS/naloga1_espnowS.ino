#include <esp_now.h>
#include <WiFi.h>

// pointer != množenje, len = koliko bytov prejmemo, const uint8_t = podatk tip unsigned 8bit
void onDataReceived(const uint8_t * mac, const uint8_t *incomingData, int len) {
  char macStr[18]; //Mac ima 17 + \0
  snprintf(macStr, sizeof(macStr), "%02X:%02X:%02X:%02X:%02X:%02X", //snprintf združi v str
           mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  
  Serial.print("Message from: ");
  Serial.println(macStr);
  Serial.print("Data: ");
  Serial.println((char*)incomingData);  // printa prejeti string
}

void setup() {
  Serial.begin(115200);

  // Wifi station
  WiFi.mode(WIFI_STA);

  // ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  //poklice funkcijo ko prejme sporocilo
  esp_now_register_recv_cb(onDataReceived);

  Serial.println("ESP-NOW Receiver Ready");
}

void loop() {
  // Nothing needed here — everything is handled in the callback
}
