/*!
 *  \file       ak47_Atomic.cpp
 *  \author     Francois Best
 *  \date       29/10/2012
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

#include "interrupts/ak47_Atomic.h"

BEGIN_AK47_NAMESPACE

byte Atomic::mContext; // No initialiser, starts at zero

AVR_BEGIN_UNNAMED_NAMESPACE

void checkAtomicValidity()
{
    // Check that mContext starts with Main value.
    AVR_STATIC_ASSERT(Atomic::Main == 0);
}

AVR_END_UNNAMED_NAMESPACE

END_AK47_NAMESPACE
