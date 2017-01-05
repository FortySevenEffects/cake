/*!
 *  \file       cake_I2C.h
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

#include "cake.h"
#include "cake_Types.h"
#include "memory/cake_RingBuffer.h"
#include "io/cake_I2C_Devices.h"
#include <util/twi.h>

#ifdef TWI_vect

BEGIN_CAKE_NAMESPACE

class I2cSession;

class I2C
{
public:
    enum // Bus speeds, assuming prescaler = 0
    {
        speed_100k = 100000,    // 100 kHz bus speed
        speed_400k = 400000,    // 400 kHz bus speed
        speed_1M   = 1000000,   // 1 MHz bus speed
    };

public:
    template<uint32 Speed>
    static inline void openMaster(byte inAddress);
    static inline void close();

public:
    static inline void sendStart();
    static inline void sendStop();


    static inline void writeHeader(bool inWriteMode = true);
    static inline void write(byte inData);

private:
    static inline void enableInterrupt();
    static inline void disableInterrupt();
    static inline void clearTwint();
    static inline byte getStatus();

private:
    static byte sExpected;

public:
    static I2cSession* sCurrentSession;
    static inline void interruptCallback();
};

// -----------------------------------------------------------------------------

class I2cSession
{
public:
    I2cSession();
    ~I2cSession();
};

// -----------------------------------------------------------------------------

template<byte Size>
class I2cTransmitterSession
    : public I2cSession
{
public:
    I2cTransmitterSession();
    ~I2cTransmitterSession();

public:
    inline void send(const byte* inData,
                     byte inSize);

private:
    RingBuffer<Size> mBuffer;
};

// -----------------------------------------------------------------------------

END_CAKE_NAMESPACE

#include "io/cake_I2C.hpp"

#endif // TWI_vect
