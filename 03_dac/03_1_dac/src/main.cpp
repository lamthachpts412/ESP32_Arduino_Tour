/**
 * @brief: This program used to study how to use DAC in Arduino-Esp32.
 * 
 * @note: - In this program we use DAC to increase brightness LED.
 */

#include <Arduino.h>

#define DAC_PIN   25

void setup() {
  
}

void loop() {
  for(int i=0; i<255; i++) {
    //Value for DAC is in range [0:255] ~ [0V:3V3].
    dacWrite(DAC_PIN, i);
    delay(10);
  }
}

