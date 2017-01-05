#pragma once

#include "cake.h"
#include "io/cake_Gpio.h"
#include <avr/interrupt.h>

BEGIN_CAKE_NAMESPACE

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

END_CAKE_NAMESPACE

#include "cake_PinChangeInterrupts.hpp"
