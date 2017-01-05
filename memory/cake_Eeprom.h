#pragma once

#include "cake.h"
#include "cake_Types.h"
#include <avr/eeprom.h>

// -----------------------------------------------------------------------------

#define AVR_EEPROM_SECTION  __attribute__((section(".eeprom")))

#ifndef E2END
#define E2END 0
#endif

// -----------------------------------------------------------------------------

BEGIN_CAKE_NAMESPACE

class Eeprom
{
public:
    AVR_TYPEDEF_FUNCTOR(void, EepromReadyCallback, void);
    static const uint16 sEepromSize = E2END;

public:
    static inline byte read(uint16 inAddress);

    static inline void write(uint16 inAddress, byte inData);
    static inline void writeNoBlock(uint16 inAddress, byte inData);
    static inline void write(uint16 inAddress,
                             const byte* inData,
                             uint16 inSize);

    static inline void setClientCallback(EepromReadyCallback inCallback);

public: // For the ISR only, not for public use
    static EepromReadyCallback sClientCallback;
};

END_CAKE_NAMESPACE

#include "memory/cake_Eeprom.hpp"
