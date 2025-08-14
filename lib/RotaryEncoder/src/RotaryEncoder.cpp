#include "RotaryEncoder.hpp"

void RotaryEncoder::Initialise(int clk, int dt, int sw, bool toggle)
{
    m_clk = clk;
    m_dt = dt;
    m_sw = sw;
    m_toggle = toggle;
    InitBoard();
}

void RotaryEncoder::Initialise(int basePort, bool toggle, bool alt)
{
    m_clk = alt ? basePort + 1 : basePort;
    m_dt = alt ? basePort : basePort + 1;
    m_sw = basePort + 2;
    m_toggle = toggle;
    InitBoard();
}

void RotaryEncoder::InitBoard()
{
    pinMode(m_clk, INPUT);
    pinMode(m_dt, INPUT);
    if (m_sw != NOT_USED)
        pinMode(m_sw, INPUT_PULLUP);
    delay(1);
    m_lastStateClk = digitalRead(m_clk);
}

int RotaryEncoder::CheckState()
{
    if (m_clk == -1)
        return ROTARY_ENCODER::NO_CHANGE;

    if (m_rateLimit == millis())
        delay(1);

    if (m_sw != NOT_USED && digitalRead(m_sw) == LOW)
    {
        m_buttonPressed = millis() - m_lastButtonPress > 50;
        m_lastButtonPress = millis();
        if (m_toggle)
        {
            if (m_buttonPressed)
                m_buttonDown = !m_buttonDown;
        }
        else
        {
            m_buttonDown = true;
        }
    }
    else
    {
        m_buttonPressed = false;
        if (!m_toggle)
            m_buttonDown = false;
    }

    m_currentStateClk = digitalRead(m_clk);

    if (m_currentStateClk != m_lastStateClk && m_currentStateClk)
        m_rotaryState = (digitalRead(m_dt) != m_currentStateClk ? ROTARY_ENCODER::COUNTER_CLOCKWISE : ROTARY_ENCODER::CLOCKWISE) | (m_buttonDown ? ROTARY_ENCODER::BUTTON_DOWN : 0);
    else
        m_rotaryState = ROTARY_ENCODER::NO_CHANGE;

    m_lastStateClk = m_currentStateClk;

    m_rateLimit = millis();

    return m_rotaryState;
}

bool RotaryEncoder::IsButtonPressed()
{
    return m_buttonPressed;
}

bool RotaryEncoder::IsButtonDown()
{
    return m_buttonDown;
}
