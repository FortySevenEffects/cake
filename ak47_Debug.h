/*!
 *  \file       ak47_Debug.h
 *  \author     Francois Best
 *  \date       09/11/2012
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

#include "ak47_Namespace.h"

BEGIN_AK47_NAMESPACE

class Debug
{
public:
    typedef void (*PrintCallback)(char);
    
public:
    static inline void print(char inChar);
    static inline void print(const char* inString);
    static inline void setDevice(PrintCallback inCallback);
    
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
