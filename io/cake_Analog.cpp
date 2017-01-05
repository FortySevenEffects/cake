#include "io/cake_Analog.h"

BEGIN_CAKE_NAMESPACE

void Adc::checkRegisterStructure()
{
    // ADMUX register structure
    AVR_STATIC_ASSERT(REFS1 == 7);
    AVR_STATIC_ASSERT(REFS0 == 6);

    // ADCSRA register structure
    AVR_STATIC_ASSERT(ADEN  == 7);
    AVR_STATIC_ASSERT(ADSC  == 6);
    AVR_STATIC_ASSERT(ADATE == 5);
    AVR_STATIC_ASSERT(ADIF  == 4);
    AVR_STATIC_ASSERT(ADIE  == 3);
    AVR_STATIC_ASSERT(ADPS2 == 2);
    AVR_STATIC_ASSERT(ADPS1 == 1);
    AVR_STATIC_ASSERT(ADPS0 == 0);
}

END_CAKE_NAMESPACE
