/*!
 *  \file       ak47_PinChangeInterrupts.hpp
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

#pragma once

BEGIN_AK47_NAMESPACE

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

template<byte PortId>
PortChangeListener<PortId>::PortChangeListener()
{
    for (byte i = 0; i < 8; ++i)
        mListeners[i] = 0;
}

template<byte PortId>
PortChangeListener<PortId>::~PortChangeListener()
{
    for (byte i = 0; i < 8; ++i)
        detachPinListener(i);
}

// -----------------------------------------------------------------------------

template<byte PortId>
void PortChangeListener<PortId>::attachPinListener(PinChangeListener* inListener,
                                                   PinNumber inPin)
{
    if (inListener != 0)
    {
        if (mListeners[inPin] != 0)
        {
            detachPinListener(inPin);
        }
        
        mListeners[inPin] = inListener;
        registerInterrupt(inPin);
    }
}

template<byte PortId>
void PortChangeListener<PortId>::detachPinListener(PinChangeListener* inListener)
{
    for (byte i = 0; i < 8; ++i)
    {
        if (mListeners[i] == inListener)
        {
            unregisterInterrupt(i);
            mListeners[i] = 0;
            break;
        }
    }
}

template<byte PortId>
void PortChangeListener<PortId>::detachPinListener(PinNumber inPin)
{
    unregisterInterrupt(inPin);
    mListeners[inPin] = 0;
}

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

template<byte PortId>
void PortChangeListener<PortId>::dispatchInterrupt(PortValue inValue)
{
    const PortValue diff = mPreviousPortValue ^ inValue;
    mPreviousPortValue = inValue;
    for (byte i = 0; i < 8; ++i)
    {
        if (diff & (1 << i) && mListeners[i] != 0)
        {
            (*mListeners[i])(inValue & (1 << i));
        }
    }
}

END_AK47_NAMESPACE
