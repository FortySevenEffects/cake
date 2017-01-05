#pragma once

#include "cake.h"
#include "cake_Types.h"
#include "memory/cake_RingBuffer.h"
#include <avr/io.h>

BEGIN_CAKE_NAMESPACE

struct Spi
{
    enum Speed
    {
        // Regular speeds
        SpiFreq_4   = 0,
        SpiFreq_16  = 1,
        SpiFreq_64  = 2,
        SpiFreq_128 = 3,

        // 2X speeds
        SpiFreq_2   = 4,
        SpiFreq_8   = 5,
        SpiFreq_32  = 6,
    };
};

template<byte TxSize>
class SpiTransmitter
{
public:
    inline  SpiTransmitter();
    inline ~SpiTransmitter();

public:
    inline void send(byte inData);
    inline void sendAndWait(byte inData);
    static inline void waitForEndOfTransmission();

public: // Restricted - not for public usage.
    inline void startTransmission(byte inData);
    inline void handleEndOfTransmission();

protected:
    static inline bool isTransmitting();

protected:
    RingBuffer<TxSize> mTxBuffer;
};

// -----------------------------------------------------------------------------

template<byte RxSize>
class SpiReceiver
{
public:
    inline  SpiReceiver();
    inline ~SpiReceiver();

public:
    inline bool read(byte& outData);

public: // Restricted - call from interrupt handler
    inline void handleByteReceived(bool inStoreData = true);

protected:
    RingBuffer<RxSize> mRxBuffer;
};

// -----------------------------------------------------------------------------

template<byte TxSize>
class SpiMaster : public SpiTransmitter<TxSize>
{
public:
    inline  SpiMaster();
    inline ~SpiMaster();

public:
    inline void open();
    inline void close();

public:
    inline void setMode(byte inSpiMode);
    inline void setSpeed(Spi::Speed inSpeed);
    inline void setDataOrder(bool inLsbFirst);
};

// -----------------------------------------------------------------------------

template<byte RxSize>
class SpiSlave : public SpiReceiver<RxSize>
{
public:
    inline  SpiSlave();
    inline ~SpiSlave();

public:
    inline void open();
    inline void close();

public:
    inline void setMode(byte inSpiMode);
};

END_CAKE_NAMESPACE

#include "io/cake_Spi.hpp"
