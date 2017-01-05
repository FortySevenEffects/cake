#pragma once

#include "cake_Namespace.h"
#include "cake_Defs.h"

BEGIN_CAKE_NAMESPACE

class Debug
{
public:
    AVR_TYPEDEF_FUNCTOR(void, PrintCallback, char);

public:
    static inline void print(char inChar);
    static inline void print(const char* inString);
    static inline void printNumber(long inNum);

    static inline void log(const char* inString);
    static inline void setPrintCallback(PrintCallback inCallback);

private:
    static PrintCallback mPrintCallback;
};

#define AVR_DBG(str) cake::Debug::print(str)

END_CAKE_NAMESPACE

// -----------------------------------------------------------------------------

#ifndef CAKE_NO_TRACE
#   define AVR_TRACE
#   include <avr/io.h>
#   define AVR_START_TRACE(port, pin)   { DDR##port  |=  (1 << pin); }
#   define AVR_STOP_TRACE(port, pin)    { DDR##port  &= ~(1 << pin); }
#   define AVR_TRACE_ON(port, pin)      { PORT##port |=  (1 << pin); }
#   define AVR_TRACE_OFF(port, pin)     { PORT##port &= ~(1 << pin); }
#   define AVR_TRACE_PULSE(port, pin)   { PIN##port |= (1 << pin);             \
                                          PIN##port |= (1 << pin); }
#else
#   define AVR_START_TRACE(port, pin)
#   define AVR_STOP_TRACE(port, pin)
#   define AVR_TRACE_ON(port, pin)
#   define AVR_TRACE_OFF(port, pin)
#   define AVR_TRACE_PULSE(port, pin)
#endif

// Aliases
#define AVR_BEGIN_TRACE(port, pin)    AVR_START_TRACE(port, pin)
#define AVR_END_TRACE(port, pin)      AVR_STOP_TRACE(port, pin)
#define AVR_TRACE_HIGH(port, pin)     AVR_TRACE_ON(port, pin)
#define AVR_TRACE_LOW(port, pin)      AVR_TRACE_OFF(port, pin)

// -----------------------------------------------------------------------------

#include "cake_Debug.hpp"
