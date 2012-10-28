/*!
 *  \file       ak47_HardwareSerial.cpp
 *  \author     Francois Best
 *  \date       16/06/2012
 *  \license    CC-BY-SA Forty Seven Effects - 2012
 *
 * THE WORK (AS DEFINED BELOW) IS PROVIDED UNDER THE TERMS 
 * OF THIS CREATIVE COMMONS PUBLIC LICENSE ("CCPL" OR "LICENSE").
 * THE WORK IS PROTECTED BY COPYRIGHT AND/OR OTHER APPLICABLE LAW. 
 * ANY USE OF THE WORK OTHER THAN AS AUTHORIZED UNDER THIS LICENSE 
 * OR COPYRIGHT LAW IS PROHIBITED.
 * 
 * BY EXERCISING ANY RIGHTS TO THE WORK PROVIDED HERE, YOU ACCEPT 
 * AND AGREE TO BE BOUND BY THE TERMS OF THIS LICENSE. 
 * TO THE EXTENT THIS LICENSE MAY BE CONSIDERED TO BE A CONTRACT, 
 * THE LICENSOR GRANTS YOU THE RIGHTS CONTAINED HERE IN CONSIDERATION 
 * OF YOUR ACCEPTANCE OF SUCH TERMS AND CONDITIONS.
 * http://creativecommons.org/licenses/by-sa/3.0/
 */

#include "io/ak47_HardwareSerial.h"
#include <avr/interrupt.h>

BEGIN_AK47_NAMESPACE

#ifdef UART0
Uart<0> Uart0;
#endif

#ifdef UART1
Uart<1> Uart1;
#endif

#ifdef UART2
Uart<2> Uart2;
#endif

#ifdef UART3
Uart<3> Uart3;
#endif

END_AK47_NAMESPACE

// -----------------------------------------------------------------------------
// Interrupts Macros

#define UART_ISR_RX(uart, obj) ISR(USART##uart##_RX_vect)                            \
{                                                                               \
    ak47::obj.handleByteReceived(UDR##uart);                                    \
}

#define UART_ISR_TX(uart, obj) ISR(USART##uart##_TX_vect)                       \
{                                                                               \
    ak47::obj.handleEndOfTransmission();                                        \
}

// -----------------------------------------------------------------------------

#ifdef UART0
UART_ISR_RX(0, Uart0);
UART_ISR_TX(0, Uart0);
#endif

#ifdef UART1
UART_ISR_RX(1, Uart1);
UART_ISR_TX(1, Uart1);
#endif

#ifdef UART2
UART_ISR_RX(2, Uart2);
UART_ISR_TX(2, Uart2);
#endif

#ifdef UART3
UART_ISR_RX(3, Uart3);
UART_ISR_TX(3, Uart3);
#endif
