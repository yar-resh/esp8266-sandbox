// This script simulates an SOS signal and allows changing the signal color via a network request

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define True 1
#define False 0

#define RED_PIN   15
#define GREEN_PIN 12
#define BLUE_PIN  13

#define RED   "red"
#define GREEN "green"
#define BLUE  "blue"

#define COOLDOWN    500
#define SHORT_BLINK 200
#define LONG_BLINK  800

byte currentLedPin = RED_PIN;

ESP8266WebServer server(80);

void changeColorHandler() {
  String ledColor = server.arg("ledColor");
  bool colorChanged = True;

  if (ledColor == RED) {
    currentLedPin = RED_PIN;
  } else if (ledColor == GREEN){
    currentLedPin = GREEN_PIN;
  } else if (ledColor == BLUE){
    currentLedPin = BLUE_PIN;
  } else {
    colorChanged = False;
  }

  if (colorChanged) {
    server.send(200, "text/plain", "LED color set to " + ledColor);
  } else {
    server.send(200, "text/plain", "No such color " + ledColor);
  }
}

void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  yield();
  
  WiFi.begin("SSID", "PASSWORD");             // set your SSID and password here
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  server.on("/change-color", changeColorHandler);  
  server.begin();
}

void loop() {
  server.handleClient();
  sos_signal();
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
