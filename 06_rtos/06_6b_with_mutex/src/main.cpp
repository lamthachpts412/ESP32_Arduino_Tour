/**
 * @brief: This program used to demonstrate how mutex works.
 * 
 * @comment: - How binary and mutex works seem alike.
 *             But they have following key different.
 *           - The "Binary" don't have onwnership.
 *             It means "Task_A" take the key then
 *             "Task_B" totaly can give the key.
 *           - The "Mutex" have an ownership.
 *             It means if "Task_A" take the key then
 *             only "Task_A" can give the key.
 */

#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#define IS_KEY_TAKEN    xSemaphoreTake(xMutex, pdMS_TO_TICKS(100)) == pdTRUE
#define GIVE_BACK_KEY   xSemaphoreGive(xMutex); 

SemaphoreHandle_t xMutex = NULL;

TaskHandle_t xTask1;
TaskHandle_t xTask2;
uint8_t data = 0;


void task(void *param) {
  uint8_t taskID = *(uint8_t*)param;

  while(1) {
    if(taskID == 1) {
      if(IS_KEY_TAKEN) {
        
        //Critical section:
        for(uint8_t i=0; i<100; i++) {
          data = i;
          ESP_LOGI("Task", "Task[%d]: data = %d", taskID, data);
          delay(10);
        }

        // Release the mutex
        GIVE_BACK_KEY;
      }
    }

    else if(taskID == 2 ) {
      if(IS_KEY_TAKEN) {
        data = 255;
        ESP_LOGI("Task", "Task[%d]: data = %d", taskID, data);
        GIVE_BACK_KEY;
        delay(100);
      }
    }
  }
}

void setup() {
  xMutex = xSemaphoreCreateMutex();
  uint8_t taskID1 = 1;
  uint8_t taskID2 = 2;
  xTaskCreatePinnedToCore(task, "Task_1", 4096, &taskID1, 1, &xTask1, APP_CPU_NUM);
  xTaskCreatePinnedToCore(task, "Task_2", 4096, &taskID2, 2, &xTask2, APP_CPU_NUM);
  
  delay(1000);
  vTaskDelete(xTask1);
  vTaskDelete(xTask2);
  vTaskDelete(NULL);
}

void loop() {
}