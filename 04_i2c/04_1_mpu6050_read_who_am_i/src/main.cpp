/**
 * @brief: This program used to study how to use I2C in Arduino-Esp32.
 * 
 * @note: - For more information about I2C API:
 *          https://docs.espressif.com/projects/arduino-esp32/en/latest/api/i2c.html
 *        - We can config any GPIOs for SDA and SCL pin.
 */

#include <Arduino.h>
#include <Wire.h>

#define MPU6050_ADD     0x68 
#define WHO_AM_I_REG    0x75
#define SDA_PIN         16
#define SCL_PIN         17
#define FREQUENCY       400000

uint8_t value = 0;
void setup() {
  // Wire.begin();                              //Default: SDA-21, SCL-22, f=100kHz
  Wire.begin(SDA_PIN, SCL_PIN, FREQUENCY);   //Setup: SDA-16, SCL-17, f=400kHz
}

void loop() {
  Wire.beginTransmission(MPU6050_ADD);
  Wire.write(WHO_AM_I_REG);
  Wire.endTransmission();

  Wire.requestFrom(MPU6050_ADD, 1);
  while (Wire.available() == 0); // Wait for data to be available
  value = Wire.read();
  printf("Value of WHO_AM_I is: 0x%x\n", value);

  delay(1000);
}

