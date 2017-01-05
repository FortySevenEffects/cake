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
