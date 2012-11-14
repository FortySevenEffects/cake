/*!
 *  \file       ak47_Debug.h
 *  \author     Francois Best
 *  \date       09/11/2012
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

#include "ak47_Namespace.h"
#include "ak47_Defs.h"

BEGIN_AK47_NAMESPACE

class Debug
{
public:
    AVR_TYPEDEF_FUNCTOR(void, PrintCallback, char);
    
public:
    static inline void print(char inChar);
    static inline void print(const char* inString);
    static inline void setPrintCallback(PrintCallback inCallback);
    
private:
    static PrintCallback mPrintCallback;
};

END_AK47_NAMESPACE

// -----------------------------------------------------------------------------

#ifndef AK47_NO_TRACE
#   include <avr/io.h>
#   define AVR_START_TRACE(port, pin)   { DDR##port  |=  (1 << pin); }
#   define AVR_STOP_TRACE(port, pin)    { DDR##port  &= ~(1 << pin); }
#   define AVR_TRACE_ON(port, pin)      { PORT##port |=  (1 << pin); }
#   define AVR_TRACE_OFF(port, pin)     { PORT##port &= ~(1 << pin); }
#   define AVR_TRACE_PULSE(port, pin)   { PIN##port |= (1 << pin);             \
                                          PIN##port |= (1 << pin); }
#else
#   define AVR_START_TRACE(...)
#   define AVR_STOP_TRACE(...)
#   define AVR_TRACE_ON(...)
#   define AVR_TRACE_OFF(...)
#   define AVR_TRACE_PULSE(...)
#endif

// -----------------------------------------------------------------------------

#include "ak47_Debug.hpp"
