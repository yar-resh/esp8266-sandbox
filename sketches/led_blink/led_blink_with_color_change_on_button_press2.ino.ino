// This script flashes an LED and changes color on button press.
// Interval between flashes depends on value read from LDR sensor

#define RED_PIN     15
#define GREEN_PIN   12
#define BLUE_PIN    13
#define BUTTON_PIN  4
#define LDR_PIN     A0

#define INTERVAL      1000
#define MIN_INTERVAL  200


byte pins[3] = {RED_PIN, GREEN_PIN, BLUE_PIN};
volatile byte currentPinIndex = 0;
int currentLdrValue = 0;
int currentInterval = INTERVAL;


IRAM_ATTR void changeColor() {
  if (currentPinIndex < 2) {
    currentPinIndex++;
  } else {
    currentPinIndex = 0;
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LDR_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), changeColor, INPUT_PULLUP);
}

void loop() {
  blink();
}

void blink() {
  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, LOW);

  currentLdrValue = analogRead(LDR_PIN);
  currentInterval = MIN_INTERVAL + currentLdrValue;

  Serial.print("LDR: " + String(currentLdrValue) + "\tInterval: " + String(currentInterval) + "\n");
  
  digitalWrite(pins[currentPinIndex], HIGH);
  delay(currentInterval);
  digitalWrite(pins[currentPinIndex], LOW);
  delay(currentInterval);
}
