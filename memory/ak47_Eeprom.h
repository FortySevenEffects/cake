/*!
 *  \file       ak47_Eeprom.h
 *  \author     Francois Best
 *  \date       27/10/2012
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
#include <avr/eeprom.h>

// -----------------------------------------------------------------------------

#define AVR_EEPROM_SECTION  __attribute__((section(".eeprom")))

// -----------------------------------------------------------------------------

BEGIN_AK47_NAMESPACE

class Eeprom
{
public:
    static inline byte read(uint16 inAddress);
    
    static inline void write(uint16 inAddress, byte inData);
    static inline void write(uint16 inAddress,
                             const byte* inData,
                             uint16 inSize);
    
public:
    static const uint16 sEepromSize;
};

END_AK47_NAMESPACE

#include "memory/ak47_Eeprom.hpp"
