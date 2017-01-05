#pragma once

BEGIN_CAKE_NAMESPACE

template <typename Reg>
inline void Register<Reg>::set(byte inBit)
{
    *Reg::ptr() |= (byte)(1 << inBit);
}

template <typename Reg>
inline void Register<Reg>::clear(byte inBit)
{
    *Reg::ptr() &= (byte)~(1 << inBit);
}

// -----------------------------------------------------------------------------

template <typename Reg>
inline Register<Reg>& Register<Reg>::operator=(const byte& inValue)
{
    *Reg::ptr() = inValue;
    return *this;
}

template <typename Reg>
inline byte Register<Reg>::operator() ()
{
    return *Reg::ptr();
}

template <typename Reg>
inline Register<Reg>::operator byte() const
{
    return *Reg::ptr();
}

END_CAKE_NAMESPACE
