#include "Arduino.h"

struct POTENTIOMETER
{
    enum STATE
    {
        NO_CHANGE = 0,
        VALUE_CHANGED = 1,
        BUTTON_PRESSED = 2,
        LONG_PRESS = 6
    };
};

class Potentiometer
{
private:
    byte m_port;
    int m_value;
    byte m_divisor;
    int m_jitterThreshold;
    POTENTIOMETER::STATE m_state;

public:
    void Initialise(byte port, byte shiftRight = 0, int jitterThreshold = 0);
    int CheckState();
    int GetValue();
};
