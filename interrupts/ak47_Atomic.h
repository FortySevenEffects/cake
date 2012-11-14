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
#include "ak47_Types.h"
#include <util/atomic.h>
#include <avr/interrupt.h>

// -----------------------------------------------------------------------------

#define AVR_BEGIN_ATOMIC_BLOCK  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
#define AVR_END_ATOMIC_BLOCK    }

// -----------------------------------------------------------------------------

#define AVR_STD_CONTEXT         0   // Standard context (runtime)
#define AVR_INT_CONTEXT         1   // Interrupt context (ISR)

#define AVR_SET_INT_CONTEXT     //ak47::sContext = AVR_INT_CONTEXT;
#define AVR_SET_STD_CONTEXT     //ak47::sContext = AVR_STD_CONTEXT;

// -----------------------------------------------------------------------------

#if defined (AVR_TRACE) && ( defined (DEBUG) || defined (_DEBUG) )
#   define AVR_BEGIN_ISR(id)    { AVR_SET_INT_CONTEXT; AVR_BEGIN_TRACE(id); }
#   define AVR_END_ISR(id)      { AVR_SET_STD_CONTEXT; AVR_END_TRACE(id); }
#else
#   define AVR_BEGIN_ISR(...)   { AVR_SET_INT_CONTEXT; }
#   define AVR_END_ISR(...)     { AVR_SET_STD_CONTEXT; }
#endif

BEGIN_AK47_NAMESPACE

END_AK47_NAMESPACE

#include "interrupts/ak47_Atomic.hpp"
