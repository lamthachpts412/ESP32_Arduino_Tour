/**
 * @brief: This program used to study how preemptive priority
 *         works in ESP32 RTOS.
 * 
 * @details: This program have 2 task with different priority:
 *           - The higher priority is "say" which used to say something.
 *           - The lower priority is "count" which used to count number.
 * 
 * @explain: In this program "say" task have higher priority than "count" task.
 *           So after 100_ms "say" task will occupy CPU to run.
 * 
 * @problem: Although following theory after 100_ms "say" task will occupy CPU to run,
 *           But in this program "say" task will run after 106_ms or 107_ms.
 *           This happen because Arduino framwork not precision.
 *           If we use IDF framework instead then "say" task will precisely run after 100_ms.
 *           
 */

#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"


TaskHandle_t sayHandle;
TaskHandle_t countHandle;

void say(void *param) {
    while(1) {
        ESP_LOGI("Say", "Keep counting, buddy");
        delay(100);
    }
}

void count(void *param) {
    while(1) {
        for(uint16_t i=1; i<100; i++) {
            ESP_LOGI("Count", "___%d___", i);
        }    
        vTaskDelete(sayHandle);
        vTaskDelete(countHandle);
    }
}

void setup() {
    xTaskCreatePinnedToCore(say, "Say", 4096, NULL, 2, &sayHandle, PRO_CPU_NUM);
    xTaskCreatePinnedToCore(count, "Count", 4096, NULL, 1, &countHandle, PRO_CPU_NUM);

    vTaskDelete(NULL);  //Delete main task.
}

void loop() {
}









