#include "Potentiometer.hpp"

void Potentiometer::Initialise(byte port, byte divisor, int jitterThreshold)
{
    m_port = port;
    m_divisor = divisor;
    m_jitterThreshold = jitterThreshold;
    m_value = analogRead(port) / m_divisor;
}

int Potentiometer::CheckState()
{
    m_state = POTENTIOMETER::NO_CHANGE;

    int value = analogRead(m_port) / m_divisor; 

    if(abs(value - m_value) > m_jitterThreshold)
    {
        m_state = POTENTIOMETER::VALUE_CHANGED;
        m_value = value;
    }

    return m_state;
}

int Potentiometer::GetValue()
{
    return m_value;
}