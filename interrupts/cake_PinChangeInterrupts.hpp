#pragma once

BEGIN_CAKE_NAMESPACE

template<class Port>
constexpr inline RegisterAddress8 PinChangeTraits<Port>::getGeneralInterruptRegister()
{
#if defined(GIMSK)
    return RegisterAddress8(&GIMSK);
#elif defined(PCICR)
    return RegisterAddress8(&PCICR);
#endif
}

// -----------------------------------------------------------------------------

#define AVR_PIN_CHANGE_TRAITS_IMPL(PortName, Id)                                        \
template<>                                                                              \
inline RegisterAddress8 PinChangeTraits<PortName>::getPinChangeMaskRegister()           \
{                                                                                       \
    return reinterpret_cast<RegisterAddress8>(&PCMSK##Id);                              \
}                                                                                       \
template<>                                                                              \
inline byte PinChangeTraits<PortName>::getPinChangeEnableMask()                         \
{                                                                                       \
    return 1 << (PCIE0 + Id);                                                           \
}

#if defined(__AVR_ATmega644P__)
    AVR_PIN_CHANGE_TRAITS_IMPL(PortA, 0);
    AVR_PIN_CHANGE_TRAITS_IMPL(PortB, 1);
    AVR_PIN_CHANGE_TRAITS_IMPL(PortC, 2);
    AVR_PIN_CHANGE_TRAITS_IMPL(PortD, 3);
#elif defined(__AVR_ATmega328P__)
    AVR_PIN_CHANGE_TRAITS_IMPL(PortB, 0);
    AVR_PIN_CHANGE_TRAITS_IMPL(PortC, 1);
    AVR_PIN_CHANGE_TRAITS_IMPL(PortD, 2);
#elif defined(__AVR_ATmega32U4__)
    AVR_PIN_CHANGE_TRAITS_IMPL(PortB, 0);
#elif defined(__AVR_ATtiny84__)
    AVR_PIN_CHANGE_TRAITS_IMPL(PortA, 0);
    AVR_PIN_CHANGE_TRAITS_IMPL(PortB, 1);
#else
#   error Implement abstraction for this chip.
#endif

#undef AVR_PIN_CHANGE_TRAITS_IMPL

// ########################################################################## //

template<class Pin>
inline PinChangeInterrupt<Pin>::PinChangeInterrupt()
{
}

template<class Pin>
inline PinChangeInterrupt<Pin>::~PinChangeInterrupt()
{
}

// -----------------------------------------------------------------------------

template<class Pin>
inline void PinChangeInterrupt<Pin>::init(bool inPullUp)
{
    static const byte mask = Traits::getPinChangeEnableMask();
    *(Traits::getGeneralInterruptRegister()) |= mask;
}

template<class Pin>
inline void PinChangeInterrupt<Pin>::enable()
{
    *(Traits::getPinChangeMaskRegister()) |= (1 << Pin::Bit);
}

template<class Pin>
inline void PinChangeInterrupt<Pin>::disable()
{
    *(Traits::getPinChangeMaskRegister()) &= ~(1 << Pin::Bit);
}

END_CAKE_NAMESPACE
