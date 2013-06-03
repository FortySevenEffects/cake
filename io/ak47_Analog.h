/*!
 *  \file       ak47_Analog.h
 *  \author     Francois Best
 *  \date       27/10/2012
 *  \license    GPL v3.0 - Copyright Forty Seven Effects 2012
 *
 *	This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details: http://www.gnu.org/licenses
 */

#pragma once

#include "ak47.h"
#include "ak47_Types.h"
#include "utility/ak47_MiscTools.h"
#include <avr/io.h>

BEGIN_AK47_NAMESPACE

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
    static const uint16 sFactor             = 8 << sNumAdditionalBits;
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

END_AK47_NAMESPACE

#include "io/ak47_Analog.hpp"
