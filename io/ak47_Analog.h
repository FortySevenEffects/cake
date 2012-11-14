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
#include "interrupts/ak47_Atomic.h"

BEGIN_AK47_NAMESPACE

class Adc
{
public:
    static inline void enable();
    static inline void disable();
    
public:
    static inline void start(byte inChannel);
    static inline uint16 read(byte inChannel);

private:
    static uint16 sBufferredValue;
};

END_AK47_NAMESPACE

#include "io/ak47_Analog.hpp"
