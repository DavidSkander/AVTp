# Vaja 1 – Serijska komunikacija ESP32

## Namen vaje
Namen vaje je bil spoznati osnovno serijsko komunikacijo UART na ESP32
razvojni plošči ter opazovati signale na oddajnem (TX) in sprejemnem (RX)
priključku z uporabo osciloskopa.

## Uporabljena oprema
- ESP32 WROOM-DA
- Arduino IDE
- Osciloskop
- Povezovalne žice

## Program
Uporabljen je bil enostaven program, ki vsako sekundo pošlje znak `A`
preko serijskega vmesnika.

```cpp
void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print("A");
  delay(1000);
}
