/**
 * @brief: This program used to study how to debounce button.
 * 
 * @note: This program use debounce technique 
 *        identical example code of Arduino.
 *        You can read the artical at: 
 *        https://docs.arduino.cc/built-in-examples/digital/Debounce/
 * 
 *        For more detail about this debounce technique,
 *        see "Docs" folder.
 */

#include <Arduino.h>

#define DEBOUNCE_TIME   50
#define BUTTON_PIN      0
#define LED_PIN         2

bool ledState = HIGH;
bool buttonStateNow = LOW;
bool buttonStatePrevInstant = LOW;
bool buttonStatePrevSteady = LOW;
uint8_t count = 0;
uint32_t timePrev = 0;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);

  // set initial LED state
  digitalWrite(LED_PIN, ledState);
}

void loop() {
  buttonStatePrevInstant = buttonStateNow;
  buttonStateNow = digitalRead(BUTTON_PIN);

  //If button change state => save time.
  if(buttonStateNow != buttonStatePrevInstant) {
    timePrev = millis();
  }

  //If status of button is steady
  if(millis()-timePrev > DEBOUNCE_TIME) {

    if(buttonStateNow != buttonStatePrevSteady) {
      buttonStatePrevSteady = buttonStateNow;

      if(buttonStateNow == LOW) {
        count++;
        printf("button was pressed: %d\n", count);

        ledState = !ledState;
        digitalWrite(LED_PIN, ledState);
      }
    }
  }
}

