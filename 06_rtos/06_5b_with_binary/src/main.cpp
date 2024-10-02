/**
 * @brief: This program used to demonstrate how a "binary" works.
 * 
 * @comment: - How binary and mutex works seem alike.
 *             But they have following key different.
 *           - The "Binary" don't have onwnership.
 *             It means "Task_A" take the key then
 *             "Task_B" totaly can give the key.
 *           - The "Mutex" have an ownership.
 *             It means if "Task_A" take the key then
 *             only "Task_A" can give the key.
 * 
 * @note: For more detail about how this program works.
 *        See "Docs" folder.
 */
#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#define IS_KEY_TAKEN     (xSemaphoreTake(xBinary, portMAX_DELAY) == pdTRUE)
#define GIVE_BACK_KEY    (xSemaphoreGive(xBinary))

SemaphoreHandle_t xBinary;
uint8_t data;
TaskHandle_t xPrintData;
TaskHandle_t xSendEven;
TaskHandle_t xSendOdd;

/*---------------------------------------- Send Even Task ----------------------------------------*/
void sendEven(void *param) {
  while(1) {
    for(uint8_t i=0; i<100; i+=2) {
      if(IS_KEY_TAKEN) {
        data = i;
        delay(100);
      }
    }
  }
}

/*---------------------------------------- Send Odd Task ----------------------------------------*/
void sendOdd(void *param) {
  while(1) {
    for(uint8_t i=1; i<100; i+=2) {
      if(IS_KEY_TAKEN) {
        data = i;
        delay(100);
      }
    }    
    vTaskDelete(xSendEven);
    vTaskDelete(xPrintData);
    vTaskDelete(xSendOdd);  //Delete countOdd task.
  }
}

/*---------------------------------------- Print Data Task ----------------------------------------*/
void printData(void *param) {
  while(1) {
    ESP_LOGI("printData", "%d", data);
    GIVE_BACK_KEY;
    delay(50);
  }
}

/*---------------------------------------- Main Task ----------------------------------------*/
void setup() {
  xBinary = xSemaphoreCreateBinary();
  xTaskCreatePinnedToCore(sendEven, "sendEven", 4096, NULL, 3, &xSendEven, APP_CPU_NUM);
  xTaskCreatePinnedToCore(sendOdd, "sendOdd", 4096, NULL, 2, &xSendOdd, APP_CPU_NUM);
  xTaskCreatePinnedToCore(printData, "printData", 4096, NULL, 1, &xPrintData, APP_CPU_NUM);

  vTaskDelete(NULL);    //Delete main task.
}

void loop() {
}