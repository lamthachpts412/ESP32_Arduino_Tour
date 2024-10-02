/**
 * @brief: This program used to demonstrate how a "queue" works.
 * 
 * @note: For more detail about how this program works.
 *        See "Docs" folder.
 */
#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

TaskHandle_t xPrintData;
TaskHandle_t xSendEven;
TaskHandle_t xSendOdd;
QueueHandle_t xQueue = NULL;

/*---------------------------------------- Send Even Task ----------------------------------------*/
void sendEven(void *param) {
  while(1) {
    for(uint8_t i=0; i<100; i+=2) {
      xQueueSend(xQueue, &i, pdMS_TO_TICKS(100));
      delay(100);
    }
  }
}

/*---------------------------------------- Send Odd Task ----------------------------------------*/
void sendOdd(void *param) {
  while(1) {
    for(uint8_t i=1; i<100; i+=2) {
      xQueueSend(xQueue, &i, pdMS_TO_TICKS(100));
      delay(100);
    }    
    vTaskDelete(xSendEven);
    vTaskDelete(xPrintData);
    vTaskDelete(xSendOdd);  //Delete countOdd task.
  }
}

/*---------------------------------------- Print Data Task ----------------------------------------*/
void printData(void *param) {
  uint8_t data;
  while(1) {
    xQueueReceive(xQueue, &data, pdMS_TO_TICKS(50));
    ESP_LOGI("printData", "%d", data);
    delay(50);
  }
}

/*---------------------------------------- Main Task ----------------------------------------*/
void setup() {
  xQueue = xQueueCreate(2, sizeof(uint8_t));
  xTaskCreatePinnedToCore(sendEven, "sendEven", 4096, NULL, 3, &xSendEven, APP_CPU_NUM);
  xTaskCreatePinnedToCore(sendOdd, "sendOdd", 4096, NULL, 2, &xSendOdd, APP_CPU_NUM);
  xTaskCreatePinnedToCore(printData, "printData", 4096, NULL, 1, &xPrintData, APP_CPU_NUM);

  vTaskDelete(NULL);    //Delete main task.
}

void loop() {
}