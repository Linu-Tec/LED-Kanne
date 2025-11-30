int LEDred = 5;
int LEDgrn = 6;
int LEDblu = 9;
int LEDw   = 10;

void setup() {
  pinMode(LEDred, OUTPUT);
  pinMode(LEDgrn, OUTPUT);
  pinMode(LEDblu, OUTPUT);
  pinMode(LEDw, OUTPUT);

  analogWrite(LEDred, 255);
  analogWrite(LEDgrn, 255);
  analogWrite(LEDblu, 255);
  analogWrite(LEDw, 255);
}

void loop() {
  dimLed(LEDred);
  delay(500);
  dimLed(LEDgrn);
  delay(500);
  dimLed(LEDblu);
  delay(500);
  dimLed(LEDw);
  delay(500);
}

void dimLed(int pin) {
  // Hoch dimmen (invertiert)
  for (int i = 0; i <= 255; i++) {
    analogWrite(pin, 255 - i);
    delay(25);
  }
  // Runter dimmen (invertiert)
  for (int i = 255; i >= 0; i--) {
    analogWrite(pin, 255 - i);
    delay(25);
  }
}
