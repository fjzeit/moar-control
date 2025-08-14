#include <Potentiometer.hpp>
#include <PushButton.hpp>
#include <RotaryEncoder.hpp>
#include <SmartLed.hpp>
#include <MidiSend.hpp>

struct LEDBANK
{
    enum
    {
        EMPTY1,
        MEAT_MISSING_LED,
        GRAVY_MISSING_LED,
        VEG_MISSING_LED,
        REVERB_ON_LED,
        COMPRESSOR_ON_LED,
        GATE_ON_LED,
        EMPTY2
    };
};

struct REVERB_MIX
{
    enum
    {
        CC_ON_OFF = 75,          // reverb on/off
        TIME = 76,
        PREDELAY = 77,
        COLOUR = 78,
        CC_MIX = 79,
        REV_TYPE = 85
    };
    // on/off is in VEG_MIX::onOff bitfield
    byte time;
    byte preDelay;
    byte colour;
    byte mix;
    byte type;
};

struct COMP_MIX
{
    enum {
        CC_ON_OFF = 18,      // compressor on/off
        CC_THRESHOLD = 19,   // threshold
        CC_CMP_GAIN = 20,    // make-up gain
        CC_CMP_ATK = 21,     // attack
        CC_CMP_PATC = 22     // patch (pre/post)
    };
    // on/off is in VEG_MIX::onOff bitfield
    byte threshold;
    byte gain;
    byte attack;
    // patch is in VEG_MIX::onOff bitfield
};

struct GATE_MIX
{
    enum {
        CC_ON_OFF = 14,     // gate on/off
        CC_THRESHOLD = 15,  // gate threshold
        CC_RELEASE = 16,    // gate release
        CC_DEPTH = 17       // gate depth
    };
    // on/off is in VEG_MIX::onOff bitfield
    byte threshold;
    byte release;
    byte depth;
};

struct EQ_MIX
{
    enum {
        CC_PRESENCE = 106,    // Adjust high frequency content
        CC_DEPTH = 107,       // Low frequency content
        CC_MIX = 104,         // Tone model mix
        CC_BASS_FRQ = 24,     // EQ low-band frequency
        CC_MID_Q = 26,        // EQ mid-band Q factor
        CC_MID_FRQ = 27,      // EQ mid-band frequency
        CC_TRBL_FRQ = 29,     // EQ high-band frequency
        CC_EQ_PATCH = 30      // patch (pre/post)
    };
    byte presence;
    byte depth;
    byte mix;
    byte bassFreq;
    byte midQ;
    byte midFreq;
    byte trebFreq;
    // patch is in VEG_MIX::onOff bitfield
};

struct VEG_MIX
{
    byte version;
    enum {
        COMP_ONOFF = 1,       // compressor on or off
        REVERB_ONOFF = 2,     // reverb on or off
        GATE_ONOFF = 4,       // noise gate on or off
        AMP_PATCH = 8,        // EQ patch pre/post
        COMP_PATCH = 16       // compressor patch pre/post
    };
    byte onOff;
    EQ_MIX ampMix;
    REVERB_MIX reverbMix;
    COMP_MIX compMix;
    GATE_MIX gateMix;
};

class TauOfTone
{
private:
    MidiSend m_midiOut;
    Potentiometer m_MeatPot;
    Potentiometer m_GravyPot;
    Potentiometer m_VegPot;

    RotaryEncoder m_vegRotary1;
    RotaryEncoder m_vegRotary2;
    RotaryEncoder m_vegRotary3;
    RotaryEncoder m_vegRotary4;
    RotaryEncoder m_vegRotary5;

    Potentiometer m_ModePot;

    PushButton m_vegPushButton;
    PushButton m_modePushButton;

    SmartLed m_ledBank;
    struct MODESELECT
    {
        enum
        {
            AMP,
            ALT,
            REV,
            COMP,
            GATE
        };
    };
    MODESELECT m_currentMode;
    VEG_MIX m_vegMix[11];

public:
    void Initialise();
    void UpdateStatus();
    void UpdateState();
};
