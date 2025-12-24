# Vaja – ESP32 Web Server z HTML stranjo

## Namen vaje
Namen vaje je bil izdelati enostaven **web server na ESP32**, ki streže
lastno HTML stran. Stran prikazuje različno veliko in različno postavljeno
besedilo. Cilj vaje je bil spoznati osnovno konfiguracijo ESP32 kot
Access Point in uporabo **WebServer knjižnice** za streženje HTML vsebine.

## Koncept
ESP32 deluje kot **WiFi dostopna točka**, na katero se lahko poveže telefon
ali računalnik. Po vpisu IP naslova ESP32 v brskalnik se naloži HTML stran,
ki smo jo vstavili direktno v program kot niz (string).

## Ključni del programa

```cpp
#include <WiFi.h>
#include <WebServer.h>

// Nastavitve WiFi Access Pointa
const char* ssid = "ESP32-AP";
const char* password = "12345678";

// Inicializacija web serverja na portu 80
WebServer server(80);

// HTML vsebina (vgrajena v program)
const char htmlPage[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="sl">
<head>
<meta charset="UTF-8">
<title>Moja spletna stran ESP32</title>
<style>
body { font-family: Arial, sans-serif; }
.naslov { text-align: center; font-size: 36px; }
.levo { text-align: left; font-size: 18px; }
.desno { text-align: right; font-size: 20px; }
.sredina { text-align: center; font-size: 24px; color: blue; }
.veliko { font-size: 48px; font-weight: bold; }
.majhno { font-size: 14px; color: gray; }
</style>
</head>
<body>
<h1 class="naslov">Moja enostavna spletna stran</h1>
<p class="levo veliko">To je veliko besedilo poravnano levo.</p>
<p class="sredina">To je sredinsko poravnano, moder tekst.</p>
<p class="desno majhno">To je manjše besedilo poravnano desno.</p>
<p class="levo">To je normalno besedilo z levo poravnavo.</p>
<p class="sredina veliko">To je zelo veliko besedilo na sredini.</p>
</body>
</html>
)rawliteral";

// Funkcija, ki streže HTML stran
void handleRoot() {
  server.send(200, "text/html", htmlPage);
}

void setup() {
  Serial.begin(115200);
  WiFi.softAP(ssid, password); // ustvari Access Point
  Serial.print("IP naslov ESP32: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", handleRoot); // routa "/" streže HTML stran
  server.begin(); // zaženi server
}

void loop() {
  server.handleClient(); // obdelava HTTP zahtevkov
}
```
## Ugotovitve
- ESP32 lahko deluje kot Access Point in streže spletne strani brez dodatnega WiFi omrežja.
- HTML stran je lahko vgrajena direktno v program kot C string.
- WebServer knjižnica omogoča enostavno upravljanje HTTP zahtevkov.
- Po vpisu IP naslova ESP32 v brskalnik se spletna stran pravilno prikaže na telefonu ali računalniku.

## Zaključek
V vaji sem uspešno izdelal ESP32 Web Server, ki streže lastno HTML stran
z različno velikim in postavljenim besedilom. Spoznal sem, kako ustvariti
dostopno točko, uporabiti WebServer knjižnico in vgrajevati HTML direktno
v program. To znanje omogoča nadaljnje razvojne projekte in interaktivne
spletne aplikacije na ESP32.