/*!
 *  \file       ak47_HardwareSerial.hpp
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

BEGIN_AK47_NAMESPACE

// -----------------------------------------------------------------------------
// Macros

#define UBBR_VALUE(baud)    (( (F_CPU) / 16 + (baud) / 2) / (baud) - 1)

#define UART_OPEN_IMPL(uart, baud)                                              \
template<>                                                                      \
template<>                                                                      \
inline void Uart<uart>::open<baud>()                                            \
{                                                                               \
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


#define UART_CLOSE(uart)                                                        \
{                                                                               \
    AVR_REGISTER(UCSR##uart##B, UartConfigRegisterB);                           \
    UartConfigRegisterB.clear(RXCIE##uart);                                     \
    UartConfigRegisterB.clear(TXCIE##uart);                                     \
    UartConfigRegisterB.clear(RXEN##uart);                                      \
    UartConfigRegisterB.clear(TXEN##uart);                                      \
    /*UCSR##uart##B &= ~(1 << RXCIE##uart) & ~(1 << TXCIE##uart) &              \
                     ~(1 << RXEN##uart)  & ~(1 << TXEN##uart);               */ \
}

#define UART_ENABLE_TX_INT(uart)    UCSR##uart##B |=  (1 << TXCIE##uart)
#define UART_DISABLE_TX_INT(uart)   UCSR##uart##B &= ~(1 << TXCIE##uart)

// -----------------------------------------------------------------------------

template<byte UartNumber>
Uart<UartNumber>::Uart()
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
    UART_CLOSE(0);
}
#endif

#ifdef UART1
template<>
inline void Uart<1>::close()
{
    UART_CLOSE(1);
}
#endif

#ifdef UART2
template<>
inline void Uart<2>::close()
{
    UART_CLOSE(2);
}
#endif

#ifdef UART3
template<>
inline void Uart<3>::close()
{
    UART_CLOSE(3);
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
    if (UCSR0B & (1 << TXCIE0))
    {
        // TX interrupt is enabled: transfer in progress -> push to buffer.
        mTxBuffer.push(inData);
    }
    else
    {
        // Ready to transmit.
        UART_ENABLE_TX_INT(0); // Activate TX interrupt
        UDR0 = inData;      // and send data.
    }
}
#endif

#ifdef UART1
template<>
inline void Uart<1>::write(byte inData)
{
    if (UCSR1B & (1 << TXCIE1))
    {
        // TX interrupt is enabled: transfer in progress -> push to buffer.
        mTxBuffer.push(inData);
    }
    else
    {
        // Ready to transmit.
        UART_ENABLE_TX_INT(1);  // Activate TX interrupt
        UDR1 = inData;          // and send data.
    }
}
#endif

#ifdef UART2
template<>
inline void Uart<2>::write(byte inData)
{
    if (UCSR2B & (1 << TXCIE2))
    {
        // TX interrupt is enabled: transfer in progress -> push to buffer.
        mTxBuffer.push(inData);
    }
    else
    {
        // Ready to transmit.
        UART_ENABLE_TX_INT(2);  // Activate TX interrupt
        UDR2 = inData;          // and send data.
    }
}
#endif

#ifdef UART3
template<>
inline void Uart<3>::write(byte inData)
{
    if (UCSR3B & (1 << TXCIE3))
    {
        // TX interrupt is enabled: transfer in progress -> push to buffer.
        mTxBuffer.push(inData);
    }
    else
    {
        // Ready to transmit.
        UART_ENABLE_TX_INT(3);  // Activate TX interrupt
        UDR3 = inData;          // and send data.
    }
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
inline void Uart<0>::handleEndOfTransmission()
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
inline void Uart<1>::handleEndOfTransmission()
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
inline void Uart<2>::handleEndOfTransmission()
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
inline void Uart<3>::handleEndOfTransmission()
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
#undef UART_CLOSE
#undef UBBR_VALUE
#undef UART_ENABLE_TX_INT
#undef UART_DISABLE_TX_INT

END_AK47_NAMESPACE
