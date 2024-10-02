/**
 * @brief: This program used to study how to use interrupt in Arduino.
 * 
 * @problem: When we press button, something we see
 *           the "count" not increase to 1 but 2 or 3 times.
 *           This happens due to button have some noise.
 * 
 * @solution: We can remove noise by a technique called "debounce".
 *            We will cover debounce technique in following programs.
 * 
 * @note: When writing an Interrupt Service Routine (ISR):
 *        1. Keep it as short as possible.
 *        2. Don't use delay().
 *        3. Don't use serial prints.
 *        4. Make variable shared with the main code is "volatile".
 *        5. Don't try to turn interrupts off or on. 
 */

#include <Arduino.h>

#define LED_PIN       2
#define BUTTON_PIN    0


void xButton();
volatile bool ledState = 0;
volatile uint16_t count = 0;


void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  attachInterrupt(BUTTON_PIN, xButton, FALLING);
}

void loop() {
  digitalWrite(LED_PIN, ledState);
  printf("Button was pressed: %d\n", count);
}

void xButton() {
  ledState = !ledState;
  count++;
}
