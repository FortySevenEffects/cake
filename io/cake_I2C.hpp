#pragma once

BEGIN_CAKE_NAMESPACE

#define I2C_GET_BIT_RATE(speed)     ((F_CPU) / (2*(speed)) - 8)
#define I2C_GET_PRESCALE(speed)     (0)

/*
 Events:
 - Start
 - Stop
 - SLA+W
 - SLA+R
 - Data byte

 Transaction description (MT mode)
 - Start
 - SLA+W
 - Data out
 - ... (more data out)
 - Stop

 Transaction description (MR mode)
 - Start
 - SLA+R
 - Data in
 - ... (more data in)
 - Send NAK
 - Stop

 */

template<uint32 Speed>
inline void I2C::openMaster(byte inAddress)
{
    AVR_STATIC_ASSERT(Speed == speed_100k ||
                      Speed == speed_400k ||
                      Speed == speed_1M);

    TWAR = inAddress; // Spare a byte and store the address there.
    TWBR = I2C_GET_BIT_RATE(Speed);

    // Enable I2C
    I2cControlRegister.set(TWEN);
    enableInterrupt();
}

inline void I2C::close()
{
    disableInterrupt();
    I2cControlRegister.clear(TWEN);
}

// -----------------------------------------------------------------------------

inline void I2C::sendStart()
{
    I2cControlRegister.set(TWSTA);
    clearTwint();
    sExpected = TW_START;
}

inline void I2C::sendStop()
{
    I2cControlRegister.set(TWSTO);
    clearTwint();
    sExpected = TW_NO_INFO;
}

// -----------------------------------------------------------------------------

inline void I2C::writeHeader(bool inWriteMode)
{

}

inline void I2C::write(byte inData)
{
}

// -----------------------------------------------------------------------------

inline void I2C::enableInterrupt()
{
    I2cControlRegister.set(TWIE);
}

inline void I2C::disableInterrupt()
{
    I2cControlRegister.clear(TWIE);
}

inline void I2C::clearTwint()
{
    I2cControlRegister.clear(TWINT);
}

// -----------------------------------------------------------------------------

inline byte I2C::getStatus()
{
    return TW_STATUS; // Defined in avr-libc
}

// -----------------------------------------------------------------------------

inline void I2C::interruptCallback()
{
    // \todo get Status code, check expectations
    // Move on to the next level.
}

// -----------------------------------------------------------------------------

#undef I2C_GET_BIT_RATE
#undef I2C_GET_PRESCALE

// ########################################################################## //

I2cSession::I2cSession()
{
}

I2cSession::~I2cSession()
{
}

// -----------------------------------------------------------------------------

template<byte Size>
I2cTransmitterSession<Size>::I2cTransmitterSession()
{
}

template<byte Size>
I2cTransmitterSession<Size>::~I2cTransmitterSession()
{
}

// -----------------------------------------------------------------------------

template<byte Size>
inline void I2cTransmitterSession<Size>::send(const byte* inData,
                                              byte inSize)
{
    AVR_ASSERT(inSize <= Size);
    mBuffer.clear();
    for (byte i = 0; i < inSize; ++i)
    {
        mBuffer.push(inData[i]);
    }

    I2C::sCurrentSession = this;
}

END_CAKE_NAMESPACE
