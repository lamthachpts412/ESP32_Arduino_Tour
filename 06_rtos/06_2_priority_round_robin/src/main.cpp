/**
 * @brief: This program used to study how round robin priority
 *         works in ESP32 RTOS.
 * 
 * @details: This program have 2 task same priority:
 *           - The first is "countEven" which used to count even number.
 *           - The second is "countOdd" which used to count odd number.
 * 
 * @problem:  When we look output at terminal,
 *            we can see "Time Slice" between tasks not equally.
 *            See "Docs" folder for details.
 * 
 * @solution: - Use delay() for each tasks, 
 *              we will get "Time Slice" equally.
 *            - Also when use delay() then 
 *              time for complete program is faster.
 * 
 * @note: Default Arduino Esp32 config "Time Slice" is 1ms.
 *        "Time Slice" configured with param "configTICK_RATE_HZ".
 */

#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "FreeRTOSConfig.h"
#include "esp_log.h"

// #define USE_DELAY


void countEven(void *param) {
    while(1) {
        for(uint16_t i=0; i<1000; i+=2) {
            ESP_LOGI("Even", "___%d___", i);

            #ifdef USE_DELAY
            delay(1);
            #endif
        }
        vTaskDelete(NULL);  //Delete countEven task.
    }
}

void countOdd(void *param) {
    while(1) {
        for(uint16_t i=1; i<1000; i+=2) {
            ESP_LOGI("Odd", "---%d---", i);

            #ifdef USE_DELAY
            delay(1);
            #endif
        }    
        vTaskDelete(NULL);  //Delete countOdd task.
    }
}

void setup() {
  xTaskCreatePinnedToCore(countEven, "Even", 4096, NULL, 1, NULL, APP_CPU_NUM);
  xTaskCreatePinnedToCore(countOdd, "Odd", 4096, NULL, 1, NULL, APP_CPU_NUM);

  vTaskDelete(NULL);    //Delete main task.
}

void loop() {
}









