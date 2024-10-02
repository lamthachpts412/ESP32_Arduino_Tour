/**
 * @brief: This program used to study how to debounce button in Arduino.
 * 
 * 
 * @note: This program got an error.
 *        Because sometime it detect 2 falling edge continuously.
 */

#include <Arduino.h>

#define LED_PIN         2
#define BUTTON_PIN      0
#define DEBOUNCE_TIME   50


void xButton();

volatile bool buttonChanged = false;
volatile bool buttonStateNow = LOW;

bool ledState = 0;
uint8_t count = 0;
uint32_t timePrev = 0;


void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  attachInterrupt(BUTTON_PIN, xButton, CHANGE);
}

void loop() {
  if(buttonChanged == true) {
    buttonChanged = false;
    
    printf("[%d]\n", buttonStateNow);
    if((buttonStateNow == LOW) && (millis()-timePrev > DEBOUNCE_TIME)) {
      
      printf("[%d] ", millis()-timePrev);

      count++;
      printf("Button was pressed: %d\n", count);

      ledState = !ledState;
      digitalWrite(LED_PIN, ledState);
    }

    timePrev = millis();
    attachInterrupt(BUTTON_PIN, xButton, CHANGE);
  }

}

void xButton() {
  buttonChanged = true;
  buttonStateNow = digitalRead(BUTTON_PIN);

  detachInterrupt(BUTTON_PIN);
}