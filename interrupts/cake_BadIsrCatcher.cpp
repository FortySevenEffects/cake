#include "cake.h"
#include <avr/interrupt.h>

BEGIN_CAKE_NAMESPACE

END_CAKE_NAMESPACE

// -----------------------------------------------------------------------------

ISR(BADISR_vect)
{
    // You have enabled an interrupt, but did not implement an ISR for it.
    // Zombie interrupts come here to die.
    AVR_ASSERT_FALSE();
}
