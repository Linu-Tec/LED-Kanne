void TasterAuslesen(){
  /*unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= 100) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;*/
  
    StatusTasteUP = !digitalRead(TasteUP);
    StatusTasteDOWN = !digitalRead(TasteDOWN);
    StatusTasteMODE = !digitalRead(TasteMODE);
    StatusTasteENTER = !digitalRead(TasteENTER);
    
    #ifdef FunktionSerial
      Serial.print("UP"); Serial.print("\t");
      Serial.print("DOWN"); Serial.print("\t");
      Serial.print("MODE"); Serial.print("\t");
      Serial.print("Enter"); Serial.println("\t");
      Serial.print(StatusTasteUP); Serial.print("\t");
      Serial.print(StatusTasteDOWN); Serial.print("\t");
      Serial.print(StatusTasteMODE); Serial.print("\t");
      Serial.print(StatusTasteENTER); Serial.println("\t");
    #endif
    
    delay(100);
  //}
}

// -------------------------------------------------------------------------------------

void TasterAuslesenDMXModus(){
  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= 50) {
    previousMillis = currentMillis;
  
    StatusTasteMODE = !digitalRead(TasteMODE);
    StatusTasteENTER = !digitalRead(TasteENTER);

    #ifdef FunktionSerial
      Serial.println(StatusTasteMODE);
      Serial.println(StatusTasteENTER);
    #endif
  }
}
