#include <WiFi.h>
#include <ESPAsyncWebServer.h>

const char *ssid = "ESP32_NetworkManager"; 
const char *password = "87654321";

AsyncWebServer server(80);

uint32_t requestCount = 0;

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta charset="UTF-8">
  <title>ESP32 Router Control</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    body { font-family: sans-serif; text-align: center; background: #f0f2f5; }
    .card { background: white; padding: 20px; margin: 20px auto; width: 80vw; border-radius: 10px; box-shadow: 0 4px 8px rgba(0,0,0,0.1); }
    h2 { color: #1a73e8; }
    .stat { font-size: 1.2rem; margin: 10px; }
  </style>
</head>
<body>
  <div class="card">
    <h2>ESP32 Nadzorna plošča omrežja</h2>
    <div class="stat">IP naslov routerja: <strong>%MY_IP%</strong></div>
    <div class="stat">Število povezanih naprav: <strong style="color:red;">%CLIENTS%</strong></div>
    <div class="stat">Zabeležen promet (HTTP zahtev): <strong>%TRAFFIC%</strong></div>
    <hr>
    <p>Osveži stran za posodobitev podatkov.</p>
  </div>
</body>
</html>)rawliteral";

String processor(const String& var){
  if(var == "MY_IP") return WiFi.softAPIP().toString();
  if(var == "CLIENTS") return String(WiFi.softAPgetStationNum());
  if(var == "TRAFFIC") return String(requestCount);
  return String();
}

void setup() {
  Serial.begin(115200);

  WiFi.softAP(ssid, password);
  Serial.print("Access Point IP: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    requestCount++;
    request->send_P(200, "text/html", index_html, processor);
  });

  server.begin();
}

void loop() {
  static unsigned long lastLog = 0;
  if (millis() - lastLog > 10000) {
    Serial.printf("Razmere v omrežju: Naprav: %d, Zahtev: %u\n", 
                  WiFi.softAPgetStationNum(), requestCount);
    lastLog = millis();
  }
}