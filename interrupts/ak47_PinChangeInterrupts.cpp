/*!
 *  \file       ak47_PinChangeInterrupts.cpp
 *  \author     Francois Best
 *  \date       23/10/2012
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

#include "ak47_PinChangeInterrupts.h"
#include "memory/ak47_Memory.h"

BEGIN_AK47_NAMESPACE

PinChangeListener::PinChangeListener()
{
}

PinChangeListener::~PinChangeListener()
{
}

// -----------------------------------------------------------------------------

#if defined(__AVR_ATmega644P__)
    AVR_REGISTER(PCICR,     PinChangeControl);
    AVR_REGISTER(PINA,      PinChangeRead0);
    AVR_REGISTER(PINB,      PinChangeRead1);
    AVR_REGISTER(PINC,      PinChangeRead2);
    AVR_REGISTER(PIND,      PinChangeRead3);
    AVR_REGISTER(PCMSK0,    PinChangeMask0);
    AVR_REGISTER(PCMSK1,    PinChangeMask1);
    AVR_REGISTER(PCMSK2,    PinChangeMask2);
    AVR_REGISTER(PCMSK3,    PinChangeMask3);
#elif defined(__AVR_ATmega328P__)
    AVR_REGISTER(PCICR,     PinChangeControl);
    AVR_REGISTER(PINB,      PinChangeRead0);
    AVR_REGISTER(PINC,      PinChangeRead1);
    AVR_REGISTER(PIND,      PinChangeRead2);
    AVR_REGISTER(PCMSK0,    PinChangeMask0);
    AVR_REGISTER(PCMSK1,    PinChangeMask1);
    AVR_REGISTER(PCMSK2,    PinChangeMask2);
#elif defined(__AVR_ATmega32U4__)
    AVR_REGISTER(PCICR,     PinChangeControl);
    AVR_REGISTER(PINB,      PinChangeRead0);
    AVR_REGISTER(PCMSK0,    PinChangeMask0);
#elif defined(__AVR_ATtiny84__)
    AVR_REGISTER(GIMSK,     PinChangeControl);
    AVR_REGISTER(PINA,      PinChangeRead0);
    AVR_REGISTER(PINB,      PinChangeRead1);
    AVR_REGISTER(PCMSK0,    PinChangeMask0);
    AVR_REGISTER(PCMSK1,    PinChangeMask1);
#else
#   error Implement abstraction for this chip.
#endif

// -----------------------------------------------------------------------------

#ifdef PCINT0_vect
template<>
void PortChangeListener<0>::registerInterrupt(PinNumber inPin)
{
    PinChangeControl.set(PCIE0);
    PinChangeMask0.set(inPin);
}
#endif

#ifdef PCINT1_vect
template<>
void PortChangeListener<1>::registerInterrupt(PinNumber inPin)
{
    PinChangeControl.set(PCIE1);
    PinChangeMask1.set(inPin);
}
#endif

#ifdef PCINT2_vect
template<>
void PortChangeListener<2>::registerInterrupt(PinNumber inPin)
{
    PinChangeControl.set(PCIE2);
    PinChangeMask2.set(inPin);
}
#endif

#ifdef PCINT3_vect
template<>
void PortChangeListener<3>::registerInterrupt(PinNumber inPin)
{
    PinChangeControl.set(PCIE3);
    PinChangeMask3.set(inPin);
}
#endif

// -----------------------------------------------------------------------------

#ifdef PCINT0_vect
template<>
void PortChangeListener<0>::unregisterInterrupt(PinNumber inPin)
{
    PinChangeMask0.clear(inPin);
    if (PinChangeMask0 == 0)
    {
        PinChangeControl.clear(PCIE0);
    }
}
#endif

#ifdef PCINT1_vect
template<>
void PortChangeListener<1>::unregisterInterrupt(PinNumber inPin)
{
    PinChangeMask1.clear(inPin);
    if (PinChangeMask1 == 0)
    {
        PinChangeControl.clear(PCIE1);
    }
}
#endif

#ifdef PCINT2_vect
template<>
void PortChangeListener<2>::unregisterInterrupt(PinNumber inPin)
{
    PinChangeMask2.clear(inPin);
    if (PinChangeMask2 == 0)
    {
        PinChangeControl.clear(PCIE2);
    }
}
#endif

#ifdef PCINT3_vect
template<>
void PortChangeListener<3>::unregisterInterrupt(PinNumber inPin)
{
    PinChangeMask2.clear(inPin);
    if (PinChangeMask2 == 0)
    {
        PinChangeControl.clear(PCIE2);
    }
}
#endif

// -----------------------------------------------------------------------------

#ifdef PCINT0_vect
template<>
void PortChangeListener<0>::handlePortInterrupt()
{
    dispatchInterrupt(PinChangeRead0());
}
#endif

#ifdef PCINT1_vect
template<>
void PortChangeListener<1>::handlePortInterrupt()
{
    dispatchInterrupt(PinChangeRead1());
}
#endif

#ifdef PCINT2_vect
template<>
void PortChangeListener<2>::handlePortInterrupt()
{
    dispatchInterrupt(PinChangeRead2());
}
#endif

#ifdef PCINT3_vect
template<>
void PortChangeListener<3>::handlePortInterrupt()
{
    dispatchInterrupt(PinChangeRead3());
}
#endif

// -----------------------------------------------------------------------------

#if defined (PCINT0_vect) || defined (PCINT_vect)
PortChangeListener<0> listener0;
#endif

#ifdef PCINT1_vect
PortChangeListener<1> listener1;
#endif

#ifdef PCINT2_vect
PortChangeListener<2> listener2;
#endif

#ifdef PCINT3_vect
PortChangeListener<3> listener3;
#endif

// -----------------------------------------------------------------------------

#if defined (PCINT0_vect) || defined (PCINT_vect)
PortChangeListener<0>* getPortChangeListener0()
{
    return &listener0;
}
#endif

#ifdef PCINT1_vect
PortChangeListener<1>* getPortChangeListener1()
{
    return &listener1;
}
#endif

#ifdef PCINT2_vect
PortChangeListener<2>* getPortChangeListener2()
{
    return &listener2;
}
#endif

#ifdef PCINT3_vect
PortChangeListener<3>* getPortChangeListener3()
{
    return &listener3;
}
#endif

// -----------------------------------------------------------------------------

#ifdef PCINT_vect
ISR(PCINT_vect)
{
    listener0.handlePortInterrupt();
}
#endif

#ifdef PCINT0_vect
ISR(PCINT0_vect)
{
    listener0.handlePortInterrupt();
}
#endif

#ifdef PCINT1_vect
ISR(PCINT1_vect)
{
    listener1.handlePortInterrupt();
}
#endif

#ifdef PCINT2_vect
ISR(PCINT2_vect)
{
    listener2.handlePortInterrupt();
}
#endif

#ifdef PCINT3_vect
ISR(PCINT3_vect)
{
    listener3.handlePortInterrupt();
}
#endif

#ifdef PCINT4_vect
#   error Implement more PCINT handlers.
#endif

#if defined (PCINT_vect)
#   error Implement for this chip.
#endif

END_AK47_NAMESPACE
