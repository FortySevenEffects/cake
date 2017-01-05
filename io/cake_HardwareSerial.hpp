/*!
 *  \file       cake_HardwareSerial.hpp
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

BEGIN_CAKE_NAMESPACE

// -----------------------------------------------------------------------------
// Macros

#define UBBR_VALUE(baud)    (( (F_CPU) / 16 + (baud) / 2) / (baud) - 1)

#define UART_OPEN_IMPL(uart, baud)                                              \
template<>                                                                      \
template<>                                                                      \
inline void Uart<uart>::open<baud>()                                            \
{                                                                               \
    cli();                                                                      \
    /* Compute baud rate */                                                     \
    UBRR##uart##H = UBBR_VALUE(baud) >> 8;                                      \
    UBRR##uart##L = UBBR_VALUE(baud) & 0xFF;                                    \
                                                                                \
    UCSR##uart##A   = 0x00;                                                     \
    UCSR##uart##B   = (1 << RXEN##uart)    /* Enable RX */                      \
                    | (1 << TXEN##uart)    /* Enable TX */                      \
                    | (1 << RXCIE##uart);  /* Enable RX Interrupt */            \
    /* TX Interrupt will be enabled when data needs sending. */                 \
                                                                                \
    /* Defaults to 8-bit, no parity, 1 stop bit */                              \
    UCSR##uart##C   = (1 << UCSZ##uart##1) | (1 << UCSZ##uart##0);              \
    sei();                                                                      \
}

#define UART_IMPLEMENT_OPEN(uart)                                               \
    UART_OPEN_IMPL(uart, 4800)                                                  \
    UART_OPEN_IMPL(uart, 9600)                                                  \
    UART_OPEN_IMPL(uart, 14400)                                                 \
    UART_OPEN_IMPL(uart, 19200)                                                 \
    UART_OPEN_IMPL(uart, 28800)                                                 \
    UART_OPEN_IMPL(uart, 31250)                                                 \
    UART_OPEN_IMPL(uart, 38400)                                                 \
    UART_OPEN_IMPL(uart, 57600)                                                 \
    UART_OPEN_IMPL(uart, 76800)                                                 \
    UART_OPEN_IMPL(uart, 115200)                                                \
    UART_OPEN_IMPL(uart, 230400)                                                \
    UART_OPEN_IMPL(uart, 250000)                                                \
    UART_OPEN_IMPL(uart, 500000)                                                \
    UART_OPEN_IMPL(uart, 1000000)

#define UART_ENABLE_TX_INT(uart)    UCSR##uart##B |=  (1 << UDRIE##uart)
#define UART_DISABLE_TX_INT(uart)   UCSR##uart##B &= ~(1 << UDRIE##uart)

// -----------------------------------------------------------------------------

template<byte UartNumber>
inline Uart<UartNumber>::Uart()
{
}

template<byte UartNumber>
inline Uart<UartNumber>::~Uart()
{
}

// -----------------------------------------------------------------------------

#ifdef UART0
UART_IMPLEMENT_OPEN(0);
#endif

#ifdef UART1
UART_IMPLEMENT_OPEN(1);
#endif

#ifdef UART2
UART_IMPLEMENT_OPEN(2);
#endif

#ifdef UART3
UART_IMPLEMENT_OPEN(3);
#endif

// -----------------------------------------------------------------------------

#ifdef UART0
template<>
inline void Uart<0>::close()
{
    UCSR0B = 0x00;
}
#endif

#ifdef UART1
template<>
inline void Uart<1>::close()
{
    UCSR1B = 0x00;
}
#endif

#ifdef UART2
template<>
inline void Uart<2>::close()
{
    UCSR2B = 0x00;
}
#endif

#ifdef UART3
template<>
inline void Uart<3>::close()
{
    UCSR3B = 0x00;
}
#endif

// -----------------------------------------------------------------------------

template<byte UartNumber>
inline bool Uart<UartNumber>::available() const
{
    return !(mRxBuffer.empty());
}

template<byte UartNumber>
inline byte Uart<UartNumber>::read()
{
    if (!mRxBuffer.empty())
        return mRxBuffer.pop();
    return 0xFF;
}

// -----------------------------------------------------------------------------

#ifdef UART0
template<>
inline void Uart<0>::write(byte inData)
{
    UART_DISABLE_TX_INT(0);
    mTxBuffer.push(inData);
    UART_ENABLE_TX_INT(0);
}
#endif

#ifdef UART1
template<>
inline void Uart<1>::write(byte inData)
{
    UART_DISABLE_TX_INT(1);
    mTxBuffer.push(inData);
    UART_ENABLE_TX_INT(1);
}
#endif

#ifdef UART2
template<>
inline void Uart<2>::write(byte inData)
{
    UART_DISABLE_TX_INT(2);
    mTxBuffer.push(inData);
    UART_ENABLE_TX_INT(2);
}
#endif

#ifdef UART3
template<>
inline void Uart<3>::write(byte inData)
{
    UART_DISABLE_TX_INT(3);
    mTxBuffer.push(inData);
    UART_ENABLE_TX_INT(3);
}
#endif

template<byte UartNumber>
inline void Uart<UartNumber>::write(const byte* inData,
                                    unsigned inSize)
{
    for (unsigned i = 0; i < inSize; ++i)
    {
        write(inData[i]);
    }
}

// -----------------------------------------------------------------------------

#ifdef UART0
template<>
inline void Uart<0>::busyWrite(byte inData)
{
    UDR0 = inData;
    while (!(UCSR0A & (1 << UDRE0)));
}
#endif

#ifdef UART1
template<>
inline void Uart<1>::busyWrite(byte inData)
{
    UDR1 = inData;
    while (!(UCSR1A & (1 << UDRE1)));
}
#endif

#ifdef UART2
template<>
inline void Uart<2>::busyWrite(byte inData)
{
    UDR2 = inData;
    while (!(UCSR2A & (1 << UDRE2)));
}
#endif

#ifdef UART3
template<>
inline void Uart<3>::busyWrite(byte inData)
{
    UDR3 = inData;
    while (!(UCSR3A & (1 << UDRE3)));
}
#endif

/*! \brief Write data and wait until end of transmission.

 Unlike write, this method will wait for each byte to be transmitted to send
 the next one. It does not use the TX buffer, allowing large amounts of data
 to be sent without the need of a big TX buffer size.
 */
template<byte UartNumber>
inline void Uart<UartNumber>::busyWrite(const byte* inData,
                                        unsigned inSize)
{
    for (unsigned i = 0; i < inSize; ++i)
    {
        busyWrite(inData[i]);
    }
}

// -----------------------------------------------------------------------------

template<byte UartNumber>
inline void Uart<UartNumber>::clearRxBuffer()
{
    mRxBuffer.clear();
}

template<byte UartNumber>
inline void Uart<UartNumber>::clearTxBuffer()
{
    mTxBuffer.clear();
}

// -----------------------------------------------------------------------------

template<byte UartNumber>
inline void Uart<UartNumber>::handleByteReceived(byte inData)
{
    mRxBuffer.push(inData);
}

// -----------------------------------------------------------------------------

#ifdef UART0
template<>
inline void Uart<0>::handleTxReady()
{
    if (!mTxBuffer.empty())
    {
        UDR0 = mTxBuffer.pop();
    }
    else
    {
        // No more data to be sent, disable TX interrupt.
        UART_DISABLE_TX_INT(0);
    }
}
#endif

#ifdef UART1
template<>
inline void Uart<1>::handleTxReady()
{
    if (!mTxBuffer.empty())
    {
        UDR1 = mTxBuffer.pop();
    }
    else
    {
        // No more data to be sent, disable TX interrupt.
        UART_DISABLE_TX_INT(1);
    }
}
#endif

#ifdef UART2
template<>
inline void Uart<2>::handleTxReady()
{
    if (!mTxBuffer.empty())
    {
        UDR2 = mTxBuffer.pop();
    }
    else
    {
        // No more data to be sent, disable TX interrupt.
        UART_DISABLE_TX_INT(2);
    }
}
#endif

#ifdef UART3
template<>
inline void Uart<3>::handleTxReady()
{
    if (!mTxBuffer.empty())
    {
        UDR3 = mTxBuffer.pop();
    }
    else
    {
        // No more data to be sent, disable TX interrupt.
        UART_DISABLE_TX_INT(3);
    }
}
#endif

// -----------------------------------------------------------------------------

#undef UART_OPEN_IMPL
#undef UART_IMPLEMENT_OPEN
#undef UBBR_VALUE
#undef UART_ENABLE_TX_INT
#undef UART_DISABLE_TX_INT

END_CAKE_NAMESPACE
