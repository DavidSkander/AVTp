# Vaja 3: ESP-NOW – Pošiljanje besedila iz Serial Monitorja

## Namen vaje
Cilj vaje je prebrati vnos iz Serial Monitorja z uporabo `Serial.read()` in ga poslati drugi ESP32 napravi preko ESP-NOW protokola.

---

## Uporabljene knjižnice
- `WiFi.h` – omogoča dostop do WiFi radia (za ESP-NOW)
- `esp_now.h` – omogoča komunikacijo ESP-NOW

---

## Opis delovanja

### Sender:
- Uporabnik vpiše besedilo v Serial Monitor in pritisne **Send**.
- ESP32 znak za znakom bere vhod preko `Serial.read()`.
- Ko zazna znak `\n` (Enter), pošlje celoten vnos drugi ESP32 napravi.
- Pošiljanje poteka v obliki niza bajtov (uint8_t*).

### Receiver:
- Prejme niz bajtov preko callback funkcije `onDataReceived`.
- Pretvori bajte nazaj v String.
- Prikaže prejeto sporočilo na serijskem monitorju.

---

## Ključni del kode

### Branje iz Serial Monitorja
```cpp
char c = Serial.read();
if (c == '\n') {
    esp_now_send(receiverMAC, (uint8_t*)inputString.c_str(), inputString.length());
}

## Pretvorba bajtov nazaj v String
String message = "";
for (int i = 0; i < len; i++) {
  message += (char)incomingData[i];
}
```
## Ugotovitve
- Serial.read() bere en znak naenkrat, zato moramo sami sestaviti celoten String.
- ESP-NOW zahteva pošiljanje podatkov kot array bajtov, zato uporabimo c_str().
- Callback funkcije omogočajo, da se prejem podatkov obdeluje brez zasedanja loop().
- Prenos deluje stabilno in hitro tudi brez WiFi omrežja.



