/*!
 *  \file       ak47_HardwareSerial.hpp
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

#pragma once

BEGIN_AK47_NAMESPACE

// -----------------------------------------------------------------------------
// Macros

#define UBBR_VALUE(baud)    (( (F_CPU) / 16 + (baud) / 2) / (baud) - 1)

#define UART_OPEN(uart, baud)                                                   \
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
    /* TX Interrupt will be enabled when data is being sent. */                 \
                                                                                \
    /* Defaults to 8-bit, no parity, 1 stop bit */                              \
    UCSR##uart##C   = (1 << UCSZ##uart##1) | (1 << UCSZ##uart##0);              \
}   

#define UART_IMPLEMENT_OPEN(uart)                                               \
    UART_OPEN(uart, 4800)                                                       \
    UART_OPEN(uart, 9600)                                                       \
    UART_OPEN(uart, 14400)                                                      \
    UART_OPEN(uart, 19200)                                                      \
    UART_OPEN(uart, 28800)                                                      \
    UART_OPEN(uart, 31250)                                                      \
    UART_OPEN(uart, 38400)                                                      \
    UART_OPEN(uart, 57600)                                                      \
    UART_OPEN(uart, 76800)                                                      \
    UART_OPEN(uart, 115200)                                                     \
    UART_OPEN(uart, 230400)                                                     \
    UART_OPEN(uart, 250000)                                                     \
    UART_OPEN(uart, 500000)                                                     \
    UART_OPEN(uart, 1000000)


