#include <Arduino.h>
#include <Debounce.h>

#define BUTTON_PIN    0
#define LED_PIN       2

uint8_t count = 0;
bool ledState = LOW;

Debounce button(BUTTON_PIN);

void setup() {
  pinMode(LED_PIN, OUTPUT);
  button.begin();
}

void loop() {
  button.update();

  if (button.isPressed()) {
    count++;
    printf("Button Pressed: %d\n", count);

    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);
  }
}



