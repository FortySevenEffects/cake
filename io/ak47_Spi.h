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

class Spi
{
public:
     Spi();
    ~Spi();
    
public:
    AVR_TYPEDEF_FUNCTOR(void, Parser, byte);
    
public:
    inline void openMaster(Parser* inParser = 0);
    inline void openSlave(Parser* inParser);
    inline void close();
    
public: // Master only
    inline void write(byte inData);
    inline void write(const byte* inData, byte inLenght);
    inline void busyWrite(byte inData);
    inline void busyWrite(const byte* inData, byte inLenght);
    
public: // Master & Slave
    inline bool available() const;
    inline byte read();
    
public: // Master & Slave
    inline void handleByteReceived(byte inData);
    inline void handleEndOfTransmission();
    
public:
    inline void clearRxBuffer();
    inline void clearTxBuffer();
    
private:
    static const byte sRxBufferSize = 16;
    static const byte sTxBufferSize = 16;
    RingBuffer<sRxBufferSize> mRxBuffer;
    RingBuffer<sTxBufferSize> mTxBuffer;
    Parser* mParser;
};

END_AK47_NAMESPACE

#include "io/ak47_Spi.hpp"
