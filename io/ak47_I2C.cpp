/*!
 *  \file       ak47_I2C.cpp
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

#include "io/ak47_I2C.h"

BEGIN_AK47_NAMESPACE

byte I2C::sExpected = 0;

// -----------------------------------------------------------------------------

#ifdef TWI_vect
ISR(TWI_vect)
{
    I2C::interruptCallback();
}
#endif

END_AK47_NAMESPACE
