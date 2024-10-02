#ifndef Debounce_h
#define Debounce_h

#include "Arduino.h"

class Debounce {
  public:
    Debounce(uint8_t pin, uint32_t debounceTime = 50);
    bool read();        // Returns debounced state
    bool isPressed();   // Returns true if button is pressed
    void update();      // Updates the debounced state, to be called in loop()
  
  private:
    uint8_t _pin;
    uint32_t _debounceTime;
    uint32_t _timePrev;
    bool _buttonStateNow;
    bool _buttonStatePrev;
    bool _buttonPressed;
};

#endif
