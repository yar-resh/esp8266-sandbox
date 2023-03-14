// This script flashes an LED and changes color on button press

#define RED_PIN     15
#define GREEN_PIN   12
#define BLUE_PIN    13
#define BUTTON_PIN  4

#define INTERVAL    500


byte pins[3] = {RED_PIN, GREEN_PIN, BLUE_PIN};
volatile byte currentPinIndex = 0;

IRAM_ATTR void changeColor() {
  if (currentPinIndex < 2) {
    currentPinIndex++;
  } else {
    currentPinIndex = 0;
  }
}

void setup() {
  // Serial.begin(115200);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), changeColor, INPUT_PULLUP);
}

void loop() {
  blink();
}

void blink() {
  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, LOW);
  
  digitalWrite(pins[currentPinIndex], HIGH);
  delay(INTERVAL);
  digitalWrite(pins[currentPinIndex], LOW);
  delay(INTERVAL);
}
