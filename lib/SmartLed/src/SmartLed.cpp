#include "SmartLed.hpp"

void SmartLed::Initialise(byte data_pin, byte latch_pin, byte clock_pin)
{
    m_data_pin = data_pin;
    m_latch_pin = latch_pin;
    m_clock_pin = clock_pin;
    pinMode(m_data_pin, OUTPUT);
    pinMode(m_latch_pin, OUTPUT);
    pinMode(m_clock_pin, OUTPUT);

    for (int num = 0; num < 8; ++num)
        Off(num);

    UpdateState(true);
}

void SmartLed::On(byte num)
{
    m_instances[num].state_machine = STATE_MACHINE::TURN_ON;
}

void SmartLed::Off(byte num)
{
    m_instances[num].state_machine = STATE_MACHINE::TURN_OFF;
}

void SmartLed::Flash(byte num, int timeout, bool startState, int repeats)
{
    m_instances[num].state_machine = STATE_MACHINE::FLASH;
    m_instances[num].flashState = startState;
    m_instances[num].flashTimer = m_instances[num].flashTimer == 0 ? 0 : m_instances[num].flashTimer;
    m_instances[num].flashTimeout = timeout;
    m_instances[num].repeats += repeats;
}

void SmartLed::UpdateState(bool force)
{
    byte muxState = m_muxState;
    unsigned long millisNow = millis();

    for (int num = 0; num < 8; ++num)
    {
        byte numBit = 1 << num;

        switch (m_instances[num].state_machine)
        {
        case STATE_MACHINE::IDLE:
            break;
        case STATE_MACHINE::TURN_ON:
            muxState |= numBit;
            m_instances[num].state_machine = STATE_MACHINE::IDLE;
            break;
        case STATE_MACHINE::TURN_OFF:
            muxState &= ~numBit;
            m_instances[num].flashTimer = 0;
            m_instances[num].state_machine = STATE_MACHINE::IDLE;
            break;
        case STATE_MACHINE::FLASH:
        {
            if (m_instances[num].flashTimer == 0)
                m_instances[num].flashTimer = millisNow;

            if (millisNow - m_instances[num].flashTimer > m_instances[num].flashTimeout)
            {
                m_instances[num].flashState = !m_instances[num].flashState;
                muxState = m_instances[num].flashState ? muxState | numBit : muxState ^ numBit;
                m_instances[num].flashTimer = millisNow;

                if (m_instances[num].repeats > 0)
                    m_instances[num].repeats -= 1;

                m_instances[num].state_machine = m_instances[num].repeats == 0 ? STATE_MACHINE::TURN_OFF : STATE_MACHINE::FLASH;
            }
        }
        break;
        }
    }

    if (force || muxState != m_muxState)
    {
        m_muxState = muxState;
        digitalWrite(m_latch_pin, LOW);
        shiftOut(m_data_pin, m_clock_pin, LSBFIRST, m_muxState);
        digitalWrite(m_latch_pin, HIGH);
    }
}