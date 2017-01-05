#pragma once

#include "cake.h"
#include "cake_Types.h"
#include "memory/cake_Register.h"
#include "memory/cake_RingBuffer.h"
#include "io/cake_HardwareSerial_Devices.h"
#include <avr/interrupt.h>

BEGIN_CAKE_NAMESPACE

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

END_CAKE_NAMESPACE;

#include "io/cake_HardwareSerial.hpp"
