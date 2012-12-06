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

BEGIN_AK47_NAMESPACE

struct TimerPrescale
{
    enum 
    {
          timer_Prescale1       = 1
        , timer_Prescale8       = 2
        , timer_Prescale64      = 3
        , timer_Prescale256     = 4
        , timer_Prescale1024    = 5
    };
};

// -----------------------------------------------------------------------------

template<int TimerId>
class Timer8
{
public:
    AVR_TYPEDEF_FUNCTOR(void, TimerCallback, void);
    
public:
     Timer8();
    ~Timer8();
    
public:
    inline void setLength(byte inLenght);
    inline void setPrescale(byte inPrescale);
    
public:
    inline void setCallbackA(TimerCallback inCallback);
    inline void setCallbackB(TimerCallback inCallback);
    
public:
    inline void start(bool inOneShot = false);
    inline void pause();
    inline void stop();
    inline void reset();
    
private:
    TimerCallback mCallbackA;
    TimerCallback mCallbackB;
    byte mFlags;
};

// -----------------------------------------------------------------------------

class Timer16
{
    
};

END_AK47_NAMESPACE

#include "time/ak47_Timer.hpp"
