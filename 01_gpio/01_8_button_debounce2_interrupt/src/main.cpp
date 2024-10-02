/**
 * @brief: This program used to study how to debounce input interrupt in Arduino.
 * 
 * 
 * @note: When writing an Interrupt Service Routine (ISR):
 *        1. Keep it as short as possible.
 *        2. Don't use delay().
 *        3. Don't use serial prints.
 *        4. Make variable shared with the main code is "volatile".
 *        5. Don't try to turn interrupts off or on. 
 */

#include <Arduino.h>

#define LED_PIN         2
#define BUTTON_PIN      0
#define DEBOUNCE_TIME   50


void xButton();

volatile bool buttonChanged = false;
volatile bool buttonStateNow = LOW;
bool buttonStatePrevSteady = LOW;

bool ledState = 0;
uint8_t count = 0;
uint32_t timePrev = 0;




void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  attachInterrupt(BUTTON_PIN, xButton, CHANGE);
}

void loop() {

  //If button change status => Save time.
  if(buttonChanged == true) {
    buttonChanged = false;   
    timePrev = millis();
  }

  //If button was in steady state
  if(millis()-timePrev > DEBOUNCE_TIME) {

    //If steady status of button have changed.
    if(buttonStateNow != buttonStatePrevSteady) {
      buttonStatePrevSteady = buttonStateNow;

      if(buttonStateNow == LOW) {
        count++;
        printf("Button was pressed: %d\n", count);

        ledState = !ledState;
        digitalWrite(LED_PIN, ledState);
      }
    }
  }
}

void xButton() {
  buttonChanged = true;
  buttonStateNow = digitalRead(BUTTON_PIN);
}