/*!
 *  \file       ak47_Timer.h
 *  \author     Francois Best
 *  \date       02/12/2012
 *  \license    GPL v3.0 - Copyright Forty Seven Effects 2012
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "ak47.h"
#include <avr/io.h>

BEGIN_AK47_NAMESPACE

template<byte TimerId, byte Bits>
struct TimerTraits;

template<byte TimerId>
struct TimerTraits<TimerId, 8>
{
    typedef uint8           Value;
    typedef volatile uint8* ControlRegister;
    typedef volatile Value* DataRegister;

    static inline ControlRegister   getTCCRA();
    static inline ControlRegister   getTCCRB();
    static inline ControlRegister   getTIMSK();
    static inline DataRegister      getOCRA();
    static inline DataRegister      getOCRB();
    static inline DataRegister      getTCNT();

    static inline byte getInterruptMaskA();
    static inline byte getInterruptMaskB();
    static inline byte getInterruptMaskOverflow();
};

template<byte TimerId>
struct TimerTraits<TimerId, 16>
{
    typedef uint16          Value;
    typedef volatile uint8* ControlRegister;
    typedef volatile Value* DataRegister;

    static inline ControlRegister   getTCCRA();
    static inline ControlRegister   getTCCRB();
    static inline ControlRegister   getTIMSK();
    static inline DataRegister      getOCRA();
    static inline DataRegister      getOCRB();
    static inline DataRegister      getTCNT();

    static inline byte getInterruptMaskA();
    static inline byte getInterruptMaskB();
    static inline byte getInterruptMaskOverflow();
};

// -----------------------------------------------------------------------------

template<byte TimerId, byte Bits>
class Timer
{
public:
    enum 
    {
          prescale1       = 1
        , prescale8       = 2
        , prescale64      = 3
        , prescale256     = 4
        , prescale1024    = 5
    };

    enum
    {
          compareOutputDisconnected     = 0
        , compareOutputToggle           = 1
        , compareOutputClear            = 2
        , compareOutputSet              = 3
    };

    typedef uint8                       Prescale;
    typedef uint8                       CompareOutputMode;
    typedef uint8                       Mode;
    typedef TimerTraits<TimerId, Bits>  Traits;
    typedef typename Traits::Value      Value;
    
public:
    inline  Timer();
    inline ~Timer();

public:
    static inline void enableInterruptA();
    static inline void enableInterruptB();
    static inline void enableInterruptOverflow();

    static inline void disableInterruptA();
    static inline void disableInterruptB();
    static inline void disableInterruptOverflow();

public:
    static inline void setCompareOutputModeA(CompareOutputMode inMode);
    static inline void setCompareOutputModeB(CompareOutputMode inMode);
    static inline void setMode(Mode inMode);

public:
    static inline void start(Prescale inPrescale = prescale1);
    static inline void stop();
    static inline void reset();

public:
    static inline void setPrescale(Prescale inPrescale);    

public:
    static inline Value getValue();
    static inline void setValue(Value inValue);

public:
    static inline void setA(Value inValue);
    static inline void setB(Value inValue);
};

END_AK47_NAMESPACE

#include "time/ak47_Timer.hpp"
