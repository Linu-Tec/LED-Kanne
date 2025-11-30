void pruefenModeMenu(){
  if(ModeMenueZaehler < 1){
    ModeMenueZaehler = 8;
  }
  if(ModeMenueZaehler >= 9){
    ModeMenueZaehler = 1;
  }
}
