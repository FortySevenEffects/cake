/*!
 *  \file       ak47_I2C_Devices.h
 *  \author     Francois Best
 *  \date       11/11/2012
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
#include "memory/ak47_Register.h"

BEGIN_AK47_NAMESPACE

#if defined TWI_vect
#   if  !defined(TWCR) ||   \
        !defined(TWSR) ||   \
        !defined(TWDR) ||   \
        !defined(TWAR) ||   \
        !defined(TWBR) ||   \
        !defined(TWAMR)
#       error I2C registers not found for this target chip.
#   endif
    AVR_REGISTER(TWCR, I2cControlRegister);
#else
#   define NO_I2C
#endif

END_AK47_NAMESPACE
