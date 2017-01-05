#pragma once

#include "cake.h"
#include "memory/cake_Register.h"

BEGIN_CAKE_NAMESPACE

#if defined TWI_vect
#   if  !defined(TWCR) ||   \
        !defined(TWSR) ||   \
        !defined(TWDR) ||   \
        !defined(TWAR) ||   \
        !defined(TWBR) ||   \
        !defined(TWAMR)
#       error I2C registers not found for this target chip.
#   endif
    AVR_REGISTER(TWCR, I2cControlRegister);
#else
#   define NO_I2C
#endif

END_CAKE_NAMESPACE
