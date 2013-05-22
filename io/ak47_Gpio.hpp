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
Gpio<Traits>::Gpio()
{
}

template<class Traits>
Gpio<Traits>::~Gpio()
{
}

// -----------------------------------------------------------------------------

template<class Traits>
template<byte Pin>
inline void Gpio<Traits>::setInput(bool inWithPullUp)
{
    *(Traits::getDdr()) &= ~(1 << Pin);
}

template<class Traits>
template<byte Pin>
inline void Gpio<Traits>::setOutput()
{
    *(Traits::getDdr()) |= (1 << Pin);
}

// -----------------------------------------------------------------------------

template<class Traits>
template<byte Pin>
inline void Gpio<Traits>::set()
{
    *(Traits::getPort()) |= (1 << Pin);
}

template<class Traits>
template<byte Pin>
inline void Gpio<Traits>::clear()
{
    *(Traits::getPort()) &= ~(1 << Pin);
}

template<class Traits>
template<byte Pin>
inline void Gpio<Traits>::toggle()
{
    *(Traits::getPin()) |= (1 << Pin);
}

// -----------------------------------------------------------------------------

template<class Traits>
inline byte Gpio<Traits>::read()
{
    return *(Traits::getPin());
}

template<class Traits>
inline void Gpio<Traits>::write(byte inValue)
{
    *(Traits::getPort()) = inValue;
}

// ########################################################################## //
// Traits specialisations

#define AVR_GPIO_TRAITS_IMPL(Id)                                                \
struct GpioTraits##Id                                                           \
{                                                                               \
    static inline RegisterAddress getPort()                                     \
    {                                                                           \
        return RegisterAddress(&PORT##Id);                                      \
    }                                                                           \
                                                                                \
    static inline RegisterAddress getDdr()                                      \
    {                                                                           \
        return RegisterAddress(&DDR##Id);                                       \
    }                                                                           \
                                                                                \
    static inline RegisterAddress getPin()                                      \
    {                                                                           \
        return RegisterAddress(&PIN##Id);                                       \
    }                                                                           \
};                                                                              \
typedef Gpio<GpioTraits##Id> Gpio##Id;


#if defined(PORTA)
AVR_GPIO_TRAITS_IMPL(A)
#endif

#if defined(PORTB)
AVR_GPIO_TRAITS_IMPL(B)
#endif

#if defined(PORTC)
AVR_GPIO_TRAITS_IMPL(C)
#endif

#if defined(PORTD)
AVR_GPIO_TRAITS_IMPL(D)
#endif

#if defined(PORTE)
AVR_GPIO_TRAITS_IMPL(E)
#endif

#if defined(PORTF)
AVR_GPIO_TRAITS_IMPL(F)
#endif

#if defined(PORTG)
AVR_GPIO_TRAITS_IMPL(G)
#endif

#if defined(PORTH)
AVR_GPIO_TRAITS_IMPL(H)
#endif

#if defined(PORTI)
AVR_GPIO_TRAITS_IMPL(I)
#endif

#undef AVR_GPIO_TRAITS_IMPL

END_AK47_NAMESPACE
