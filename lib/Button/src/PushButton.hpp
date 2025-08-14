#include <Arduino.h>

struct PUSHBUTTON
{
    enum STATE
    {
        NO_CHANGE = 0,
        SHORT_PRESS = 1,
        LONG_PRESS = 2,
        LONG_PRESS_PENDING = 4
    };
};

class PushButton
{
private:
    byte m_pin;
    PUSHBUTTON::STATE m_state;
    bool m_notifyShortPress = false;
    bool m_notifyLongPress = false;
    unsigned long m_milliSinceReadingChanged;
    unsigned long m_longPressStart;
    unsigned long m_longPressEnd;
    struct STATE_MACHINE
    {
        enum STATE
        {
            IDLE,
            BUTTON_DOWN,
            LONG_PRESS,
            ZOMBIE
        };
    };
    STATE_MACHINE::STATE m_stateMachine;

public:
    void Initialise(int pin, byte notify, int longPressStart = 3000, int longPressEnd = 5000);
    int CheckState();
};
