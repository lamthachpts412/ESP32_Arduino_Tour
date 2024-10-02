/**
 * @brief: This program used to study how to debounce button.
 * 
 * @note: For more detail about this debounce technique,
 *        see "Docs" folder.
 */

#include <Arduino.h>

#define DEBOUNCE_TIME   50
#define BUTTON_PIN      0
#define LED_PIN         2

bool ledState = HIGH;
bool buttonStateNow = LOW;
bool buttonStatePrev = LOW;
uint8_t count = 0;
uint32_t timePrev = 0;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);

  // set initial LED state
  digitalWrite(LED_PIN, ledState);
}

void loop() {
  buttonStatePrev = buttonStateNow;
  buttonStateNow = digitalRead(BUTTON_PIN);

  //If detect button change status
  if(buttonStateNow != buttonStatePrev) {
    printf("[%d]\n", buttonStateNow);

    //If detect falling edge && time passed is higher 50ms
    if(buttonStateNow == LOW && (millis()-timePrev) > DEBOUNCE_TIME) {
      printf("[%d] ", millis()-timePrev);

      //Do something in here
      count++;
      printf("Button was pressed: %d\n", count);

      ledState = !ledState;
      digitalWrite(LED_PIN, ledState);
    }

    //Save time
    timePrev = millis();
  }
}

