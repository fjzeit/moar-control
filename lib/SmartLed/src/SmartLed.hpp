#include <Arduino.h>

class SmartLed
{
private:
    struct STATE_MACHINE
    {
        enum STATE
        {
            IDLE,
            TURN_ON,
            TURN_OFF,
            FLASH
        };
    };
    struct Instance
    {
        unsigned long flashTimer;
        unsigned int flashTimeout;
        int repeats;
        bool flashState;
        STATE_MACHINE::STATE state_machine;
    };
    Instance m_instances[8];

    byte m_muxState;
    byte m_data_pin;
    byte m_latch_pin;
    byte m_clock_pin;

public:
    void Initialise(byte data_pin, byte latch_pin, byte clock_pin);
    void On(byte num);
    void Off(byte num);
    void Flash(byte num, int timeout = 500, bool startState = HIGH, int repeats = -1);
    void UpdateState(bool force = false);
};
