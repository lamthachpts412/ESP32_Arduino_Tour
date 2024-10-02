/**
 * @brief: This program used to serve for demonstrating 
 *         how "binary" work in next program.
 * 
 * @desired_output:
 *                [    37][I][main.cpp:44] printData(): [printData] 1
 *                [    93][I][main.cpp:44] printData(): [printData] 2
 *                [   148][I][main.cpp:44] printData(): [printData] 3
 *                [   203][I][main.cpp:44] printData(): [printData] 4
 *                [   258][I][main.cpp:44] printData(): [printData] 5
 *                [   313][I][main.cpp:44] printData(): [printData] 6
 *                [   368][I][main.cpp:44] printData(): [printData] 7
 *                [   423][I][main.cpp:44] printData(): [printData] 8
 *                [   478][I][main.cpp:44] printData(): [printData] 9
 *                [   533][I][main.cpp:44] printData(): [printData] 10 
 * 
 * @actual_output:  
 *                [    37][I][main.cpp:44] printData(): [printData] 1
 *                [    93][I][main.cpp:44] printData(): [printData] 1
 *                [   148][I][main.cpp:44] printData(): [printData] 3
 *                [   203][I][main.cpp:44] printData(): [printData] 3
 *                [   258][I][main.cpp:44] printData(): [printData] 5
 *                [   313][I][main.cpp:44] printData(): [printData] 5
 *                [   368][I][main.cpp:44] printData(): [printData] 7
 *                [   423][I][main.cpp:44] printData(): [printData] 7
 *                [   478][I][main.cpp:44] printData(): [printData] 9
 *                [   533][I][main.cpp:44] printData(): [printData] 9
 * 
 * @note: For more details about how this program works.
 *        See "Docs" folder.
 * 
 */

#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

uint8_t data;
TaskHandle_t xPrintData;
TaskHandle_t xSendEven;
TaskHandle_t xSendOdd;

/*---------------------------------- Send Even Task ----------------------------------*/
void sendEven(void *param) {
  while(1) {
    for(uint8_t i=0; i<100; i+=2) {
      data = i;
      delay(100);
    }
  }
}

/*---------------------------------- Send Odd Task ----------------------------------*/
void sendOdd(void *param) {
  while(1) {
    for(uint8_t i=1; i<100; i+=2) {
      data = i;
      delay(100);
    }    
    vTaskDelete(xSendEven);
    vTaskDelete(xPrintData);
    vTaskDelete(xSendOdd);
  }
}

/*---------------------------------- Print Data Task ----------------------------------*/
void printData(void *param) {
  while(1) {
    ESP_LOGI("printData", "%d", data);
    delay(50);
  }
}

/*---------------------------------- Main Task ----------------------------------*/
void setup() {
  xTaskCreatePinnedToCore(sendEven, "sendEven", 4096, NULL, 3, &xSendEven, APP_CPU_NUM);
  xTaskCreatePinnedToCore(sendOdd, "sendOdd", 4096, NULL, 2, &xSendOdd, APP_CPU_NUM);
  xTaskCreatePinnedToCore(printData, "printData", 4096, NULL, 1, &xPrintData, APP_CPU_NUM);

  vTaskDelete(NULL);    //Delete main task.
}

void loop() {
}