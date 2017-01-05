#pragma once

#include "cake.h"
#include <util/atomic.h>
#include <avr/interrupt.h>

BEGIN_CAKE_NAMESPACE

struct ScopedInterruptLock
{
    inline  ScopedInterruptLock();
    inline ~ScopedInterruptLock();
};

struct ScopedInterruptUnlock
{
    inline  ScopedInterruptUnlock();
    inline ~ScopedInterruptUnlock();
};

END_CAKE_NAMESPACE

#include "interrupts/cake_Atomic.hpp"
