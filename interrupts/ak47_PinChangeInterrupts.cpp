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

BEGIN_AK47_NAMESPACE

PinChangeListener::PinChangeListener()
{
}

PinChangeListener::~PinChangeListener()
{
}

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
