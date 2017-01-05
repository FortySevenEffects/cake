#pragma once

#include "cake.h"
#include <avr/interrupt.h>

BEGIN_CAKE_NAMESPACE

template<class Traits>
class ExternalInterrupt
{
public:
    enum TriggerMode
    {
          lowLevel = 0
        , bothEdges
        , fallingEdge
        , risingEdge
    };

public:
    inline  ExternalInterrupt();
    inline ~ExternalInterrupt();

public:
    static inline void enable();
    static inline void disable();

public:
    static inline void setTriggerOn(TriggerMode inMode);
};

END_CAKE_NAMESPACE

#include "interrupts/cake_ExternalInterrupt.hpp"
