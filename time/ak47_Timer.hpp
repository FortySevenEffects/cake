/*!
 *  \file       ak47_Timer.hpp
 *  \author     Francois Best
 *  \date       02/12/2012
 *  \license    GPL v3.0 - Copyright Forty Seven Effects 2012
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

template<byte TimerId, byte Bits>
inline Timer<TimerId, Bits>::Timer()
{
}

template<byte TimerId, byte Bits>
inline Timer<TimerId, Bits>::~Timer()
{
}

// -----------------------------------------------------------------------------

template<byte TimerId, byte Bits>
inline void Timer<TimerId, Bits>::enableInterruptA()
{
    *(Traits::getTIMSK()) |= Traits::getInterruptMaskA();
}

template<byte TimerId, byte Bits>
inline void Timer<TimerId, Bits>::enableInterruptB()
{
    *(Traits::getTIMSK()) |= Traits::getInterruptMaskB();
}

template<byte TimerId, byte Bits>
inline void Timer<TimerId, Bits>::enableInterruptOverflow()
{
    *(Traits::getTIMSK()) |= Traits::getInterruptMaskOverflow();
}

template<byte TimerId, byte Bits>
inline void Timer<TimerId, Bits>::disableInterruptA()
{
    *(Traits::getTIMSK()) &= ~(Traits::getInterruptMaskA());
}

template<byte TimerId, byte Bits>
inline void Timer<TimerId, Bits>::disableInterruptB()
{
    *(Traits::getTIMSK()) &= ~(Traits::getInterruptMaskB());
}

template<byte TimerId, byte Bits>
inline void Timer<TimerId, Bits>::disableInterruptOverflow()
{
    *(Traits::getTIMSK()) &= ~(Traits::getInterruptMaskOverflow());
}

// -----------------------------------------------------------------------------

template <byte TimerId, byte Bits>
inline void Timer<TimerId, Bits>::setCompareOutputModeA(CompareOutputMode inMode)
{
    static const byte mask  = 0xC0;
    static const byte shift = 6;

    const uint8 tccra = *(Traits::getTCCRA()) & ~(mask);
    *(Traits::getTCCRA()) = tccra | ((inMode << shift) & mask);
}

template <byte TimerId, byte Bits>
inline void Timer<TimerId, Bits>::setCompareOutputModeB(CompareOutputMode inMode)
{
    static const byte mask  = 0x30;
    static const byte shift = 4;

    const uint8 tccra = *(Traits::getTCCRA()) & ~(mask);
    *(Traits::getTCCRA()) = tccra | ((inMode << shift) & mask);
}

template <byte TimerId, byte Bits>
inline void Timer<TimerId, Bits>::setMode(Mode inMode)
{
    static const byte maskMsb  = 0x18;
    static const byte maskLsb  = 0x03;
    static const byte shiftMsb = 3;
    static const byte shiftLsb = 0;

    const byte msb = (inMode >> 2) & 0x03;
    const byte lsb = inMode & 0x03;

    const uint8 tccra = *(Traits::getTCCRA()) & ~(maskLsb);
    *(Traits::getTCCRA()) = tccra | ((inMode << shiftLsb) & maskLsb);

    const uint8 tccrb = *(Traits::getTCCRB()) & ~(maskMsb);
    *(Traits::getTCCRB()) = tccrb | ((inMode << shiftMsb) & maskMsb);
}

// -----------------------------------------------------------------------------

template<byte TimerId, byte Bits>
inline void Timer<TimerId, Bits>::start(Prescale inPrescale)
{
    setPrescale(inPrescale);
}

template<byte TimerId, byte Bits>
inline void Timer<TimerId, Bits>::stop()
{
    *(Traits::getTCCRB()) &= ~(0x07);
}

template<byte TimerId, byte Bits>
inline void Timer<TimerId, Bits>::reset()
{
    *(Traits::getTCNT()) = 0;
}

// -----------------------------------------------------------------------------

template<byte TimerId, byte Bits>
inline typename Timer<TimerId, Bits>::Value Timer<TimerId, Bits>::getValue()
{
    return *(Traits::getTCNT());
}

template<byte TimerId, byte Bits>
inline void Timer<TimerId, Bits>::setValue(Value inValue)
{
    *(Traits::getTCNT()) = inValue;
}

template<byte TimerId, byte Bits>
inline void Timer<TimerId, Bits>::setA(Value inValue)
{
    *(Traits::getOCRA()) = inValue;
}

template<byte TimerId, byte Bits>
inline void Timer<TimerId, Bits>::setB(Value inValue)
{
    *(Traits::getOCRB()) = inValue;
}

// -----------------------------------------------------------------------------

template<byte TimerId, byte Bits>
inline void Timer<TimerId, Bits>::setPrescale(Prescale inPrescale)
{
    static const uint8 mask = 0x07;
    const uint8 tccrb = *(Traits::getTCCRB()) & ~(0x07);    // Mask away the old value
    *(Traits::getTCCRB()) = tccrb | (inPrescale & mask);    // And set the new one
}

// ########################################################################## //
// Traits specialisations

#define AVR_TIMER_TRAITS_IMPL(Id, Bit)                                          \
template<>                                                                      \
inline TimerTraits<Id, Bit>::ControlRegister TimerTraits<Id, Bit>::getTCCRA()   \
{                                                                               \
    return ControlRegister(&TCCR##Id##A);                                       \
}                                                                               \
                                                                                \
template<>                                                                      \
inline TimerTraits<Id, Bit>::ControlRegister TimerTraits<Id, Bit>::getTCCRB()   \
{                                                                               \
    return ControlRegister(&TCCR##Id##B);                                       \
}                                                                               \
                                                                                \
template<>                                                                      \
inline TimerTraits<Id, Bit>::ControlRegister TimerTraits<Id, Bit>::getTIMSK()   \
{                                                                               \
    return ControlRegister(&TIMSK##Id);                                         \
}                                                                               \
                                                                                \
template<>                                                                      \
inline TimerTraits<Id, Bit>::DataRegister TimerTraits<Id, Bit>::getOCRA()       \
{                                                                               \
    return DataRegister(&OCR##Id##A);                                           \
}                                                                               \
                                                                                \
template<>                                                                      \
inline TimerTraits<Id, Bit>::DataRegister TimerTraits<Id, Bit>::getOCRB()       \
{                                                                               \
    return DataRegister(&OCR##Id##B);                                           \
}                                                                               \
                                                                                \
template<>                                                                      \
inline TimerTraits<Id, Bit>::DataRegister TimerTraits<Id, Bit>::getTCNT()       \
{                                                                               \
    return DataRegister(&TCNT##Id);                                             \
}                                                                               \
                                                                                \
template<>                                                                      \
inline byte TimerTraits<Id, Bit>::getInterruptMaskA()                           \
{                                                                               \
    return (1 << OCIE##Id##A);                                                  \
}                                                                               \
                                                                                \
template<>                                                                      \
inline byte TimerTraits<Id, Bit>::getInterruptMaskB()                           \
{                                                                               \
    return (1 << OCIE##Id##B);                                                  \
}                                                                               \
                                                                                \
template<>                                                                      \
inline byte TimerTraits<Id, Bit>::getInterruptMaskOverflow()                    \
{                                                                               \
    return (1 << TOIE##Id);                                                     \
}                                                                               \
                                                                                \
template<>                                                                      \
inline void TimerTraits<Id, Bit>::checkRegistersStructure()                     \
{                                                                               \
    /* Check TCCRnA structure */                                                \
    AVR_STATIC_ASSERT(COM##Id##A1   == 7);                                      \
    AVR_STATIC_ASSERT(COM##Id##A0   == 6);                                      \
    AVR_STATIC_ASSERT(COM##Id##B1   == 5);                                      \
    AVR_STATIC_ASSERT(COM##Id##B0   == 4);                                      \
    AVR_STATIC_ASSERT(WGM##Id##1    == 1);                                      \
    AVR_STATIC_ASSERT(WGM##Id##0    == 0);                                      \
                                                                                \
    /* Check TCCRnB structure */                                                \
    AVR_STATIC_ASSERT(WGM##Id##3    == 4);                                      \
    AVR_STATIC_ASSERT(WGM##Id##2    == 3);                                      \
    AVR_STATIC_ASSERT(CS##Id##2     == 2);                                      \
    AVR_STATIC_ASSERT(CS##Id##1     == 1);                                      \
    AVR_STATIC_ASSERT(CS##Id##0     == 0);                                      \
}

#ifdef TCNT0
typedef Timer<0, 8 * sizeof(TCNT0)> Timer0;
AVR_TIMER_TRAITS_IMPL(0, 8 * sizeof(TCNT0))
#endif

#ifdef TCNT1
typedef Timer<1, 8 * sizeof(TCNT1)> Timer1;
AVR_TIMER_TRAITS_IMPL(1, 8 * sizeof(TCNT1))
#endif

#ifdef TCNT2
typedef Timer<2, 8 * sizeof(TCNT2)> Timer2;
AVR_TIMER_TRAITS_IMPL(2, 8 * sizeof(TCNT2))
#endif

#ifdef TCNT3
typedef Timer<3, 8 * sizeof(TCNT3)> Timer3;
AVR_TIMER_TRAITS_IMPL(3, 8 * sizeof(TCNT3))
#endif

#undef AVR_TIMER_TRAITS_IMPL

END_AK47_NAMESPACE
