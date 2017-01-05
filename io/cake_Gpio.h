#pragma once

#include "cake.h"
#include "cake_Types.h"
#include "memory/cake_Register.h"
#include <avr/io.h>

BEGIN_CAKE_NAMESPACE

template<class RegisterTraits>
class Port
{
public:
    typedef RegisterTraits Traits;

public:
    inline  Port();
    inline ~Port();

public: // Direction
    template<byte Pin>
    static inline void setInput(bool inWithPullUp = false);

    template<byte Pin>
    static inline void setOutput();

public: // Pin operations
    template<byte Pin>
    static inline void set();

    template<byte Pin>
    static inline void clear();

    template<byte Pin>
    static inline void toggle();

public: // Port operations
    static inline byte read();
    static inline void write(byte inValue);
};

// -----------------------------------------------------------------------------

template<class IOPort, byte IOBit>
class Pin
{
public:
    typedef IOPort Port;
    static const byte Bit = IOBit;

public:
    inline  Pin();
    inline ~Pin();

public:
    static inline void setInput(bool inWithPullUp = false);
    static inline void setOutput();

public:
    static inline void set();
    static inline void clear();
    static inline void toggle();
    static inline bool read();

public:
    static inline void pulseHigh();
    static inline void pulseLow();

public:
    struct ScopedPinSet
    {
        inline  ScopedPinSet();
        inline ~ScopedPinSet();
    };

    struct ScopedPinClear
    {
        inline  ScopedPinClear();
        inline ~ScopedPinClear();
    };

    struct ScopedPinToggle
    {
        inline  ScopedPinToggle();
        inline ~ScopedPinToggle();
    };
};

// -----------------------------------------------------------------------------

template<class Port, byte Mask>
class PinGroup
{
public:
    inline  PinGroup();
    inline ~PinGroup();

public:
    static inline void setInput(bool inWithPullUp = false);
    static inline void setOutput();

public:
    static inline void set(byte inValue);
    static inline void clear();
    static inline byte read();

private:
    static inline byte getShift();
};

// -----------------------------------------------------------------------------

class DummyPin
{
public:
    inline  DummyPin() { }
    inline ~DummyPin() { }

public:
    static inline void setInput(bool inWithPullUp = false) { }
    static inline void setOutput() { }

public:
    static inline void set() { }
    static inline void clear() { }
    static inline void toggle() { }
    static inline bool read() { return false; }

public:
    static inline void pulseHigh() { }
    static inline void pulseLow() { }

public:
    struct ScopedPinSet
    {
        inline  ScopedPinSet() { }
        inline ~ScopedPinSet() { }
    };

    struct ScopedPinClear
    {
        inline  ScopedPinClear() { }
        inline ~ScopedPinClear() { }
    };

    struct ScopedPinToggle
    {
        inline  ScopedPinToggle() { }
        inline ~ScopedPinToggle() { }
    };
};

END_CAKE_NAMESPACE

#include "io/cake_Gpio.hpp"
