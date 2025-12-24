#include <WiFi.h>
#include <WebServer.h>

// Nastavitve WiFi Access Pointa
const char* ssid = "ESP32-AP";
const char* password = "12345678";

// Inicializacija web serverja na portu 80
WebServer server(80);

// Pin, kjer je priključen potenciometer
const int potPin = 34; // analogni vhod na ESP32

// Funkcija, ki generira HTML stran z aktualno vrednostjo
String generateHTML(int value) {
  String html = "<!DOCTYPE html><html lang='sl'><head><meta charset='UTF-8'>";
  html += "<title>ESP32 - vrednost potenciometra</title>";
  html += "<meta http-equiv='refresh' content='1'>"; // osvežitev vsako sekundo
  html += "<style>body { font-family: Arial; text-align:center; margin-top:50px; }";
  html += "h1 { font-size:36px; } p { font-size:24px; }</style></head><body>";
  html += "<h1>Vrednost potenciometra</h1>";
  html += "<p>" + String(value) + "</p>";
  html += "</body></html>";
  return html;
}

// Funkcija, ki streže HTML stran
void handleRoot() {
  int potValue = analogRead(potPin); // preberi analogno vrednost
  String html = generateHTML(potValue);
  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);

  // Nastavi pin za potenciometer
  pinMode(potPin, INPUT);

  // Ustvari WiFi Access Point
  WiFi.softAP(ssid, password);
  Serial.println("Access Point ustvarjen");
  Serial.print("IP naslov: ");
  Serial.println(WiFi.softAPIP());

  // Nastavi routo "/" za streženje HTML
  server.on("/", handleRoot);

  // Zaženi server
  server.begin();
  Serial.println("Web server zagnan");
}

void loop() {
  server.handleClient(); // obdelava HTTP zahtevkov
}

