#pragma once

BEGIN_CAKE_NAMESPACE

inline void Adc::enable()
{
    ADCSRA |= (1 << ADEN);
}

inline void Adc::disable()
{
    ADCSRA &= ~(1 << ADEN);
}

// -----------------------------------------------------------------------------

inline void Adc::setReference(AnalogReference inReference)
{
    static const byte mask  = 0xc0;
    static const byte shift = 6;

    const byte admux = ADMUX & ~mask;
    ADMUX = admux | ((inReference << shift) & mask);
}

inline void Adc::setPrescaler(Prescaler inPrescaler)
{
    static const byte mask  = 0x07;

    const byte adcsra = ADCSRA & ~mask;
    ADCSRA = adcsra | (inPrescaler & mask);
}

// -----------------------------------------------------------------------------

inline Adc::Sample Adc::read(ChannelId inChannel)
{

#if defined(MUX7)
    static const byte mask = 0xff;
#elif defined(MUX6)
    static const byte mask = 0x7f;
#elif defined(MUX5)
    static const byte mask = 0x3f;
#elif defined(MUX4)
    static const byte mask = 0x1f;
#elif defined(MUX3)
    static const byte mask = 0x0f;
#elif defined(MUX2)
    static const byte mask = 0x07;
#else
    static const byte mask = 0x03;
#endif

    const byte admux = ADMUX & ~mask;
    ADMUX = admux | (inChannel & mask);

    ADCSRA |= (1 << ADSC); // Start conversion

    while (bit_is_set(ADCSRA, ADSC))
    {
        // Wait until it's finished
    }

    // Read data (LSB must be read first).
    const uint16 lsb = ADCL;
    const uint16 msb = ADCH;

    return (msb << 8) | lsb;
}

// ########################################################################## //

template<byte NumBits>
inline AdcOversamplingFilter<NumBits>::AdcOversamplingFilter()
{
    // Make sure size is a power of two.
    AVR_STATIC_ASSERT(sBufferSize >= 1);
    AVR_STATIC_ASSERT(!(sBufferSize & (sBufferSize - 1)));
}

template<byte NumBits>
inline AdcOversamplingFilter<NumBits>::~AdcOversamplingFilter()
{
}

// -----------------------------------------------------------------------------

template<byte NumBits>
inline Adc::Sample AdcOversamplingFilter<NumBits>::process(Adc::Sample inSample)
{
    mBuffer[mWriteIndex++] = inSample;
    mWriteIndex &= (sBufferSize - 1);

    uint16 sum = 0;
    for (byte i = 0; i < sBufferSize; ++i)
    {
        sum += mBuffer[i];
    }
    return sum >> sShift;
}

// ########################################################################## //

template<byte Bit>
inline void AnalogPin<Bit>::init()
{
    // Disable digital interface to save power.
    DIDR0 |= (1 << Bit);
}

template<byte Bit>
inline Adc::Sample AnalogPin<Bit>::read()
{
    return Adc::read(Bit);
}

END_CAKE_NAMESPACE
