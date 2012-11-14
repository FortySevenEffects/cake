/*!
 *  \file       ak47_BadIsrCatcher.cpp
 *  \author     Francois Best
 *  \date       23/10/2012
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

#include "ak47.h"
#include <avr/interrupt.h>

BEGIN_AK47_NAMESPACE

END_AK47_NAMESPACE

// -----------------------------------------------------------------------------

ISR(BADISR_vect) 
{
    // You have enabled an interrupt, but did not implement an ISR for it.
    // Zombie interrupts come here to die.
    AVR_ASSERT_FALSE();
}
