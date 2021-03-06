#pragma once

#include "cake.h"
#include "cake_Types.h"
#include <avr/io.h>

BEGIN_CAKE_NAMESPACE

class Adc
{
public:
    typedef uint16  Sample;
    typedef uint8   ChannelId;

    enum AnalogReference
    {
          AREF          = 0 // AREF pin, internal Vref turned off
        , AVCC          = 1 // AVCC with external capacitor at AREF pin
        , internal1_1   = 2 // Internal 1.1V  Voltage Reference with external capacitor at AREF pin
        , internal2_56  = 3 // Internal 2.56V Voltage Reference with external capacitor at AREF pin
    };

    enum Prescaler
    {
          prescaleOff   = 0 // Not actually off (/2)
        , prescale2     = 1
        , prescale4     = 2
        , prescale8     = 3
        , prescale16    = 4
        , prescale32    = 5
        , prescale64    = 6
        , prescale128   = 7
    };

public:
    static inline void enable();
    static inline void disable();

public:
    static inline void setReference(AnalogReference inReference);
    static inline void setPrescaler(Prescaler inPrescaler);

public:
    static inline Sample read(ChannelId inChannel);

private:
    void checkRegisterStructure();
};

// -----------------------------------------------------------------------------

template<byte NumBits>
class AdcOversamplingFilter
{
public:
    static const byte sAdcNumBits           = 10;
    static const byte sNumAdditionalBits    = NumBits - sAdcNumBits;
    static const uint16 sFactor             = 1 << (2 * sNumAdditionalBits);
    static const uint16 sBufferSize         = sFactor;
    static const byte sShift                = sNumAdditionalBits;

public:
    inline  AdcOversamplingFilter();
    inline ~AdcOversamplingFilter();

public:
    inline Adc::Sample process(Adc::Sample inSample);

private:
    Adc::Sample mBuffer[sBufferSize];
    uint16      mWriteIndex;
};

// -----------------------------------------------------------------------------

template<byte Bit>
class AnalogPin
{
public:
    static inline void init();
    static inline Adc::Sample read();
};

class AnalogDummyPin
{
public:
    static inline void init() { }
    static inline Adc::Sample read() { return 0; }
};

END_CAKE_NAMESPACE

#include "io/cake_Analog.hpp"
