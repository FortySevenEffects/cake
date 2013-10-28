/*!
 *  \file       ak47_HardwareSerial.h
 *  \author     Francois Best
 *  \date       16/06/2012
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
#include "memory/ak47_Register.h"
#include "memory/ak47_RingBuffer.h"
#include "io/ak47_HardwareSerial_Devices.h"
#include <avr/interrupt.h>

BEGIN_AK47_NAMESPACE

template<byte UartNumber>
class Uart
{
public:
    inline Uart();
    inline ~Uart();

public:
    template<uint16 BaudRate>
    inline void open();
    inline void close();

public:
    inline byte read();
    inline bool available() const;

public:
    inline void write(byte inData);
    inline void write(const byte* inData,
                      unsigned inSize);

    inline void busyWrite(byte inData);
    inline void busyWrite(const byte* inData,
                          unsigned inSize);

public:
    inline void clearRxBuffer();
    inline void clearTxBuffer();

public:
    inline void handleByteReceived(byte inData);
    inline void handleTxReady();

protected:
    static const byte sRxBufferSize = 32;
    static const byte sTxBufferSize = 32;
    RingBuffer<sRxBufferSize, byte> mRxBuffer;
    RingBuffer<sTxBufferSize, byte> mTxBuffer;
};

// -----------------------------------------------------------------------------

#ifdef UART0
typedef Uart<0> Uart0;
#endif

#ifdef UART1
typedef Uart<1> Uart1;
#endif

#ifdef UART2
typedef Uart<2> Uart2;
#endif

#ifdef UART3
typedef Uart<3> Uart3;
#endif

// -----------------------------------------------------------------------------

#define UART_ISR_RX_IMPL(uartNum, obj)                                          \
ISR(USART##uartNum##_RX_vect)                                                   \
{                                                                               \
    obj.handleByteReceived(UDR##uartNum);                                       \
}

#define UART_ISR_TX_IMPL(uartNum, obj)                                          \
ISR(USART##uartNum##_UDRE_vect)                                                 \
{                                                                               \
    obj.handleTxReady();                                                        \
}

END_AK47_NAMESPACE;

#include "io/ak47_HardwareSerial.hpp"
