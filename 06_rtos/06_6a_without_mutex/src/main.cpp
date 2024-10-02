#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

TaskHandle_t xTask1;
TaskHandle_t xTask2;
uint8_t data = 0;


void task(void *param) {
  uint8_t taskID = *(uint8_t*)param;

  while(1) {
    if(taskID == 1) {
      for(uint8_t i=0; i<100; i++) {
        data = i;
        ESP_LOGI("Task", "Task[%d]: data = %d", taskID, data);
        delay(10);
      }
    }
    else if(taskID == 2 ) {
      data = 255;
      ESP_LOGI("Task", "Task[%d]: data = %d", taskID, data);
      delay(100);
    }

  }
}

void setup() {
  uint8_t taskID1 = 1;
  uint8_t taskID2 = 2;
  xTaskCreatePinnedToCore(task, "Task_2", 4096, &taskID2, 2, &xTask2, APP_CPU_NUM);
  xTaskCreatePinnedToCore(task, "Task_1", 4096, &taskID1, 1, &xTask1, APP_CPU_NUM);
  
  delay(1000);
  vTaskDelete(xTask1);
  vTaskDelete(xTask2);
  vTaskDelete(NULL);
}

void loop() {
}