#define UART_CLOSE(uart)                                                        \
{                                                                               \
    UCSR##uart##B &= ~(1 << RXCIE##uart) & ~(1 << TXCIE##uart) &                \
                     ~(1 << RXEN##uart)  & ~(1 << TXEN##uart);                  \
}

#define UART_ENABLE_TX_INT(uart)    UCSR##uart##B |=  (1 << TXCIE##uart)
#define UART_DISABLE_TX_INT(uart)   UCSR##uart##B &= ~(1 << TXCIE##uart)

// -----------------------------------------------------------------------------

template<unsigned UartNumber>
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

template<unsigned UartNumber>
inline bool Uart<UartNumber>::available() const
{
    return !(mRxBuffer.empty());
}

template<unsigned UartNumber>
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

template<unsigned UartNumber>
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
template<unsigned UartNumber>
inline void Uart<UartNumber>::busyWrite(const byte* inData,
                                        unsigned inSize)
{
    for (unsigned i = 0; i < inSize; ++i)
    {
        busyWrite(inData[i]);
    }
}

// -----------------------------------------------------------------------------

template<unsigned UartNumber>
inline void Uart<UartNumber>::flushRxBuffer()
{
    mRxBuffer.flush();
}

template<unsigned UartNumber>
inline void Uart<UartNumber>::flushTxBuffer()
{
    mTxBuffer.flush();
}

// -----------------------------------------------------------------------------

template<unsigned UartNumber>
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

#undef UART_OPEN
#undef UART_IMPLEMENT_OPEN
#undef UART_CLOSE
#undef UBBR_VALUE
#undef UART_ENABLE_TX_INT
#undef UART_DISABLE_TX_INT


/*
// -----------------------------------------------------------------------------
// Construction & Initialisation

template <unsigned tUARTNumber>
void UART<tUARTNumber>::begin(unsigned inBaudRate)
{
    mRXBuffer.init();
    mTXBuffer.init();
    
    mTXReady = true;
    
#if defined(UBRRH) || defined(UBRR0H)
    if (tUARTNumber == 0) { mDataRegister = &UDR0; BEGIN_SERIAL(0,inBaudRate); }
#endif
#if defined(UBRR1H)
    if (tUARTNumber == 1) { mDataRegister = &UDR1; BEGIN_SERIAL(1,inBaudRate); }
#endif
#if defined(UBRR2H)
    if (tUARTNumber == 2) { mDataRegister = &UDR2; BEGIN_SERIAL(2,inBaudRate); }
#endif
#if defined(UBRR3H)
    if (tUARTNumber == 3) { mDataRegister = &UDR3; BEGIN_SERIAL(3,inBaudRate); }
#endif
}


// -----------------------------------------------------------------------------
// Interfaces

template <unsigned tUARTNumber>
byte UART<tUARTNumber>::available() 
{
    return mRXBuffer.available();
}

template <unsigned tUARTNumber>
void UART<tUARTNumber>::write(byte inData) 
{
    if (mTXReady)
    {
        mTXReady = false;
        *mDataRegister = inData;
    }
    else
    {
        mTXBuffer.push(inData);
    }
}

template <unsigned tUARTNumber>
byte UART<tUARTNumber>::read()
{
    if (available())
        return mRXBuffer.pop();
    return 0xFF;
}

template <unsigned tUARTNumber>
void UART<tUARTNumber>::flush()
{
    mRXBuffer.flush();
}

template <unsigned tUARTNumber>
void UART<tUARTNumber>::receive(byte Incoming)
{
    mRXBuffer.push(Incoming);
}

// Print

template <unsigned tUARTNumber> void UART<tUARTNumber>::print(uint8_t b) {
    write(b);
}
template <unsigned tUARTNumber> void UART<tUARTNumber>::print(char c) {
  print((byte) c);
}
template <unsigned tUARTNumber> void UART<tUARTNumber>::print(const char c[]) {
  while (*c)
    print(*c++);
}
template <unsigned tUARTNumber> void UART<tUARTNumber>::print(int n) {
  print((long) n);
}
template <unsigned tUARTNumber> void UART<tUARTNumber>::print(unsigned int n) {
  print((unsigned long) n);
}
template <unsigned tUARTNumber> void UART<tUARTNumber>::print(long n) {
  if (n < 0) {
    print('-');
    n = -n;
  }
  printNumber(n, 10);
}
template <unsigned tUARTNumber> void UART<tUARTNumber>::print(unsigned long n) {
  printNumber(n, 10);
}
template <unsigned tUARTNumber> void UART<tUARTNumber>::print(long n, int base) {
  if (base == 0)
    print((char) n);
  else if (base == 10)
    print(n);
  else
    printNumber(n, base);
}
template <unsigned tUARTNumber> void UART<tUARTNumber>::print(double n, int inDigits) {
  printFloat(n,inDigits);
}
template <unsigned tUARTNumber> void UART<tUARTNumber>::printNumber(unsigned long n, uint8_t base) {
  unsigned char buf[8 * sizeof(long)]; // Assumes 8-bit chars. 
  unsigned long i = 0;

  if (n == 0) {
    print('0');
    return;
  } 

  while (n > 0) {
    buf[i++] = n % base;
    n /= base;
  }

  for (; i > 0; i--)
    print((char) (buf[i - 1] < 10 ?
      '0' + buf[i - 1] :
      'A' + buf[i - 1] - 10));
}
template <unsigned tUARTNumber> void UART<tUARTNumber>::printFloat(double number, uint8_t digits) { 
  // Handle negative numbers
  if (number < 0.0)
  {
     print('-');
     number = -number;
  }

  // Round correctly so that print(1.999, 2) prints as "2.00"
  double rounding = 0.5;
  for (uint8_t i=0; i<digits; ++i)
    rounding /= 10.0;
  
  number += rounding;

  // Extract the integer part of the number and print it
  unsigned long int_part = (unsigned long)number;
  double remainder = number - (double)int_part;
  print(int_part);

  // Print the decimal point, but only if there are digits beyond
  if (digits > 0)
    print("."); 

  // Extract digits from the remainder one at a time
  while (digits-- > 0)
  {
    remainder *= 10.0;
    int toPrint = int(remainder);
    print(toPrint);
    remainder -= toPrint; 
  } 
}


template <unsigned tUARTNumber>
void UART<tUARTNumber>::endOfTransmission()
{
    if (mTXBuffer.available())
        *mDataRegister = mTXBuffer.pop();
    else
        mTXReady = true;
}
*/

END_AK47_NAMESPACE
