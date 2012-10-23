/*!
 *  \file       ak47_PinChangeInterrupts.h
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
