#include "PushButton.hpp"

void PushButton::Initialise(int pin, byte notification, int longPressStart, int longPressEnd)
{
    m_pin = pin;
    m_milliSinceReadingChanged = 0;
    m_notifyShortPress = notification & PUSHBUTTON::SHORT_PRESS;
    m_notifyLongPress = notification & PUSHBUTTON::LONG_PRESS;
    m_longPressStart = longPressStart;
    m_longPressEnd = longPressEnd;
    m_stateMachine = STATE_MACHINE::IDLE;
    pinMode(pin, INPUT);
}

int PushButton::CheckState()
{
    byte currentState = digitalRead(m_pin);
    m_state = PUSHBUTTON::NO_CHANGE;

    if (m_notifyLongPress || m_notifyShortPress)
    {
        int millisNow = millis();

        switch (m_stateMachine)
        {
        case STATE_MACHINE::IDLE:
            if (currentState == HIGH)
            {
                bool buttonPressed = millisNow - m_milliSinceReadingChanged > 50;
                m_milliSinceReadingChanged = millisNow;
                if (buttonPressed)
                {
                    m_stateMachine = STATE_MACHINE::BUTTON_DOWN;
                }
            }
            break;
        case STATE_MACHINE::BUTTON_DOWN:
            if (currentState == LOW)
            {
                bool buttonReleased = millisNow - m_milliSinceReadingChanged > 50;
                m_milliSinceReadingChanged = millisNow;

                if (buttonReleased)
                {
                    m_state = PUSHBUTTON::SHORT_PRESS;
                    m_stateMachine = STATE_MACHINE::IDLE;
                }
            }
            else if (millisNow - m_milliSinceReadingChanged > m_longPressStart)
            {
                m_state = PUSHBUTTON::LONG_PRESS_PENDING;
                m_stateMachine = STATE_MACHINE::LONG_PRESS;
            }
            break;
        case STATE_MACHINE::LONG_PRESS:
            if (millisNow - m_milliSinceReadingChanged > m_longPressEnd)
            {
                m_state = PUSHBUTTON::LONG_PRESS;
                m_stateMachine = STATE_MACHINE::ZOMBIE;
            }
            break;
        case STATE_MACHINE::ZOMBIE:
            if (currentState == LOW)
            {
                bool buttonReleased = millisNow - m_milliSinceReadingChanged > 50;
                m_milliSinceReadingChanged = millisNow;

                if (buttonReleased)
                {
                    m_stateMachine = STATE_MACHINE::IDLE;
                }
            }
            break;
        }
    }

    return m_state;
}