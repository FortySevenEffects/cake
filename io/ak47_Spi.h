/*!
 *  \file       ak47_Spi.h
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

#include "ak47.h"
#include "ak47_Types.h"
#include "memory/ak47_RingBuffer.h"
#include <avr/io.h>

BEGIN_AK47_NAMESPACE

struct Spi
{
    enum Speed
    {
        // Regular speeds
        SpiFreq_4   = 0,
        SpiFreq_16  = 1,
        SpiFreq_64  = 2,
        SpiFreq_128 = 3,

        // 2X speeds
        SpiFreq_2   = 4,
        SpiFreq_8   = 5,
        SpiFreq_32  = 6,
    };
};

template<byte TxSize>
class SpiTransmitter
{
public:
    inline  SpiTransmitter();
    inline ~SpiTransmitter();

public:
    inline void send(byte inData);
    inline void sendAndWait(byte inData);
    static inline void waitForEndOfTransmission();

public: // Restricted - not for public usage.
    inline void startTransmission(byte inData);
    inline void handleEndOfTransmission();

protected:
    static inline bool isTransmitting();

protected:
    RingBuffer<TxSize> mTxBuffer;
};

// -----------------------------------------------------------------------------

template<byte RxSize>
class SpiReceiver
{
public:
    inline  SpiReceiver();
    inline ~SpiReceiver();

public:
    inline bool read(byte& outData);

public: // Restricted - call from interrupt handler
    inline void handleByteReceived(bool inStoreData = true);

protected:
    RingBuffer<RxSize> mRxBuffer;
};

// -----------------------------------------------------------------------------

template<byte TxSize>
class SpiMaster : public SpiTransmitter<TxSize>
{
public:
    inline  SpiMaster();
    inline ~SpiMaster();

public:
    inline void open();
    inline void close();

public:
    inline void setMode(byte inSpiMode);
    inline void setSpeed(Spi::Speed inSpeed);
    inline void setDataOrder(bool inLsbFirst);
};

// -----------------------------------------------------------------------------

template<byte RxSize>
class SpiSlave : public SpiReceiver<RxSize>
{
public:
    inline  SpiSlave();
    inline ~SpiSlave();

public:
    inline void open();
    inline void close();

public:
    inline void setMode(byte inSpiMode);
};

END_AK47_NAMESPACE

#include "io/ak47_Spi.hpp"
