#ifdef FunktionDMX
void DMXauslesen(){
  redLevel = DMXSerial.read(dmxBaseCh + redCh);     // Dmx Rot Wert auslesen
  grnLevel = DMXSerial.read(dmxBaseCh + grnCh);     // Dmx Grün Wert auslesen
  bluLevel = DMXSerial.read(dmxBaseCh + bluCh);     // Dmx Blau Wert auslesen
  whiteLevel = DMXSerial.read(dmxBaseCh + whiteCh);     // Dmx Blau Wert auslesen
  
  //strobe = DMXSerial.read(dmxBaseCh + strobeCh);     // Dmx Strobe Wert auslesen
  brightness = DMXSerial.read(dmxBaseCh + brightnessCh);     // Dmx Dimmer Wert auslesen
  brightness = map(brightness, 1, 255, 0, maxBrightness);   // Dimmer Wert runter rechnen

  redLevel = 255 - float(redLevel) * (float(brightness) / float(maxBrightness));    // Dimmer auf Farbe anwenden
  grnLevel = 255 - float(grnLevel) * (float(brightness) / float(maxBrightness));    // Dimmer auf Farbe anwenden
  bluLevel = 255 - float(bluLevel) * (float(brightness) / float(maxBrightness));    // Dimmer auf Farbe anwenden
  whiteLevel = 255 - float(whiteLevel) * (float(brightness) / float(maxBrightness));    // Dimmer auf Farbe anwenden
}
#endif

void DMXsteuern(){
  analogWrite(LEDred, redLevel);
  analogWrite(LEDgrn, grnLevel);
  analogWrite(LEDblu, bluLevel);
  analogWrite(LEDw, whiteLevel);
}
