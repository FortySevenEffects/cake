/*!
 *  \file       ak47_Gpio.h
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
#include <avr/io.h>

BEGIN_AK47_NAMESPACE

typedef volatile uint8* RegisterAddress;

template<class RegisterTraits>
class Port
{
public:
    typedef RegisterTraits Traits;

public:
    inline  Port();
    inline ~Port();

public: // Direction
    template<byte Pin>
    static inline void setInput(bool inWithPullUp = false);

    template<byte Pin>
    static inline void setOutput();

public: // Pin operations
    template<byte Pin>
    static inline void set();

    template<byte Pin>
    static inline void clear();

    template<byte Pin>
    static inline void toggle();

public: // Port operations
    static inline byte read();
    static inline void write(byte inValue);
};

// -----------------------------------------------------------------------------

template<class Port, byte Bit>
class Pin
{
public:
    inline  Pin();
    inline ~Pin();

public:
    static inline void setInput(bool inWithPullUp = false);
    static inline void setOutput();

public:
    static inline void set();
    static inline void clear();
    static inline void toggle();
    static inline bool read();
};

// -----------------------------------------------------------------------------

template<class Port, byte Mask>
class PinGroup
{
public:
    inline  PinGroup();
    inline ~PinGroup();

public:
    static inline void setInput(bool inWithPullUp = false);
    static inline void setOutput();

public:
    static inline void set(byte inValue);
    static inline void clear();
    static inline byte read();

private:
    static inline byte getShift();
};

END_AK47_NAMESPACE

#include "io/ak47_Gpio.hpp"
