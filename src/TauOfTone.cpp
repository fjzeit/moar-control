#include <TauOfTone.hpp>

void DebugPot(int state, Potentiometer *pot)
{
    if (state & POTENTIOMETER::VALUE_CHANGED)
    {
        Serial.print("State: ");
        Serial.println(pot->GetValue());
    }
}

void DebugRotary(int state)
{
    if(!state) return;
    
    Serial.print("veg1:Direction ");
    if (state & ROTARY_ENCODER::COUNTER_CLOCKWISE)
        Serial.print("CCW");
    if (state & ROTARY_ENCODER::CLOCKWISE)
        Serial.print("CW");
    if (state & ROTARY_ENCODER::BUTTON_DOWN)
        Serial.print(" (PRESSED)");
    Serial.println();
}

void TauOfTone::Initialise()
{
    Serial.begin(115200);

    m_ledBank.Initialise(11, 12, 13);
    m_vegRotary1.Initialise(2, 3, RotaryEncoder::NOT_USED);
    m_vegRotary2.Initialise(4, 5, RotaryEncoder::NOT_USED);
    m_vegRotary3.Initialise(6, 7, RotaryEncoder::NOT_USED);
    m_vegRotary4.Initialise(8, 9, RotaryEncoder::NOT_USED);
    m_vegRotary5.Initialise(A4, A5, RotaryEncoder::NOT_USED);
    m_ModePot.Initialise(A0, 3, 5);
    m_MeatPot.Initialise(A1, 3, 5);
    m_GravyPot.Initialise(A2, 3, 5);
    m_VegPot.Initialise(A3, 3, 5);
    m_vegPushButton.Initialise(11, PUSHBUTTON::SHORT_PRESS | PUSHBUTTON::LONG_PRESS);
    m_modePushButton.Initialise(12, PUSHBUTTON::SHORT_PRESS | PUSHBUTTON::LONG_PRESS);
}

void TauOfTone::UpdateStatus()
{
    int veg1State = m_vegRotary1.CheckState();
    int veg2State = m_vegRotary2.CheckState();
    int veg3State = m_vegRotary3.CheckState();
    int veg4State = m_vegRotary4.CheckState();

    int modeState = m_ModePot.CheckState();
    int meatState = m_MeatPot.CheckState();
    int gravyState = m_GravyPot.CheckState();
    int vegState = m_VegPot.CheckState();
   
    DebugRotary(veg1State);
    DebugRotary(veg2State);
    DebugRotary(veg3State);
    DebugRotary(veg4State);

    DebugPot(modeState, &m_ModePot);
    DebugPot(meatState, &m_MeatPot);
    DebugPot(gravyState, &m_GravyPot);
    DebugPot(vegState, &m_VegPot);
}

void TauOfTone::UpdateState()
{
    m_ledBank.UpdateState();
}

