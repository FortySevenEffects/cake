/*!
 *  \file       ak47_Analog.cpp
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

#include "io/ak47_Analog.h"

BEGIN_AK47_NAMESPACE

void Adc::checkRegisterStructure()
{
    // ADMUX register structure
    AVR_STATIC_ASSERT(REFS1 == 7);
    AVR_STATIC_ASSERT(REFS0 == 6);

    // ADCSRA register structure
    AVR_STATIC_ASSERT(ADEN  == 7);
    AVR_STATIC_ASSERT(ADSC  == 6);
    AVR_STATIC_ASSERT(ADATE == 5);
    AVR_STATIC_ASSERT(ADIF  == 4);
    AVR_STATIC_ASSERT(ADIE  == 3);
    AVR_STATIC_ASSERT(ADPS2 == 2);
    AVR_STATIC_ASSERT(ADPS1 == 1);
    AVR_STATIC_ASSERT(ADPS0 == 0);
}

END_AK47_NAMESPACE
