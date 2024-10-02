/**
 * @brief: This program used to study how to build a library for debounce.
 * 
 * @note: For more information about debounce technique,
 *        See "Docs" folder.
 */
#include <Arduino.h>
#include "Debounce.h"

#define BUTTON_PIN    0
#define LED_PIN       2

bool ledState = LOW;
uint8_t count = 0;

Debounce button(BUTTON_PIN);  // Pin 2 for button, using default debounce delay (50 ms)

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  button.update();  // Call the update method in the loop

  if (button.isPressed()) {
    count++;
    printf("Button was pressed: %d\n", count);

    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);
  }
}
