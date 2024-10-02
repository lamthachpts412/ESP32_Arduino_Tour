#include <Arduino.h>
#include "esp_log.h"

/**
 *  eRunning    = 0
 *  eReady      = 1
 *  eBlocked    = 2
 *  eSuspended  = 3
 *  eDeleted    = 4
 *  eInvalid    = 5 
 */

TaskHandle_t xSpell = NULL;
TaskHandle_t xCount = NULL;

volatile bool flag = false;
eTaskState spellState;
eTaskState countState;

void count(void *parameter) {
    uint8_t i = 0;

    while (true) {
      for(uint8_t i=0; i<100; i++) {
        countState = eTaskGetState(xCount);
        spellState = eTaskGetState(xSpell);
        ESP_LOGI("Count", "--- %i ---|count: %d|_|spell: %d|", i, countState, spellState);

        if(i>=10) flag = true;  
        delay(100);
      }
    }
}

void spell(void *parameter) {

    while (true) {
      if(flag == true) {
        countState = eTaskGetState(xCount);
        spellState = eTaskGetState(xSpell);
        ESP_LOGI("Spell", "___One___|count: %d|_|spell: %d|", countState, spellState);
        vTaskDelete(xCount);
        vTaskDelete(xSpell);
      }
    }
}

void setup() {
    xTaskCreatePinnedToCore(spell, "spell", 2048, NULL, 1, &xSpell, APP_CPU_NUM);
    xTaskCreatePinnedToCore(count, "count", 2048, NULL, 2, &xCount, APP_CPU_NUM);
}

void loop() {
}
