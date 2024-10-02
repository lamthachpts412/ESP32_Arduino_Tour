#include "Arduino.h"
#include "Debounce.h"

Debounce::Debounce(uint8_t pin, uint32_t debounceTime) {
  _pin = pin;
  _debounceTime = debounceTime;
  pinMode(_pin, INPUT_PULLUP);
  _timePrev = 0;
  _buttonStateNow = HIGH;
  _buttonStatePrev = HIGH;
  _buttonPressed = false;
}

bool Debounce::read() {
  return _buttonPressed;
}

bool Debounce::isPressed() {
  return _buttonPressed == true;  
}

void Debounce::update() {
  _buttonPressed = false;
  _buttonStatePrev = _buttonStateNow;
  _buttonStateNow = digitalRead(_pin);

  //If detect button change status.
  if(_buttonStateNow != _buttonStatePrev) {
    
    //If detect falling edge && time passed higher 50ms
    if(_buttonStateNow == LOW && (millis()-_timePrev) > _debounceTime) {
      _buttonPressed = true;
    }

    //Save time
    _timePrev = millis();
  }
}
