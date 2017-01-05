#include "io/cake_I2C.h"

#ifdef TWI_vect

BEGIN_CAKE_NAMESPACE

byte I2C::sExpected = 0;

// -----------------------------------------------------------------------------

ISR(TWI_vect)
{
    I2C::interruptCallback();
}

END_CAKE_NAMESPACE

#endif
