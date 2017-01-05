#include "cake_Types.h"

BEGIN_CAKE_NAMESPACE

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

END_CAKE_NAMESPACE
