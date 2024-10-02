/**
 * @brief: This program used to study how to use SPI in Arduino-Esp32.
 * 
 * @note: - For more details about SPI API:
 *          https://docs.espressif.com/projects/arduino-esp32/en/latest/api/spi.html
 *        
 */
#include <Arduino.h>
#include <SPI.h>

#define WHO_AM_I_REG  0x75

#define SCLK_PIN    18  //Wire to SCL pin of MPU9250
#define MOSI_PIN    23  //Wire to SDA pin of MPU9250
#define MISO_PIN    19  //Wire to ADO pin of MPU9250
#define CS_PIN      5   //Wire to NCS pin of MPU9250

#define READ        0x80    //0b1000.0000

uint8_t value = 0;

void setup() {
  pinMode(CS_PIN, OUTPUT);
  SPI.begin(SCLK_PIN, MISO_PIN, MOSI_PIN, CS_PIN); // SCK, MISO, MOSI, CS
  SPI.setClockDivider(SPI_CLOCK_DIV16); // Set SPI clock speed
  SPI.setDataMode(SPI_MODE0); // Set SPI mode
  SPI.setBitOrder(MSBFIRST); // Set bit order
}

void loop() {
  digitalWrite(CS_PIN, LOW); // Select the MPU9250
  SPI.transfer(WHO_AM_I_REG | READ); // Set the MSB to indicate read
  value = SPI.transfer(0x00); // Dummy byte to read the response
  digitalWrite(CS_PIN, HIGH); // Deselect the MPU9250

  printf("Value of WHO_AM_I is: 0x%x\n", value);
  delay(1000);
}

