/*!
 *  \file       cake_Eeprom.cpp
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

#include "memory/cake_Eeprom.h"
#include <avr/interrupt.h>

BEGIN_CAKE_NAMESPACE

Eeprom::EepromReadyCallback Eeprom::sClientCallback = 0;

END_CAKE_NAMESPACE

// -----------------------------------------------------------------------------

#if   defined (EE_READY_vect)
#   define EEPROM_ISR EE_READY_vect
#elif defined (EEPROM_READY_vect)
#   define EEPROM_ISR EEPROM_READY_vect
#elif defined (EE_RDY_vect)
#   define EEPROM_ISR EE_RDY_vect
#endif

ISR(EEPROM_ISR)
{
    if (cake::Eeprom::sClientCallback != 0)
    {
        cake::Eeprom::sClientCallback();
    }
}
