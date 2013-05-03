/*!
 *  \file       ak47_HardwareSerial.cpp
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

#include "io/ak47_HardwareSerial.h"
#include <avr/interrupt.h>

BEGIN_AK47_NAMESPACE

template<byte UartNumber>
Uart<UartNumber> Uart<UartNumber>::sInstance;

END_AK47_NAMESPACE

// -----------------------------------------------------------------------------
// Interrupts Macros

#define UART_ISR_RX(uartNum) ISR(USART##uartNum##_RX_vect)                       \
{                                                                               \
    ak47::Uart<uartNum>::sInstance.handleByteReceived(UDR##uartNum);                                    \
}

#define UART_ISR_TX(uartNum) ISR(USART##uartNum##_TX_vect)                       \
{                                                                               \
    ak47::Uart<uartNum>::sInstance.handleEndOfTransmission();                                        \
}

// -----------------------------------------------------------------------------

#ifdef UART0
UART_ISR_RX(0);
UART_ISR_TX(0);
#endif

#ifdef UART1
UART_ISR_RX(1);
UART_ISR_TX(1);
#endif

#ifdef UART2
UART_ISR_RX(2);
UART_ISR_TX(2);
#endif

#ifdef UART3
UART_ISR_RX(3);
UART_ISR_TX(3);
#endif
