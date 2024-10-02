#include <Arduino.h>
#include "esp_log.h"

/**
 *  eRunning = 0
 *  eReady = 1
 *  eBlocked = 2
 *  eSuspended = 3
 *  eDeleted = 4
 *  eInvalid = 5 
 */

TaskHandle_t xSpell = NULL;
TaskHandle_t xCount = NULL;

eTaskState spellState;
eTaskState countState;

void count(void *parameter) {
    
    while (true) {
      countState = eTaskGetState(xCount);
      spellState = eTaskGetState(xSpell);
      ESP_LOGI("Count", "--- 1 ---|count: %d|_|spell: %d|", countState, spellState);
      delay(100);

      countState = eTaskGetState(xCount);
      spellState = eTaskGetState(xSpell);
      ESP_LOGI("Count", "--- 2 ---|count: %d|_|spell: %d|", countState, spellState);
    }
}

void spell(void *parameter) {

    while (true) {
      countState = eTaskGetState(xCount);
      spellState = eTaskGetState(xSpell);
      ESP_LOGI("Spell", "___One___|count: %d|_|spell: %d|", countState, spellState);
      delay(23);
    }
}

void setup() {
    xTaskCreatePinnedToCore(spell, "spell", 2048, NULL, 1, &xSpell, APP_CPU_NUM);
    xTaskCreatePinnedToCore(count, "count", 2048, NULL, 2, &xCount, APP_CPU_NUM);

}

void loop() {
  delay(1000);
  vTaskSuspend(xSpell);
  vTaskSuspend(xCount);

  countState = eTaskGetState(xCount);
  spellState = eTaskGetState(xSpell);
  ESP_LOGI("Count", "___Loop___|count: %d|_|spell: %d|", countState, spellState);

  vTaskDelete(NULL);
}
