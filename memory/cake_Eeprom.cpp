#include "memory/cake_Eeprom.h"
#include <avr/interrupt.h>

BEGIN_CAKE_NAMESPACE

Eeprom::EepromReadyCallback Eeprom::sClientCallback = 0;

END_CAKE_NAMESPACE

// -----------------------------------------------------------------------------

#if   defined (EE_READY_vect)
#   define EEPROM_ISR EE_READY_vect
#elif defined (EEPROM_READY_vect)
#   define EEPROM_ISR EEPROM_READY_vect
#elif defined (EE_RDY_vect)
#   define EEPROM_ISR EE_RDY_vect
#endif

ISR(EEPROM_ISR)
{
    if (cake::Eeprom::sClientCallback != 0)
    {
        cake::Eeprom::sClientCallback();
    }
}
