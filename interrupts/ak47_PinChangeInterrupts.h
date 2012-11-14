/*!
 *  \file       ak47_PinChangeInterrupts.h
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

#include "ak47.h"
#include "ak47_Types.h"
#include <avr/interrupt.h>
#include <avr/io.h>

BEGIN_AK47_NAMESPACE

// -----------------------------------------------------------------------------

/*! \brief Inherit from this class to be notified of pin changes. */
class PinChangeListener
{
public:
    explicit PinChangeListener();
    virtual ~PinChangeListener();
    
public:
    virtual void operator() (bool inPinState) = 0;
};

// -----------------------------------------------------------------------------

template<int PortId>
class PortChangeListener
{
protected:
    typedef volatile byte PortValue;
    typedef byte PinNumber;
    
public:
    explicit PortChangeListener();
    virtual ~PortChangeListener();
    
public:
    inline void attachPinListener(PinChangeListener* inListener,
                                  PinNumber inPinToAttachTo);
    inline void detachPinListener(PinChangeListener* inListener);
    inline void detachPinListener(PinNumber inPinToDetach);
    
public:
    inline void registerInterrupt(PinNumber inPin);
    inline void unregisterInterrupt(PinNumber inPin);
    inline void handlePortInterrupt();
    
protected:
    inline void dispatchInterrupt(PortValue inCurrentPortValue);
    
    PinChangeListener* mListeners[8];
    PortValue mPreviousPortValue;
};

// -----------------------------------------------------------------------------

#ifdef PCINT0_vect
PortChangeListener<0>* getPortChangeListener0();
#endif

#ifdef PCINT1_vect
PortChangeListener<1>* getPortChangeListener1();
#endif

#ifdef PCINT2_vect
PortChangeListener<2>* getPortChangeListener2();
#endif

#ifdef PCINT3_vect
PortChangeListener<3>* getPortChangeListener3();
#endif

// -----------------------------------------------------------------------------

END_AK47_NAMESPACE

#include "ak47_PinChangeInterrupts.hpp"
