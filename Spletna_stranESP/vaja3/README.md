# Vaja – ESP32 Web Server z live prikazom senzorja

## Namen vaje
Namen vaje je bil razširiti prejšnji ESP32 Web Server, tako da se na telefonu
v realnem času prikazuje vrednost potenciometra ali senzorja. Cilj je bil
spoznati, kako lahko ESP32 bere analogne vrednosti in jih prikazuje na HTML
strani, ki se avtomatsko osvežuje.

## Koncept
ESP32 deluje kot **WiFi Access Point**, povežemo telefon nanj in odprete
IP naslov v brskalniku. Potenciometer je priključen na analogni vhod, ESP32
pa vsako sekundo posodobi prikazano vrednost na HTML strani z uporabo
meta-refresh ali JavaScript.

## Ključni del programa

```cpp
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

  pinMode(potPin, INPUT);

  WiFi.softAP(ssid, password); // ustvari Access Point
  Serial.println("Access Point ustvarjen");
  Serial.print("IP naslov: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", handleRoot); // routa "/" streže HTML stran
  server.begin();
  Serial.println("Web server zagnan");
}

void loop() {
  server.handleClient(); // obdelava HTTP zahtevkov
}
```
## Ugotovitve
- ESP32 lahko bere analogne vrednosti senzorjev (potenciometra) in jih prikazuje na telefonu.
- HTML stran se samodejno osveži vsako sekundo, prikaz pa vedno odraža trenutno vrednost.
- WiFi Access Point omogoča, da se lahko povežemo direktno na ESP32 brez dodatnega omrežja.
- Tak pristop je osnova za razvoj real-time dashboardov in IoT aplikacij.

## Zaključek
V vaji sem uspešno nadgradil ESP32 Web Server tako, da se vrednost potenciometra
v realnem času prikazuje na telefonu. Spoznal sem, kako povezati senzor,
sprejeti analogne vrednosti in jih dinamično prikazati preko HTML strani.
To znanje omogoča razvoj interaktivnih IoT aplikacij in vizualizacijo podatkov
v realnem času.