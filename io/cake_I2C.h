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
