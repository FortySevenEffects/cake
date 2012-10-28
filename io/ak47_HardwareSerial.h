/*!
 *  \file       ak47_HardwareSerial.h
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

#include "ak47.h"
#include "ak47_Types.h"
#include "memory/ak47_RingBuffer.h"
#include <avr/io.h>

BEGIN_AK47_NAMESPACE

template<unsigned UartNumber>
class Uart
{   
public:
    explicit Uart();
    inline void init();
    
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
    inline void flushRxBuffer();
    inline void flushTxBuffer();
    
public:
    inline void handleByteReceived(byte inReceived);
    inline void handleEndOfTransmission();
    
protected:
    static const byte sRxBufferSize = 32;
    static const byte sTxBufferSize = 32;
    RingBuffer<sRxBufferSize, byte> mRxBuffer;
    RingBuffer<sTxBufferSize, byte> mTxBuffer;
};

// -----------------------------------------------------------------------------
// Hardware Abstraction

#if defined (__AVR_ATmega644P__)
#   define UART0
#   define UART1
#elif defined (__AVR_ATmega32U4__)
#   define UART1
#elif defined (__AVR_ATtiny84__)
#   define NO_UART  // No UART available
#else
#   error Implement abstraction for this target chip.
#endif

// -----------------------------------------------------------------------------

#ifdef UART0
extern Uart<0> Uart0;
#endif

#ifdef UART1
extern Uart<1> Uart1;
#endif

#ifdef UART2
extern Uart<2> Uart2;
#endif

#ifdef UART3
extern Uart<3> Uart3;
#endif

/*
template <unsigned tUARTNumber>
class UART
{
public:
    
    // -------------------------------------------------------------------------
    // Construction & Initialisation
    
    void begin(unsigned inBaudRate);
    
    
    // -------------------------------------------------------------------------
    // Interfaces
    
    byte available();
    byte read();
    void flush();
    
    void print(char);
    void print(const char[]);
    void print(uint8_t);
    void print(int);
    void print(unsigned int);
    void print(long);
    void print(unsigned long);
    void print(long, int);
    void print(double,int inDigits = 2);

    inline UART& operator<<(char arg)           { print(arg); return *this; }
    inline UART& operator<<(const char *arg)    { print(arg); return *this; }
    inline UART& operator<<(uint8_t arg)        { print(arg); return *this; }
    inline UART& operator<<(int arg)            { print(arg); return *this; }
    inline UART& operator<<(unsigned int arg)   { print(arg); return *this; }
    inline UART& operator<<(long arg)           { print(arg); return *this; }
    inline UART& operator<<(unsigned long arg)  { print(arg); return *this; }
    inline UART& operator<<(double arg)         { print(arg); return *this; }
    
    void write(byte inData);
    
    void receive(byte inReceived);

    void endOfTransmission();
    
    void printNumber(unsigned long, uint8_t);
    
    bool isReadyToPrint() const
    {
        return mTXReady;
    }
    
    
protected:
    
    void printFloat(double, uint8_t);
    
    
    static const byte bufferSize = 128;
    
    core::RingBuffer<bufferSize>    mRXBuffer;
    core::RingBuffer<bufferSize>    mTXBuffer;
    
    volatile bool                   mTXReady;
    volatile uint8_t*               mDataRegister;
    
};
*/

END_AK47_NAMESPACE;
                      
#include "io/ak47_HardwareSerial.hpp"
