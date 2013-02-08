/*!
 *  \file       ak47_Memory.hpp
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

#pragma once

extern uint16 __heap_start;
extern void*  __brkval;

BEGIN_AK47_NAMESPACE

uint16 getFreeMemory()
{
    return 0;
}

uint16 getHeapSize()
{
    uint8 dummy; 
    return (uint16) &dummy - (__brkval == 0 ? (uint16) &__heap_start : (uint16) __brkval);
}

uint16 getStackSize()
{
    return RAMEND - SP;
}

END_AK47_NAMESPACE

// -----------------------------------------------------------------------------

#if AK47_DYNAMIC_MEMORY && defined(__cplusplus)

AVR_BEGIN_EXTERN_C

void* operator new(size_t size)
{
    return malloc(size);
}

void operator delete(void* ptr) 
{
    if (ptr != 0)
    {
        free(ptr);
    }
}

void* operator new[](size_t size)
{
    return malloc(size);
}

void operator delete[](void* ptr)
{
    if (ptr != 0)
    {
        free(ptr);
    }
}

AVR_END_EXTERN_C

#endif // AK47_DYNAMIC_MEMORY
