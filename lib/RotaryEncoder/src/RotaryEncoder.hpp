#include "Arduino.h"

struct ROTARY_ENCODER
{
    enum STATE
    {
        NO_CHANGE = 0,
        CLOCKWISE = 1,
        COUNTER_CLOCKWISE = 2,
        BUTTON_DOWN = 4
    };
};

class RotaryEncoder
{
private:
    int m_clk = -1;
    int m_dt;
    int m_sw;
    int m_counter = 0;
    int m_currentStateClk = 0;
    int m_lastStateClk = 0;
    unsigned long m_lastButtonPress;
    int m_rotaryState = ROTARY_ENCODER::BUTTON_DOWN;
    bool m_buttonPressed = false;
    bool m_buttonDown = false;
    bool m_toggle = false;
    unsigned long m_rateLimit = 0;

    void InitBoard();

public:
    static const int NOT_USED = -1; 
    int CheckState();
    bool IsButtonPressed();
    bool IsButtonDown();
    void Initialise(int clk, int dt, int sw, bool toggle = false);
    void Initialise(int basePort, bool toggle = false, bool alt = false);
};