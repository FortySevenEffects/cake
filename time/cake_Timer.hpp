/*!
 *  \file       cake_Timer.hpp
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

BEGIN_CAKE_NAMESPACE

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
    static const byte flag = 1; // See Traits::checkRegistersStructure
    static const byte mask = (1 << flag);
    *(Traits::getTIMSK()) |= mask;
}

template<byte TimerId, byte Bits>
inline void Timer<TimerId, Bits>::enableInterruptB()
{
    static const byte flag = 2; // See Traits::checkRegistersStructure
    static const byte mask = (1 << flag);
    *(Traits::getTIMSK()) |= mask;
}

template<byte TimerId, byte Bits>
inline void Timer<TimerId, Bits>::enableInterruptOverflow()
{
    static const byte flag = 0; // See Traits::checkRegistersStructure
    static const byte mask = (1 << flag);
    *(Traits::getTIMSK()) |= mask;
}

template<byte TimerId, byte Bits>
inline void Timer<TimerId, Bits>::disableInterruptA()
{
    static const byte flag = 1; // See Traits::checkRegistersStructure
    static const byte mask = (1 << flag);
    *(Traits::getTIMSK()) &= ~(mask);
}

template<byte TimerId, byte Bits>
inline void Timer<TimerId, Bits>::disableInterruptB()
{
    static const byte flag = 2; // See Traits::checkRegistersStructure
    static const byte mask = (1 << flag);
    *(Traits::getTIMSK()) &= ~(mask);
}

template<byte TimerId, byte Bits>
inline void Timer<TimerId, Bits>::disableInterruptOverflow()
{
    static const byte flag = 0; // See Traits::checkRegistersStructure
    static const byte mask = (1 << flag);
    *(Traits::getTIMSK()) &= ~(mask);
}

// -----------------------------------------------------------------------------

template<byte TimerId, byte Bits>
inline void Timer<TimerId, Bits>::setCompareOutputModeA(CompareOutputMode inMode)
{
    static const byte mask  = 0xC0;
    static const byte shift = 6;

    const byte tccra = *(Traits::getTCCRA()) & ~(mask);
    *(Traits::getTCCRA()) = tccra | ((inMode << shift) & mask);
}

template<byte TimerId, byte Bits>
inline void Timer<TimerId, Bits>::setCompareOutputModeB(CompareOutputMode inMode)
{
    static const byte mask  = 0x30;
    static const byte shift = 4;

    const byte tccra = *(Traits::getTCCRA()) & ~(mask);
    *(Traits::getTCCRA()) = tccra | ((inMode << shift) & mask);
}

template<byte TimerId, byte Bits>
template<byte Mode>
inline void Timer<TimerId, Bits>::setMode()
{
    AVR_STATIC_ASSERT(Traits::hasWGM3 == true  && (Mode & ~0x0F) == 0 ||
                      Traits::hasWGM3 == false && (Mode & ~0x07) == 0);

    static const byte maskMsb  = (Traits::hasWGM3 ? 0x18 : 0x08);
    static const byte maskLsb  = 0x03;
    static const byte shiftMsb = 3;
    static const byte shiftLsb = 0;

    const byte msb = (Mode >> 2);
    const byte lsb = Mode & 0x03;

    const byte tccra = *(Traits::getTCCRA()) & ~(maskLsb);
    *(Traits::getTCCRA()) = tccra | (lsb << shiftLsb);

    const byte tccrb = *(Traits::getTCCRB()) & ~(maskMsb);
    *(Traits::getTCCRB()) = tccrb | (msb << shiftMsb);
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
    static const byte mask = 0x07;
    const byte tccrb = *(Traits::getTCCRB()) & ~mask;    // Mask away the old value
    *(Traits::getTCCRB()) = tccrb | (inPrescale & mask); // And set the new one
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
    AVR_STATIC_ASSERT(WGM##Id##2    == 3);                                      \
    AVR_STATIC_ASSERT(CS##Id##2     == 2);                                      \
    AVR_STATIC_ASSERT(CS##Id##1     == 1);                                      \
    AVR_STATIC_ASSERT(CS##Id##0     == 0);                                      \
                                                                                \
    /* Check TIMSKn structure */                                                \
    AVR_STATIC_ASSERT(OCIE##Id##B   == 2);                                      \
    AVR_STATIC_ASSERT(OCIE##Id##A   == 1);                                      \
    AVR_STATIC_ASSERT(TOIE##Id      == 0);                                      \
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

#ifdef TCNT4
typedef Timer<4, 8 * sizeof(TCNT4)> Timer4;
AVR_TIMER_TRAITS_IMPL(4, 8 * sizeof(TCNT4))
#endif

#ifdef TCNT5
typedef Timer<5, 8 * sizeof(TCNT5)> Timer5;
AVR_TIMER_TRAITS_IMPL(5, 8 * sizeof(TCNT5))
#endif

#undef AVR_TIMER_TRAITS_IMPL

END_CAKE_NAMESPACE
