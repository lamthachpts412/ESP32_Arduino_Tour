#ifndef Debounce_h
#define Debounce_h

#include <Arduino.h>

class Debounce {
public:
    Debounce(int pin);
    void begin();
    void update();
    bool isPressed();
    
private:
    static void ISR();
    static Debounce* instance;

    int _pin;

    volatile bool _buttonChanged;
    volatile bool _buttonStateNow;
    bool _buttonStatePrevSteady;

    volatile bool _pressed;
    uint32_t _timePrev;
    static const uint32_t debounceTime = 50; // Adjust debounce time (in milliseconds)
};

#endif
