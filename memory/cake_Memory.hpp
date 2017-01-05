#pragma once

BEGIN_CAKE_NAMESPACE

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

END_CAKE_NAMESPACE

// -----------------------------------------------------------------------------

#if CAKE_DYNAMIC_MEMORY && defined(__cplusplus)

inline void* operator new(size_t size)
{
    return malloc(size);
}

inline void* operator new(size_t size_,void *ptr_)
{
    return ptr_;
}

inline void* operator new[](size_t size)
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

void operator delete[](void* ptr)
{
    if (ptr != 0)
    {
        free(ptr);
    }
}

#endif
