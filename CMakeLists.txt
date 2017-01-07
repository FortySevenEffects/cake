target(cake)

target_sources(cake
    cake.cpp
    cake.h
    cake_Defs.h
    cake_Namespace.h
    cake_Types.cpp
    cake_Types.h
    cake_Assert.h
    cake_Debug.cpp
    cake_Debug.hpp
    cake_Debug.h

    memory/cake_Memory.cpp
    memory/cake_Memory.hpp
    memory/cake_Memory.h
    memory/cake_Register.cpp
    memory/cake_Register.hpp
    memory/cake_Register.h
    memory/cake_Eeprom.cpp
    memory/cake_Eeprom.hpp
    memory/cake_Eeprom.h
    memory/cake_GeneralPurposeRegisters.cpp
    memory/cake_GeneralPurposeRegisters.hpp
    memory/cake_GeneralPurposeRegisters.h
    memory/cake_ProgramSpace.cpp
    memory/cake_ProgramSpace.hpp
    memory/cake_ProgramSpace.h
    memory/cake_RingBuffer.cpp
    memory/cake_RingBuffer.hpp
    memory/cake_RingBuffer.h

    time/cake_Timer.cpp
    time/cake_Timer.hpp
    time/cake_Timer.h

    interrupts/cake_Atomic.cpp
    interrupts/cake_Atomic.hpp
    interrupts/cake_Atomic.h
    interrupts/cake_ExternalInterrupt.cpp
    interrupts/cake_ExternalInterrupt.hpp
    interrupts/cake_ExternalInterrupt.h
    interrupts/cake_PinChangeInterrupts.cpp
    interrupts/cake_PinChangeInterrupts.hpp
    interrupts/cake_PinChangeInterrupts.h
    interrupts/cake_BadIsrCatcher.cpp

    io/cake_Analog.cpp
    io/cake_Analog.hpp
    io/cake_Analog.h
    io/cake_Gpio.cpp
    io/cake_Gpio.hpp
    io/cake_Gpio.h
    io/cake_HardwareSerial.cpp
    io/cake_HardwareSerial.hpp
    io/cake_HardwareSerial.h
    io/cake_HardwareSerial_Devices.h
    io/cake_I2C.cpp
    io/cake_I2C.hpp
    io/cake_I2C.h
    io/cake_Spi.cpp
    io/cake_Spi.hpp
    io/cake_Spi.h
)

target_defs(cake
    AVR_CAKE=1
    AVR_BREAK_ON_ASSERT=1
)

build_static_library(cake)
