/*!
 *  \file       cake_Register.h
 *  \author     Francois Best
 *  \date       16/11/2012
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
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "cake.h"
#include <avr/io.h>

BEGIN_CAKE_NAMESPACE

template <typename Reg>
struct Register
{
    inline void set(byte inBit);
    inline void clear(byte inBit);

    inline Register& operator=(const byte& inValue);
    inline byte operator() ();
    inline operator byte() const;
};

// -----------------------------------------------------------------------------

// This macro is inspired by the works of Olivier Gillet for his avril library,
// available here: https://github.com/pichenettes/avril
#define AVR_REGISTER(reg, name)                                                 \
    struct reg##Register                                                        \
    {                                                                           \
        static inline volatile byte* ptr() { return &(reg); }                   \
    };                                                                          \
    Register<reg##Register> name;

// -----------------------------------------------------------------------------

typedef volatile uint8*     RegisterAddress;
typedef volatile uint8*     RegisterAddress8;
typedef volatile uint16*    RegisterAddress16;

END_CAKE_NAMESPACE

#include "memory/cake_Register.hpp"
