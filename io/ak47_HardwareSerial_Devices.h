/*!
 *  \file       ak47_HardwareSerial_Devices.h
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

// -----------------------------------------------------------------------------
// Hardware Abstraction

#if defined (__AVR_ATmega644P__)
#   define UART0
#   define UART1
#elif defined (__AVR_ATmega32U4__)
#   define UART1
#elif defined (__AVR_ATtiny84__)
#   define NO_UART  // No UART available
#else
#   error Implement abstraction for this target chip.
#endif

END_AK47_NAMESPACE
