/*!
 *  \file       ak47_ExternalInterrupt.hpp
 *  \author     Francois Best
 *  \date       16/10/2013
 *  \license    GPL v3.0 - Copyright Forty Seven Effects 2013
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

BEGIN_AK47_NAMESPACE

template<class Traits>
inline ExternalInterrupt<Traits>::ExternalInterrupt()
{
}

template<class Traits>
inline ExternalInterrupt<Traits>::~ExternalInterrupt()
{
}

// -----------------------------------------------------------------------------

template<class Traits>
inline void ExternalInterrupt<Traits>::enable()
{
    *(Traits::getEnableRegister()) |= (1 << Traits::sEnableIndex);
}

template<class Traits>
inline void ExternalInterrupt<Traits>::disable()
{
    *(Traits::getEnableRegister()) &= ~(1 << Traits::sEnableIndex);
}

// -----------------------------------------------------------------------------

template<class Traits>
inline void ExternalInterrupt<Traits>::setTriggerOn(TriggerMode inMode)
{
    const byte modeReg = *(Traits::getModeRegister()) & ~(Traits::sModeMask);
    *(Traits::getModeRegister()) = modeReg | (inMode << Traits::sModeShift);
}

// ########################################################################## //
// Traits specialisations

#if defined(GIMSK) // ATtiny family
#define AVR_EXT_INT_MODE_REG        MCUCR
#define AVR_EXT_INT_ENABLE_REG      GIMSK
#elif defined(EICRA) // ATmega family
#define AVR_EXT_INT_MODE_REG        EICRA
#define AVR_EXT_INT_ENABLE_REG      EIMSK
#endif

#define AVR_TRAITS_IMPL(Id)                                                     \
struct ExtInterruptTraits##Id                                                   \
{                                                                               \
    typedef volatile uint8* RegisterAddress;                                    \
                                                                                \
    static inline RegisterAddress getModeRegister()                             \
    {                                                                           \
        return RegisterAddress(&AVR_EXT_INT_MODE_REG);                          \
    }                                                                           \
    static inline RegisterAddress getEnableRegister()                           \
    {                                                                           \
        return RegisterAddress(&AVR_EXT_INT_ENABLE_REG);                        \
    }                                                                           \
                                                                                \
    static const byte sModeMask     = 0x03 << Id;                               \
    static const byte sModeShift    = 2 * Id;                                   \
    static const byte sEnableIndex  = INT0 + Id;                                \
};                                                                              \
typedef ExternalInterrupt<ExtInterruptTraits##Id> ExternalInterrupt##Id;

#ifdef INT0
AVR_TRAITS_IMPL(0)
#endif

#ifdef INT1
AVR_TRAITS_IMPL(1)
#endif

#ifdef INT2
AVR_TRAITS_IMPL(2)
#endif

#ifdef INT3
AVR_TRAITS_IMPL(3)
#endif

#ifdef INT4
AVR_TRAITS_IMPL(4)
#endif

#ifdef INT5
AVR_TRAITS_IMPL(5)
#endif

#ifdef INT6
AVR_TRAITS_IMPL(6)
#endif

#undef AVR_EXT_INT_MODE_REG
#undef AVR_EXT_INT_ENABLE_REG
#undef AVR_TRAITS_IMPL

END_AK47_NAMESPACE
