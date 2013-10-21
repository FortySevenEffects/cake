/*!
 *  \file       ak47_PinChangeInterrupts.h
 *  \author     Francois Best
 *  \date       23/10/2012
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
#include "io/ak47_Gpio.h"
#include <avr/interrupt.h>

BEGIN_AK47_NAMESPACE

template<class Port>
struct PinChangeTraits
{
    static constexpr inline RegisterAddress8 getGeneralInterruptRegister();
    static constexpr inline RegisterAddress8 getPinChangeMaskRegister();
    static constexpr inline byte getPinChangeEnableMask();
};

// -----------------------------------------------------------------------------

template<class Pin>
class PinChangeInterrupt
{
private:
    typedef PinChangeTraits<typename Pin::Port> Traits;

public:
    inline  PinChangeInterrupt();
    inline ~PinChangeInterrupt();

public:
    static inline void init(bool inPullUp = true);

public:
    static inline void enable();
    static inline void disable();
};

END_AK47_NAMESPACE

#include "ak47_PinChangeInterrupts.hpp"
