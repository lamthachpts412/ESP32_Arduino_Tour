#include "Debounce.h"

Debounce* Debounce::instance = nullptr;


Debounce::Debounce(int pin) 
    : _pin(pin), 
      _pressed(false), 
      _buttonChanged(false),
      _buttonStateNow(HIGH),
      _buttonStatePrevSteady(HIGH), 
      _timePrev(0)
{
    instance = this;
}

void Debounce::begin() {
    pinMode(_pin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(_pin), ISR, CHANGE);
}

void Debounce::update() {
    _pressed = false;

    //If button changed status.
    if(_buttonChanged == true) {
        _buttonChanged = false;
        _timePrev = millis();
    }

    //If button was in steady state.
    if(millis()-_timePrev > debounceTime) {

        //If steady state of button was changed.
        if(_buttonStateNow != _buttonStatePrevSteady) {
            _buttonStatePrevSteady = _buttonStateNow;

            //If steady status of button is LOW
            if(_buttonStateNow == LOW) {
                _pressed = true;
            }
        }
    }
}

void Debounce::ISR() {
    instance->_buttonChanged = true;
    instance->_buttonStateNow = digitalRead(instance->_pin);
}

bool Debounce::isPressed() {
    return _pressed; // Return the debounced state
}
