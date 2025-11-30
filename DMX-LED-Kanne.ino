#include <DMXSerial.h>

// DMX Kanalzuordnung (leicht oben änderbar)
const int DMX_RED     = 5; // DMX Kanal für Rot
const int DMX_GREEN   = 6; // DMX Kanal für Grün
const int DMX_BLUE    = 7; // DMX Kanal für Blau
const int DMX_WHITE   = 8; // DMX Kanal für Weiß
const int DMX_DIMMER  = 4; // DMX Kanal für Master-Dimmer

// LED Pins
const int LEDred = 3;
const int LEDgrn = 5;
const int LEDblu = 6;
const int LEDw   = 9;

// Default-Werte für "LEDs aus" (invertiert: 255 = aus)
const int RedDefaultLevel   = 255;
const int GreenDefaultLevel = 255;
const int BlueDefaultLevel  = 255;
const int WhiteDefaultLevel = 255;

void setup() {
  pinMode(LEDred, OUTPUT);
  pinMode(LEDgrn, OUTPUT);
  pinMode(LEDblu, OUTPUT);
  pinMode(LEDw, OUTPUT);

  DMXSerial.init(DMXReceiver);
}

void loop() {
  // Millisekunden seit letztem DMX-Paket
  unsigned long lastPacket = DMXSerial.noDataSince();

  if (lastPacket < 500) {  // <--- Zeit einfach anpassen!
    // DMX Werte auslesen
    int redValue   = DMXSerial.read(DMX_RED);
    int grnValue   = DMXSerial.read(DMX_GREEN);
    int bluValue   = DMXSerial.read(DMX_BLUE);
    int wValue     = DMXSerial.read(DMX_WHITE);
    int dimmer     = DMXSerial.read(DMX_DIMMER);

    float dimFactor = dimmer / 255.0;

    // Werte dimmen und invertieren
    analogWrite(LEDred, 255 - int(redValue * dimFactor));
    analogWrite(LEDgrn, 255 - int(grnValue * dimFactor));
    analogWrite(LEDblu, 255 - int(bluValue * dimFactor));
    analogWrite(LEDw,   255 - int(wValue   * dimFactor));
  } else {
    // Kein DMX: Alle LEDs aus
    analogWrite(LEDred,   RedDefaultLevel);
    analogWrite(LEDgrn,   GreenDefaultLevel);
    analogWrite(LEDblu,   BlueDefaultLevel);
    analogWrite(LEDw,     WhiteDefaultLevel);
  }
}
