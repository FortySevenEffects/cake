/*!
 *  \file       ak47_Eeprom.h
 *  \author     Francois Best
 *  \date       27/10/2012
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
#include <avr/eeprom.h>

// -----------------------------------------------------------------------------

#define AVR_EEPROM_SECTION  __attribute__((section(".eeprom")))

#ifndef E2END
#define E2END 0
#endif

// -----------------------------------------------------------------------------

BEGIN_AK47_NAMESPACE

class Eeprom
{
public:
    AVR_TYPEDEF_FUNCTOR(void, EepromReadyCallback, void);
    static const uint16 sEepromSize = E2END;
    
public:
    static inline byte read(uint16 inAddress);
    
    static inline void write(uint16 inAddress, byte inData);
    static inline void writeNoBlock(uint16 inAddress, byte inData);
    static inline void write(uint16 inAddress,
                             const byte* inData,
                             uint16 inSize);
    
    static inline void setClientCallback(EepromReadyCallback inCallback);
    
public: // For the ISR only, not for public use
    static EepromReadyCallback sClientCallback;
};

END_AK47_NAMESPACE

#include "memory/ak47_Eeprom.hpp"
