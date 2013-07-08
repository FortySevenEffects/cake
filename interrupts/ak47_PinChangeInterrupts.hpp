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
