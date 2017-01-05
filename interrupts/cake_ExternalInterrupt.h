/*!
 *  \file       cake_ExternalInterrupt.h
 *  \author     Francois Best
 *  \date       16/10/2013
 *  \license    GPL v3.0 - Copyright Forty Seven Effects 2013
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

#include "cake.h"
#include <avr/interrupt.h>

BEGIN_CAKE_NAMESPACE

template<class Traits>
class ExternalInterrupt
{
public:
    enum TriggerMode
    {
          lowLevel = 0
        , bothEdges
        , fallingEdge
        , risingEdge
    };

public:
    inline  ExternalInterrupt();
    inline ~ExternalInterrupt();

public:
    static inline void enable();
    static inline void disable();

public:
    static inline void setTriggerOn(TriggerMode inMode);
};

END_CAKE_NAMESPACE

#include "interrupts/cake_ExternalInterrupt.hpp"
