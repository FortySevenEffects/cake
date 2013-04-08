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

inline void Spi::setMode(byte inSpiMode)
{
    // Mode CPOL CPHA
    // 0    0    0
    // 1    0    1
    // 2    1    0
    // 3    1    1
    
    if (inSpiMode & 0x01) // Mask for CPHA
    {
        SPCR |= (1 << CPHA);
    }
    else
    {
        SPCR &= ~(1 << CPHA);
    }
    
    if (inSpiMode & 0x02) // Mask for CPOL
    {
        SPCR |= (1 << CPOL);
    }
    else
    {
        SPCR &= ~(1 << CPOL);
    }
}

inline void Spi::setSpeed(SpiSpeed inSpeed)
{
    // Clear old config and replace with new.
    SPCR = (SPCR & ~(0x03)) | (inSpeed & 0x03);
    
    // 2X factor
    if (inSpeed & 0x04)
    {
        SPSR |= (1 << SPI2X);
    }
    else
    {
        SPSR &= ~(1 << SPI2X);
    }
}

inline void Spi::setDataOrder(bool inLsbFirst)
{
    if (inLsbFirst)
    {
        SPCR |= (1 << DORD);
    }
    else
    {
        SPCR &= ~(1 << DORD);
    }
}

// -----------------------------------------------------------------------------

inline void Spi::openMaster(Parser inParser)
{
    mParser = inParser;
    SPCR |= (1 << SPE) | (1 << MSTR);
    // \todo Configure SS pin as output
}

inline void Spi::openSlave(Parser inParser)
{
    mParser = inParser;
    SPCR &= ~(1 << MSTR);
    SPCR |=  (1 << SPE);
}

inline void Spi::close()
{
    SPCR &= ~((1 << SPE) | (1 << SPIE));
    clearRxBuffer();
    clearTxBuffer();
}

// -----------------------------------------------------------------------------

inline void Spi::write(byte inData)
{
    if (mTxBuffer.empty())
    {
        // Avoid buffer overhead, send directly.
        SPCR |= (1 << SPIE);    // Enable interrupt
        SPDR = inData;          // Start transaction
    }
    else
    {
        mTxBuffer.push(inData);
    }
}

inline void Spi::write(const byte* inData, byte inLength)
{
    if (mTxBuffer.empty())
    {
        write(inData[0]);
        for (byte i = 1; i < inLength; ++i)
        {
            mTxBuffer.push(inData[i]);
        }
    }
    else
    {
        for (byte i = 0; i < inLength; ++i)
        {
            mTxBuffer.push(inData[i]);
        }
    }
}

// -----------------------------------------------------------------------------

inline void Spi::busyWrite(byte inData)
{
    SPDR = inData;
    while (bit_is_clear(SPSR, SPIF));
    handleByteReceived(SPDR);
}

inline void Spi::busyWrite(const byte* inData, byte inLenght)
{
    for (byte i = 0; i < inLenght; ++i)
    {
        busyWrite(inData[i]);
    }
}

// -----------------------------------------------------------------------------

inline void Spi::writeSlave(byte inData)
{
    // Write only the response for next transaction
    mTxBuffer.push(inData);
}

inline void Spi::writeSlave(const byte* inData, byte inLenght)
{
    for (byte i = 0; i < inLenght; ++i)
    {
        writeSlave(inData[i]);
    }
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

inline void Spi::handleInterrupt()
{
    handleByteReceived(SPDR);
    if (mTxBuffer.empty())
    {
        // End of transmission: disable interrupt
        SPCR &= ~(1 << SPIE);
    }
    else
    {
        // Continue transmission
        SPDR = mTxBuffer.pop();
    }
}

inline void Spi::handleByteReceived(byte inData)
{
    // \todo Check logic with real user cases
    if (mParser != 0)
    {
        mParser(inData);
    }
    else
    {
        mRxBuffer.push(inData);
    }
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
