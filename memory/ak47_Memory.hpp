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

BEGIN_AK47_NAMESPACE

static const byte sStackPattern = 0xaa;

inline uint16 getFreeMemory()
{
    // \todo Implement me.
    return 0;
}

inline uint16 getHeapSize()
{
    extern uint16 __heap_start;
    extern void*  __brkval;
    uint8 dummy;
    return (uint16) &dummy - (__brkval == 0 ? (uint16) &__heap_start : (uint16) __brkval);
}

inline uint16 getStackSize()
{
    return RAMEND - SP;
}

// -----------------------------------------------------------------------------

inline void paintStack()
{
    // Code from MichaelMcTernan:
    // http://www.avrfreaks.net/index.php?name=PNphpBB2&file=printview&t=52249

    extern uint8_t _end;
    extern uint8_t __stack;
    
    uint8_t* stackPointer = &_end;

    while(stackPointer <= &__stack)
    {
        *stackPointer = sStackPattern;
        stackPointer++;
    }
}

inline uint16 getMaxStackUsage()
{
    // Code from MichaelMcTernan:
    // http://www.avrfreaks.net/index.php?name=PNphpBB2&file=printview&t=52249
    
    extern uint8_t _end;
    extern uint8_t __stack;

    const uint8_t *stackPointer = &_end;
    uint16 count = 0;

    while(*stackPointer == sStackPattern && stackPointer <= &__stack)
    {
        stackPointer++;
        count++;
    }
    return count; 
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
