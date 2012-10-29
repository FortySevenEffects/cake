/*!
 *  \file       ak47_Atomic.h
 *  \author     Francois Best
 *  \date       29/10/2012
 *  \license    CC-BY-SA Forty Seven Effects - 2012
 *
 * THE WORK (AS DEFINED BELOW) IS PROVIDED UNDER THE TERMS 
 * OF THIS CREATIVE COMMONS PUBLIC LICENSE ("CCPL" OR "LICENSE").
 * THE WORK IS PROTECTED BY COPYRIGHT AND/OR OTHER APPLICABLE LAW. 
 * ANY USE OF THE WORK OTHER THAN AS AUTHORIZED UNDER THIS LICENSE 
 * OR COPYRIGHT LAW IS PROHIBITED.
 * 
 * BY EXERCISING ANY RIGHTS TO THE WORK PROVIDED HERE, YOU ACCEPT 
 * AND AGREE TO BE BOUND BY THE TERMS OF THIS LICENSE. 
 * TO THE EXTENT THIS LICENSE MAY BE CONSIDERED TO BE A CONTRACT, 
 * THE LICENSOR GRANTS YOU THE RIGHTS CONTAINED HERE IN CONSIDERATION 
 * OF YOUR ACCEPTANCE OF SUCH TERMS AND CONDITIONS.
 * http://creativecommons.org/licenses/by-sa/3.0/
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
