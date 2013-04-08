/*!
 *  \file       ak47_Spi.cpp
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

#include "io/ak47_Spi.h"
#include <avr/interrupt.h>

BEGIN_AK47_NAMESPACE

Spi spi;

Spi::Spi()
{
}

Spi::~Spi()
{
}

END_AK47_NAMESPACE

// -----------------------------------------------------------------------------

ISR(SPI_STC_vect)
{
    ak47::spi.handleInterrupt();
}
