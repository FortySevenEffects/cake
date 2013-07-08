/*!
 *  \file       ak47_Atomic.h
 *  \author     Francois Best
 *  \date       29/10/2012
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
#include <util/atomic.h>
#include <avr/interrupt.h>

// -----------------------------------------------------------------------------

BEGIN_AK47_NAMESPACE

struct Atomic
{
    enum
    {
        Main = 0,
        Interrupt,
    };

    template<byte Context>
    static inline void setContext();

    static inline bool isContext(byte inContext);

private:
    static byte mContext;
};

END_AK47_NAMESPACE

// -----------------------------------------------------------------------------

#define AVR_BEGIN_ATOMIC_BLOCK      ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
#define AVR_END_ATOMIC_BLOCK        }

// -----------------------------------------------------------------------------

#if AVR_DEBUG
#   define AVR_BEGIN_ISR(port, pin)                                             \
    {                                                                           \
        AVR_TRACE_ON(port, pin);                                                \
        Atomic::setContext<Atomic::Interrupt>();                                \
    }
#   define AVR_END_ISR(port, pin)                                               \
    {                                                                           \
        Atomic::setContext<Atomic::Main>();                                     \
        AVR_TRACE_OFF(port, pin);                                               \
    }
#else
#   define AVR_BEGIN_ISR(...)
#   define AVR_END_ISR(...)
#endif

#include "interrupts/ak47_Atomic.hpp"
