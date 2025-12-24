# Vaja 3 – Tipkovnica in realnočasovna komunikacija

## Namen vaje
Namen vaje je bil izdelati enostavno tipkovnico s tremi tipkami, kjer ima
vsaka tipka svojo črko, ter tipko za pošiljanje sporočila. Sestavljeno
sporočilo smo poslali drugemu mikrokrmilniku in omogočili realnočasovno
dvosmerno komunikacijo.

## Opis delovanja
Vsak mikrokrmilnik ima tri tipke za vnos znakov in eno tipko za pošiljanje.
Ob pritisku na tipko se ustrezna črka doda v sporočilo. Ko uporabnik pritisne
tipko za pošiljanje, se sporočilo pošlje drugemu mikrokrmilniku.

Oba mikrokrmilnika hkrati sprejemata in pošiljata podatke ter izpisujeta
prejeta sporočila v serijski monitor.

## Ključni deli programa

### Vnos znakov s tipkami
Ob pritisku tipke se znak doda v niz, ki predstavlja sporočilo:
```cpp
if (digitalRead(tipkaA) == LOW) {
  sporocilo += "A";
}
``` 
##Pošiljanje sporočila
Sporočilo se pošlje ob pritisku tipke za pošiljanje:

``` cpp
mySerial.println(sporocilo);
sporocilo = "";
```
##Sprejem podatkov v realnem času
Mikrokrmilnik sproti preverja, ali so na voljo podatki za sprejem:

```cpp
if (mySerial.available()) {
  Serial.write(mySerial.read());
}
```
##Ugotovitve
Tipke omogočajo enostaven vnos znakov

Programska serijska komunikacija omogoča dvosmerni prenos

Mikrokrmilnika lahko delujeta hkrati brez čakanja drug na drugega

## Zaključek
V vaji smo uspešno izdelali preprosto tipkovnico in omogočili realnočasovno

komunikacijo med dvema mikrokrmilnikoma.
