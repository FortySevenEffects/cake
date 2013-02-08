/*!
 *  \file       ak47_Spi.hpp
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

inline void Spi::openMaster(Parser* inParser)
{
    mParser = inParser;
    // \todo Implement me.
}

inline void Spi::openSlave(Parser* inParser)
{
    mParser = inParser;
    // \todo Implement me.
}

inline void Spi::close()
{
    // \todo Implement me.
}

// -----------------------------------------------------------------------------

inline void Spi::write(byte inData)
{
    // \todo Implement me.
}

inline void Spi::write(const byte* inData, byte inLength)
{
    // \todo Implement me.
}

// -----------------------------------------------------------------------------

inline void Spi::busyWrite(byte inData)
{
    // \todo Implement me.
}

inline void Spi::busyWrite(const byte* inData, byte inLenght)
{
    // \todo Implement me.
}

// -----------------------------------------------------------------------------

inline bool Spi::available() const
{
    return !mRxBuffer.empty();
}

inline byte Spi::read()
{
    if (!mRxBuffer.empty())
        return mRxBuffer.pop();
    return 0xFF;
}

// -----------------------------------------------------------------------------

inline void Spi::handleByteReceived(byte inData)
{
    mRxBuffer.push(inData);
}

inline void Spi::handleEndOfTransmission()
{
    // \todo Implement me.
}

// -----------------------------------------------------------------------------

inline void Spi::clearRxBuffer()
{
    mRxBuffer.clear();
}

inline void Spi::clearTxBuffer()
{
    mTxBuffer.clear();
}

END_AK47_NAMESPACE
