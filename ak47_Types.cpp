/*!
 *  \file       ak47_Types.cpp
 *  \author     Francois Best
 *  \date       22/10/2012
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

#include "ak47_Types.h"

BEGIN_AK47_NAMESPACE

AVR_BEGIN_UNNAMED_NAMESPACE

void checkTypesBitWidths()
{
    AVR_STATIC_ASSERT(sizeof(float32) == 4);
    AVR_STATIC_ASSERT(sizeof(float64) == 4);
    
    AVR_STATIC_ASSERT(sizeof(int8)   == 1);
    AVR_STATIC_ASSERT(sizeof(uint8)  == 1);
    AVR_STATIC_ASSERT(sizeof(int16)  == 2);
    AVR_STATIC_ASSERT(sizeof(uint16) == 2);
    AVR_STATIC_ASSERT(sizeof(int32)  == 4);
    AVR_STATIC_ASSERT(sizeof(uint32) == 4);
    AVR_STATIC_ASSERT(sizeof(int64)  == 8);
    AVR_STATIC_ASSERT(sizeof(uint64) == 8);
    
    AVR_STATIC_ASSERT(sizeof(byte) == 1);
    
    AVR_STATIC_ASSERT(sizeof(int) == 2);
    AVR_STATIC_ASSERT(sizeof(unsigned) == 2);
}

AVR_END_UNNAMED_NAMESPACE

END_AK47_NAMESPACE
