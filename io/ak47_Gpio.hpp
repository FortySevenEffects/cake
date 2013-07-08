/*!
 *  \file       ak47_Gpio.hpp
 *  \author     Francois Best
 *  \date       27/10/2012
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

template<class Traits>
Port<Traits>::Port()
{
}

template<class Traits>
Port<Traits>::~Port()
{
}

// -----------------------------------------------------------------------------

template<class Traits>
template<byte Pin>
inline void Port<Traits>::setInput(bool inWithPullUp)
{
    *(Traits::getDirectionRegister()) &= ~(1 << Pin);
    // \todo Handle pull-up
}

template<class Traits>
template<byte Pin>
inline void Port<Traits>::setOutput()
{
    *(Traits::getDirectionRegister()) |= (1 << Pin);
}

// -----------------------------------------------------------------------------

template<class Traits>
template<byte Pin>
inline void Port<Traits>::set()
{
    *(Traits::getOutputRegister()) |= (1 << Pin);
}

template<class Traits>
template<byte Pin>
inline void Port<Traits>::clear()
{
    *(Traits::getOutputRegister()) &= ~(1 << Pin);
}

template<class Traits>
template<byte Pin>
inline void Port<Traits>::toggle()
{
    *(Traits::getInputRegister()) |= (1 << Pin);
}

// -----------------------------------------------------------------------------

template<class Traits>
inline byte Port<Traits>::read()
{
    return *(Traits::getInputRegister());
}

template<class Traits>
inline void Port<Traits>::write(byte inValue)
{
    *(Traits::getOutputRegister()) = inValue;
}

// ########################################################################## //
// Traits specialisations

#define AVR_PORT_TRAITS_IMPL(Id)                                                \
struct PortTraits##Id                                                           \
{                                                                               \
    typedef volatile uint8* RegisterAddress;                                    \
                                                                                \
    static inline RegisterAddress getDirectionRegister()                        \
    {                                                                           \
        return RegisterAddress(&DDR##Id);                                       \
    }                                                                           \
                                                                                \
    static inline RegisterAddress getOutputRegister()                           \
    {                                                                           \
        return RegisterAddress(&PORT##Id);                                      \
    }                                                                           \
                                                                                \
    static inline RegisterAddress getInputRegister()                            \
    {                                                                           \
        return RegisterAddress(&PIN##Id);                                       \
    }                                                                           \
};                                                                              \
typedef Port<PortTraits##Id> Port##Id;


#if defined(PORTA)
AVR_PORT_TRAITS_IMPL(A)
#endif

#if defined(PORTB)
AVR_PORT_TRAITS_IMPL(B)
#endif

#if defined(PORTC)
AVR_PORT_TRAITS_IMPL(C)
#endif

#if defined(PORTD)
AVR_PORT_TRAITS_IMPL(D)
#endif

#if defined(PORTE)
AVR_PORT_TRAITS_IMPL(E)
#endif

#if defined(PORTF)
AVR_PORT_TRAITS_IMPL(F)
#endif

#if defined(PORTG)
AVR_PORT_TRAITS_IMPL(G)
#endif

#if defined(PORTH)
AVR_PORT_TRAITS_IMPL(H)
#endif

#if defined(PORTI)
AVR_PORT_TRAITS_IMPL(I)
#endif

#undef AVR_PORT_TRAITS_IMPL

// ########################################################################## //

template<class Port, byte Bit>
inline Pin<Port, Bit>::Pin()
{
}

template<class Port, byte Bit>
inline Pin<Port, Bit>::~Pin()
{
}

// -----------------------------------------------------------------------------

template<class Port, byte Bit>
inline void Pin<Port, Bit>::setInput(bool inWithPullUp)
{
    Port::template setInput<Bit>(inWithPullUp);
    // \todo Handle pull-up
}

template<class Port, byte Bit>
inline void Pin<Port, Bit>::setOutput()
{
    Port::template setOutput<Bit>();
}

// -----------------------------------------------------------------------------

template<class Port, byte Bit>
inline void Pin<Port, Bit>::set()
{
    Port::template set<Bit>();
}

template<class Port, byte Bit>
inline void Pin<Port, Bit>::clear()
{
    Port::template clear<Bit>();
}

template<class Port, byte Bit>
inline void Pin<Port, Bit>::toggle()
{
    Port::template toggle<Bit>();
}

template<class Port, byte Bit>
inline bool Pin<Port, Bit>::read()
{
    return Port::read() & (1 << Bit);
}

// ########################################################################## //

template<class Port, byte Mask>
inline PinGroup<Port, Mask>::PinGroup()
{
}

template<class Port, byte Mask>
inline PinGroup<Port, Mask>::~PinGroup()
{
}

// -----------------------------------------------------------------------------

template<class Port, byte Mask>
inline void PinGroup<Port, Mask>::setInput(bool inWithPullUp)
{
    *(Port::Traits::getDirectionRegister()) &= ~Mask;
    // \todo Handle pull-up
}

template<class Port, byte Mask>
inline void PinGroup<Port, Mask>::setOutput()
{
    *(Port::Traits::getDirectionRegister()) |= Mask;
}

// -----------------------------------------------------------------------------

template<class Port, byte Mask>
inline void PinGroup<Port, Mask>::set(byte inValue)
{
    const byte base = *(Port::Traits::getOutputRegister()) & ~Mask;
    *(Port::Traits::getOutputRegister()) = base | ((inValue << getShift()) & Mask);
}

template<class Port, byte Mask>
inline void PinGroup<Port, Mask>::clear()
{
    *(Port::Traits::getOutputRegister()) &= ~Mask;
}

template<class Port, byte Mask>
inline byte PinGroup<Port, Mask>::read()
{
    return (*(Port::Traits::getInputRegister()) & Mask) >> getShift();
}

// -----------------------------------------------------------------------------

template<class Port, byte Mask>
inline byte PinGroup<Port, Mask>::getShift()
{
    AVR_STATIC_ASSERT(Mask >= 0x01);
    AVR_STATIC_ASSERT(Mask <= 0xff);

    for (byte i = 0; i < 8; ++i)
    {
        if (Mask & (1 << i))
            return i;
    }
    return 7;
}

END_AK47_NAMESPACE
