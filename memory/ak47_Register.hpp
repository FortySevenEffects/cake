/*!
 *  \file       ak47_Register.hpp
 *  \author     Francois Best
 *  \date       16/11/2012
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
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

BEGIN_AK47_NAMESPACE

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

END_AK47_NAMESPACE
