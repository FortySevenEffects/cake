#pragma once

BEGIN_CAKE_NAMESPACE

inline ScopedInterruptLock::ScopedInterruptLock()
{
    cli();
}

inline ScopedInterruptLock::~ScopedInterruptLock()
{
    sei();
}

// -----------------------------------------------------------------------------

inline ScopedInterruptUnlock::ScopedInterruptUnlock()
{
    sei();
}

inline ScopedInterruptUnlock::~ScopedInterruptUnlock()
{
    cli();
}

END_CAKE_NAMESPACE
