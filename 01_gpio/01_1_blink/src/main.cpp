#include <Arduino.h>
#define USE_ARDUINO

/*------------ Use Arduino framework ------------*/
#ifdef USE_ARDUINO
void setup() {
  pinMode(2, OUTPUT);
}
void loop() { 
  digitalWrite(2, HIGH);
  delay(100);
  digitalWrite(2, LOW);
  delay(100);
}


/*------------ Use ESP-IDF framework ------------*/
#else
void setup() {
  gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT);
}
void loop() { 
  gpio_set_level(GPIO_NUM_2, HIGH);
  vTaskDelay(pdMS_TO_TICKS(1000));
  gpio_set_level(GPIO_NUM_2, LOW);
  vTaskDelay(pdMS_TO_TICKS(1000));
}
#endif