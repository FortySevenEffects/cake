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
#   define PCINT_CTL_REG        PCICR
#   define PCINT_READ_0         PINA
#   define PCINT_READ_1         PINB
#   define PCINT_READ_2         PINC
#   define PCINT_READ_3         PIND
#elif defined(__AVR_ATmega32U4__)
#   define PCINT_CTL_REG        PCICR
#   define PCINT_READ_0         PINB
#elif defined(__AVR_ATtiny84__)
#   define PCINT_CTL_REG        GIMSK
#   define PCINT_READ_0         PINA
#   define PCINT_READ_1         PINB
#else
#   error Implement abstraction for this chip.
#endif

// -----------------------------------------------------------------------------

template<int PortId>
PortChangeListener<PortId>::PortChangeListener()
{
    for (byte i = 0; i < 8; ++i)
        mListeners[i] = 0;
}

template<int PortId>
PortChangeListener<PortId>::~PortChangeListener()
{
    for (byte i = 0; i < 8; ++i)
        detachPinListener(i);
}

// -----------------------------------------------------------------------------

template<int PortId>
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

template<int PortId>
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

template<int PortId>
void PortChangeListener<PortId>::detachPinListener(PinNumber inPin)
{
    unregisterInterrupt(inPin);
    mListeners[inPin] = 0;
}

// -----------------------------------------------------------------------------

#ifdef PCINT0_vect
template<>
void PortChangeListener<0>::registerInterrupt(byte inPin)
{
    PCINT_CTL_REG |= (1 << PCIE0);
    PCMSK0 |= (1 << inPin);
}
#endif

#ifdef PCINT1_vect
template<>
void PortChangeListener<1>::registerInterrupt(byte inPin)
{
    PCINT_CTL_REG |= (1 << PCIE1);
    PCMSK1 |= (1 << inPin);
}
#endif

#ifdef PCINT2_vect
template<>
void PortChangeListener<2>::registerInterrupt(byte inPin)
{
    PCINT_CTL_REG |= (1 << PCIE2);
    PCMSK2 |= (1 << inPin);
}
#endif

#ifdef PCINT3_vect
template<>
void PortChangeListener<3>::registerInterrupt(byte inPin)
{
    PCINT_CTL_REG |= (1 << PCIE3);
    PCMSK3 |= (1 << inPin);
}
#endif

// -----------------------------------------------------------------------------

#ifdef PCINT0_vect
template<>
void PortChangeListener<0>::unregisterInterrupt(byte inPin)
{
    PCMSK0 &= ~(1 << inPin);
    if (PCMSK0 == 0)
        PCINT_CTL_REG &= ~(1 << PCIE0);
}
#endif

#ifdef PCINT1_vect
template<>
void PortChangeListener<1>::unregisterInterrupt(byte inPin)
{
    PCMSK1 &= ~(1 << inPin);
    if (PCMSK1 == 0)
        PCINT_CTL_REG &= ~(1 << PCIE1);
}
#endif

#ifdef PCINT2_vect
template<>
void PortChangeListener<2>::unregisterInterrupt(byte inPin)
{
    PCMSK2 &= ~(1 << inPin);
    if (PCMSK2 == 0)
        PCINT_CTL_REG &= ~(1 << PCIE2);
}
#endif

#ifdef PCINT3_vect
template<>
void PortChangeListener<3>::unregisterInterrupt(byte inPin)
{
    PCMSK3 &= ~(1 << inPin);
    if (PCMSK3 == 0)
        PCINT_CTL_REG &= ~(1 << PCIE3);
}
#endif

// -----------------------------------------------------------------------------

#ifdef PCINT0_vect
template<>
void PortChangeListener<0>::handlePortInterrupt()
{
    dispatchInterrupt(PCINT_READ_0);
}
#endif

#ifdef PCINT1_vect
template<>
void PortChangeListener<1>::handlePortInterrupt()
{
    dispatchInterrupt(PCINT_READ_1);
}
#endif

#ifdef PCINT2_vect
template<>
void PortChangeListener<2>::handlePortInterrupt()
{
    dispatchInterrupt(PCINT_READ_2);
}
#endif

#ifdef PCINT3_vect
template<>
void PortChangeListener<3>::handlePortInterrupt()
{
    dispatchInterrupt(PCINT_READ_3);
}
#endif

// -----------------------------------------------------------------------------

template<int PortId>
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

// -----------------------------------------------------------------------------

#ifdef      PCINT_CTL_REG
#   undef   PCINT_CTL_REG
#endif

#ifdef      PCINT_READ_0
#   undef   PCINT_READ_0
#endif

#ifdef      PCINT_READ_1
#   undef   PCINT_READ_1
#endif

#ifdef      PCINT_READ_2
#   undef   PCINT_READ_2
#endif

#ifdef      PCINT_READ_3
#   undef   PCINT_READ_3
#endif

END_AK47_NAMESPACE
