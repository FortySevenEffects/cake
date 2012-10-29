/*!
 *  \file       ak47_PinChangeInterrupts.cpp
 *  \author     Francois Best
 *  \date       23/10/2012
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
