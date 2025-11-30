//#define FunktionLED
#define FunktionSound
#define FunktionDMX
//#define FunktionSerial    // Wenn Aktiviert, FunktionDMX Deaktivieren
//#define EEPROMschreiben
//#define FunktionPoti    // Wenn Aktiviert, FunktionLED Aktivieren


// ------------------Arduino-----------------------

//#define ArduinoUno
//#define ArduinoNano
#define AdruinoNanoV2

#if defined(ArduinoUno)
  #define LEDWS2812b 13
  #define DMXmodePin 2
  #define TM1637CLK 11
  #define TM1637Dio 10
  #define TASTEup 4
  #define TASTEdown 5
  #define TASTEmode 6
  #define TASTEenter 7
  #define SOUNDdigital 8
  #define SOUNDanalog A0
  
#elif defined(ArduinoNano)
  #define LEDWS2812b 13
  #define DMXmodePin 2
  #define TM1637CLK 11
  #define TM1637Dio 10
  #define TASTEup 4
  #define TASTEdown 5
  #define TASTEmode 6
  #define TASTEenter 7
  #define SOUNDdigital 8
  #define SOUNDanalog A0
  
#elif defined(AdruinoNanoV2)
  #define LEDWS2812b 13
  #define DMXmodePin 2
  #define TM1637CLK 7
  #define TM1637Dio 8
  #define TASTEup 2
  #define TASTEdown 4
  #define TASTEmode 11
  #define TASTEenter 12
  #define LEDPWMrot 3
  #define LEDPWMgruen 5
  #define LEDPWMblau 6
  #define LEDPWMweiss 9
  #define SOUNDdigital A1
  #define SOUNDanalog A0
  
#else
  #error "Kein gültiger Controller ausgewählt!"
#endif


// ------------------library-----------------------
#include <Arduino.h>

// ------------------DMX-Werte-----------------------

byte maxBrightness     = 250;    // brightness range [off..on] = [0..255], keep dim for less current draw
volatile byte brightness,
     strobe,
     effect,
     effectspeed,
     redLevel,  // store the received channel level control data
     grnLevel,
     bluLevel,
     whiteLevel;

volatile byte Prevbrightness = 0,
     PrevRedLevel = 0,
     PrevGreenLevel = 0,
     PrevBlueLevel = 0,
     PrevWhiteLevel = 0;

// ------------------DMX-Channel-----------------------

byte brightnessCh      =   3,   // DMX channel offsets from base channel
     strobeCh          =   1,
     effectCh          =   2,
     effectspeedCh     =   3,
     redCh             =   4,   
     grnCh             =   5,
     bluCh             =   6,
     whiteCh           =   7;

// ------------------LED-----------------------
// LED Pins
const int LEDred = LEDPWMrot;
const int LEDgrn = LEDPWMgruen;
const int LEDblu = LEDPWMblau;
const int LEDw   = LEDPWMweiss;

// ------------------DMXSerial-----------------------

#ifdef FunktionDMX
  #include <DMXSerial.h>
  
  #define DMXMODEPIN DMXmodePin
  extern DMXSerialClass DMXSerial;
#endif



// ------------------TM1637Display-----------------------
#include <TM1637Display.h>
// Module connection pins (Digital Pins)
TM1637Display display(TM1637CLK, TM1637Dio); // CLK, DIO

const uint8_t d[] = {SEG_B | SEG_C | SEG_D | SEG_E | SEG_G};
const uint8_t A[] = {SEG_A | SEG_B | SEG_C | SEG_E | SEG_F | SEG_G};
const uint8_t C[] = {SEG_A | SEG_D | SEG_E | SEG_F };
const uint8_t Sound[] = {SEG_A | SEG_C | SEG_D | SEG_F | SEG_G,
                         SEG_C | SEG_D | SEG_E | SEG_G,
                         SEG_C | SEG_D | SEG_E,
                         SEG_B | SEG_C | SEG_D | SEG_E | SEG_G};
const uint8_t Bindestrich[] = {SEG_G,
                               SEG_G,
                               SEG_G,
                               SEG_G};

// ------------------EEPROM-----------------------
#include <EEPROM.h>
int Adresse_0 = 0,    // Speicher DMX-Adresse
    Adresse_1 = 1,
    Adresse_2 = 2,
    Adresse_3 = 3,
    Adresse_4 = 4,
    Adresse_5 = 5,
    Adresse_6 = 6,
    Adresse_7 = 7,
    Adresse_8 = 8,
    Adresse_9 = 9,    // Speicher DMX-Adresse
    Adresse_10 = 10,    // Speicher Hauptmenü DMX-Modus oder Autoprogramm
    Adresse_11 = 11,    // Speicher Autoprogramm
    Adresse_12 = 12;    // Speicher Channel Auswahl

// ------------------Taster-----------------------
int TasteUP = 2,    // Pin vom Taster
    StatusTasteUP,    // Zustand vom Taster
    TasteDOWN = 4,
    StatusTasteDOWN,
    TasteMODE = 11,
    StatusTasteMODE,
    TasteENTER = 12,
    StatusTasteENTER;

// Zeit für Taster
unsigned long previousMillis = 0;

// ------------------Variabeln-----------------------
int dmxBaseCh,    // DMX-Adresse
    stelle,
    MODE = 0,
    ModeMenueZaehler,    // EEprom letzter Zustand
    Hauptmenuezaehler,    // EEprom letzter Zustand
    Hauptmenue,
    chanel_nummer,    // Wert kommt aus/wird berechnet aus dem EEPROM
    Speicher_Channel;

// Zwischenspeicher Hauptmenü Funktion (in welcher Funktion er ist)
int DMX_Modus_Nix,
    DMX_Adresse_einstellen,
    Channel_einstellen,
    Autoprogramme;


// ------------------------------------Setup-----------------------------------------
void setup() {
  #ifdef EEPROMschreiben
    EEPROMschreibenErstesMal();
  #endif
  
  #ifdef FunktionSerial
    Serial.begin(9600);
  #endif
  
  // ------------------LED-----------------------
  pinMode(LEDred, OUTPUT);
  pinMode(LEDgrn, OUTPUT);
  pinMode(LEDblu, OUTPUT);
  pinMode(LEDw, OUTPUT);

  // ------------------DMX-----------------------
  #ifdef FunktionDMX
    DMXSerial.init(DMXReceiver);  // Pin 2
    //_DMX_setMode(RDATA);
  #endif

  // ------------------Taster-----------------------
  pinMode(TasteUP, INPUT_PULLUP);
  pinMode(TasteDOWN, INPUT_PULLUP);
  pinMode(TasteMODE, INPUT_PULLUP);
  pinMode(TasteENTER, INPUT_PULLUP);

  // ------------------Display-----------------------
  display.setBrightness(0x0f);

  // ------------------EEPROM-----------------------
  eepromauslesen();

  // Werte aus dem EEPROM lesen
  Hauptmenuezaehler = EEPROM.read(Adresse_10);
  ModeMenueZaehler = EEPROM.read(Adresse_11);
  Speicher_Channel = EEPROM.read(Adresse_12);

}

// ------------------------------------Loop-----------------------------------------
void loop() {
  HauptMenu();
}
