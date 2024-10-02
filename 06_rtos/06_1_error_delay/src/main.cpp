/**
 * @brief: This program used to fix a "delay" bug that
 *         we can meet when work with FreeRTOS.
 * 
 * @problem: In this program, we used delay 1_ms in "print" task.
 *           But when we run program it was 2_ms. 
 * 
 * @solution: - In essence, the setup() and loop() function also a task (main task).
 *              So this program have 2 tasks which is "print" task and "main" task.
 *              Because "main" task also take time from CPU then it make delay()
 *              work in the wrong way.
 *            - To deal with problem, we need stop this "main" task.
 *              So we used vTaskDelete() in setup() to delete "main" task.
 * 
 * @note: For more details about problem, see "Docs" folder.
 */

#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

// #define USE_TASK_DELETE  //Delete main task.
#define LED_PIN     25

bool ledState = LOW;

void print(void *param) {
    while(1) {
        ledState = !ledState;
        digitalWrite(LED_PIN, ledState);
        delay(1);
    }
}


void setup() {
    pinMode(LED_PIN, OUTPUT);
    xTaskCreatePinnedToCore(print, "print", 4096, NULL, 1, NULL, APP_CPU_NUM);

    #ifdef USE_TASK_DELETE
    vTaskDelete(NULL);      //Delete main task.
    #endif
}

void loop() {
}









