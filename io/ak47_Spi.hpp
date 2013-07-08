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

template<byte TxSize>
inline SpiTransmitter<TxSize>::SpiTransmitter()
{
}

template<byte TxSize>
inline SpiTransmitter<TxSize>::~SpiTransmitter()
{
}

// -----------------------------------------------------------------------------

template<byte TxSize>
inline void SpiTransmitter<TxSize>::send(byte inData)
{
#if defined(SPCR)
    const bool isTransmitting = SPCR & (1 << SPIE);
#elif defined(USICR)
    const bool isTransmitting = USICR & (1 << USIOIE);
#endif

    if (!isTransmitting && mTxBuffer.empty())
    {
        startTransmission(inData);
    }
    else
    {
        mTxBuffer.push(inData);
    }
}

// -----------------------------------------------------------------------------

template<byte TxSize>
inline void SpiTransmitter<TxSize>::startTransmission(byte inData)
{
#if defined(SPCR)
    SPCR  |= (1 << SPIE);       // Enable End of Transmission interrupt
    SPDR = inData;              // Send data to output register
#elif defined(USICR)
    USICR |= (1 << USIOIE);     // Enable End of Transmission interrupt
    USIDR = inData;             // Send data to output register
#endif
}

template<byte TxSize>
inline void SpiTransmitter<TxSize>::handleEndOfTransmission()
{
    if (!mTxBuffer.empty())
    {
        startTransmission(mTxBuffer.pop());
    }
    else
    {
        // Disable End of Transmission interrupt
#if defined(SPCR)
        SPCR  &= ~(1 << SPIE);
#elif defined(USICR)
        USICR &= ~(1 << USIOIE);
#endif
    }
}

// ########################################################################## //

template<byte RxSize>
inline SpiReceiver<RxSize>::SpiReceiver()
{
}

template<byte RxSize>
inline SpiReceiver<RxSize>::~SpiReceiver()
{
}

// -----------------------------------------------------------------------------

template<byte RxSize>
inline bool SpiReceiver<RxSize>::read(byte& outData)
{
    if (mRxBuffer.empty())
        return false;

    outData = mRxBuffer.pop();
    return true;
}

// -----------------------------------------------------------------------------

template<byte RxSize>
inline void SpiReceiver<RxSize>::handleByteReceived()
{
#if defined(SPDR)
    mRxBuffer.push(SPDR);
#elif defined(USIBR)
    mRxBuffer.push(USIBR);
#endif
}

// ########################################################################## //

template<byte TxSize>
inline SpiMaster<TxSize>::SpiMaster()
    : SpiTransmitter<TxSize>()
{
}

template<byte TxSize>
inline SpiMaster<TxSize>::~SpiMaster()
{
}

// -----------------------------------------------------------------------------

template<byte TxSize>
inline void SpiMaster<TxSize>::open()
{
    // Enable SPI + set master
#if defined(SPCR)
    SPCR  = (1 << SPE) | (1 << MSTR);
#elif defined(USICR)
    USICR = (1 << USIWM0); // No hardware master operation on USI.
#endif

    setMode(0);
}

template<byte TxSize>
inline void SpiMaster<TxSize>::close()
{
#if defined(SPCR)
    SPCR = 0;
#elif defined(USICR)
    USICR = 0;
#endif
}

// -----------------------------------------------------------------------------

template<byte TxSize>
inline void SpiMaster<TxSize>::setMode(byte inSpiMode)
{
    // Mode CPOL CPHA
    // 0    0    0
    // 1    0    1
    // 2    1    0
    // 3    1    1

    static const byte maskCPHA = 0x01;
    static const byte maskCPOL = 0x02;

#if defined(SPCR)
    if (inSpiMode & maskCPHA)       SPCR |=  (1 << CPHA);
    else                            SPCR &= ~(1 << CPHA);

    if (inSpiMode & maskCPOL)       SPCR |=  (1 << CPOL);
    else                            SPCR &= ~(1 << CPOL);

#elif defined(USICR)
    // USI has no polarity support.
    if (inSpiMode & maskCPHA)
    {
        USICR |= (1 << USICS1) | (1 << USICS0);
    }
    else
    {
        USICR |=  (1 << USICS1);
        USICR &= ~(1 << USICS0);
    }
#endif
}

template<byte TxSize>
inline void SpiMaster<TxSize>::setSpeed(Spi::Speed inSpeed)
{
#if defined(SPCR)
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
#elif defined(USICR)
    // USI has no speed support.
#endif
}

template<byte TxSize>
inline void SpiMaster<TxSize>::setDataOrder(bool inLsbFirst)
{
#if defined(SPCR)
    if (inLsbFirst)
    {
        SPCR |= (1 << DORD);
    }
    else
    {
        SPCR &= ~(1 << DORD);
    }
#elif defined(USICR)
    // USI has no data order support.
#endif
}

// ########################################################################## //

template<byte RxSize>
inline SpiSlave<RxSize>::SpiSlave()
    : SpiReceiver<RxSize>()
{
}

template<byte RxSize>
inline SpiSlave<RxSize>::~SpiSlave()
{
}

// -----------------------------------------------------------------------------

template<byte RxSize>
inline void SpiSlave<RxSize>::open()
{
    // Enable interrupt + enable SPI.
#if defined(SPCR)
    SPCR  = (1 << SPIE) | (1 << SPE);
#elif defined(USICR)
    USICR = (1 << USIOIE) | (1 << USIWM0);
#endif
    setMode(0);
}

template<byte RxSize>
inline void SpiSlave<RxSize>::close()
{
#if defined(SPCR)
    SPCR = 0;
#elif defined(USICR)
    USICR = 0;
#endif
}

// -----------------------------------------------------------------------------

template<byte RxSize>
inline void SpiSlave<RxSize>::setMode(byte inSpiMode)
{
    // Mode CPOL CPHA
    // 0    0    0
    // 1    0    1
    // 2    1    0
    // 3    1    1

    static const byte maskCPHA = 0x01;
    static const byte maskCPOL = 0x02;

#if defined(SPCR)
    if (inSpiMode & maskCPHA)       SPCR |=  (1 << CPHA);
    else                            SPCR &= ~(1 << CPHA);

    if (inSpiMode & maskCPOL)       SPCR |=  (1 << CPOL);
    else                            SPCR &= ~(1 << CPOL);

#elif defined(USICR)
    // USI has no polarity support.
    if (inSpiMode & maskCPHA)
    {
        USICR |= (1 << USICS1) | (1 << USICS0);
    }
    else
    {
        USICR |=  (1 << USICS1);
        USICR &= ~(1 << USICS0);
    }
#endif
}

END_AK47_NAMESPACE
