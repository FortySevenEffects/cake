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
#include <avr/io.h>

BEGIN_AK47_NAMESPACE

#if defined (__AVR_ATmega644P__) || defined (__AVR_ATmega32U4__)
#   define I2C_REG_CTRL         TWCR
#   define I2C_REG_STAT         TWSR
#   define I2C_REG_DATA         TWDR
#   define I2C_REG_ADDR         TWAR
#   define I2C_REG_MASK         TWAMR
#   define I2C_REG_RATE         TWBR
#elif defined (__AVR_ATtiny84__)
#   define NO_I2C // Not support for USI yet.
#else
#   error Implement abstraction for this target chip.
#endif

END_AK47_NAMESPACE
