// This script simulates a SOS signal by alternating three colors of LEDs: red, green, and blue

#define RED_PIN   15
#define GREEN_PIN 12
#define BLUE_PIN  13

#define COOLDOWN    800
#define SHORT_BLINK 300
#define LONG_BLINK  1000

byte currentLedPin = RED_PIN;
byte ledPins[3] = {RED_PIN, GREEN_PIN, BLUE_PIN};
byte pinsNumber = 3;

void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
}

void loop() {
  for(byte i = 0; i < pinsNumber; i++) {
    currentLedPin = ledPins[i];
    sos_signal();
  }
}

void blink(byte pin, int timeout) {
  digitalWrite(pin, HIGH);
  delay(timeout);
  digitalWrite(pin, LOW);
  delay(timeout);
}

void sos_signal() {
  blink(currentLedPin, SHORT_BLINK);
  blink(currentLedPin, SHORT_BLINK);
  blink(currentLedPin, SHORT_BLINK);

  blink(currentLedPin, LONG_BLINK);
  blink(currentLedPin, LONG_BLINK);
  blink(currentLedPin, LONG_BLINK);

  blink(currentLedPin, SHORT_BLINK);
  blink(currentLedPin, SHORT_BLINK);
  blink(currentLedPin, SHORT_BLINK);

  delay(COOLDOWN);
}
