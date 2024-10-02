/**
 * @brief: This program used to study how to use ADC in Arduino-Esp32.
 * 
 * @note: - One shot mode means whenever we use analogRead() we got a ADC value.
 *        - For more information about ADC: 
 *          https://docs.espressif.com/projects/arduino-esp32/en/latest/api/adc.html
 */

#include <Arduino.h>
#define ADC_PIN   25

void setup() {
  //Set the resolution to 12 bits (0-4095).
  analogReadResolution(12);
  //Set attenuation to 11dB.
  analogSetAttenuation(ADC_11db);
}

void loop() {

  int analogValue = analogRead(ADC_PIN);
  int analogVolts = analogReadMilliVolts(ADC_PIN);

  printf("ADC analog value = %d\n", analogValue);
  printf("ADC millivolts value = %d mV\n", analogVolts);

  delay(500);
}
