#include <Arduino.h>

#define BUTTON_PRESSED    (digitalRead(0) == LOW)
#define BUTTON_PIN        0
#define LED_PIN           2

bool ledStatus = 0;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  if(BUTTON_PRESSED) {
    digitalWrite(LED_PIN, ledStatus);
    ledStatus = !ledStatus;
  }
}