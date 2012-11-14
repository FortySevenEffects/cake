/*!
 *  \file       ak47_Eeprom.cpp
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

#include "memory/ak47_Eeprom.h"

BEGIN_AK47_NAMESPACE

#if E2END
const uint16 Eeprom::sEepromSize = E2END;
#else
const uint16 Eeprom::sEepromSize = 0;
#endif

END_AK47_NAMESPACE
