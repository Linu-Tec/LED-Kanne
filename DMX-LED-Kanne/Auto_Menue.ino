// ------------Autoprogramme-------------------------------------------------------------------------

void ModeFunktion(){
  TasterAuslesen();
  if(StatusTasteUP == HIGH){
    ModeMenueZaehler++;
  }
  if(StatusTasteDOWN == HIGH){
    ModeMenueZaehler--;
  }
  pruefenModeMenu();
  ModeMenue();
  
  if(StatusTasteENTER == HIGH){   // Wenn Enter gedrückt, dann
    EEPROM.write(Adresse_10, Hauptmenuezaehler);   // Speichere Wert Hauptmenü im EEPROM
    EEPROM.write(Adresse_11, ModeMenueZaehler);   // Speichere Wert Autoprogramm im EEPROM
    #ifdef FunktionSerial
      Serial.println(Hauptmenuezaehler);
      Serial.println(ModeMenueZaehler);
    #endif
    delay(100);
  }

  switch(ModeMenueZaehler){
    case 1:
      AlleRot();
      break;
    case 2:
      AlleGruen();
      break;
    case 3:
      AlleBlau();
      break;
    case 4:
      AlleGelb();
      break;
    case 5:
      AlleTuerkis();
      break;
    case 6:
      AlleLila();
      break;
    case 7:
      AlleWeiss();
      break;
    case 8:
      AlleAus();
      break;
  }
}
