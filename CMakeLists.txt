
target(ak47)

append(ak47_SOURCES

    ak47.cpp
    ak47.h
    ak47_Defs.h
    ak47_Namespace.h
    ak47_Types.cpp
    ak47_Types.h
    ak47_Assert.h
    ak47_Debug.cpp
    ak47_Debug.hpp
    ak47_Debug.h

    memory/ak47_Memory.cpp
    memory/ak47_Memory.hpp
    memory/ak47_Memory.h
    memory/ak47_Register.cpp
    memory/ak47_Register.hpp
    memory/ak47_Register.h
    memory/ak47_Eeprom.cpp
    memory/ak47_Eeprom.hpp
    memory/ak47_Eeprom.h
    memory/ak47_GeneralPurposeRegisters.cpp
    memory/ak47_GeneralPurposeRegisters.hpp
    memory/ak47_GeneralPurposeRegisters.h
    memory/ak47_ProgramSpace.cpp
    memory/ak47_ProgramSpace.hpp
    memory/ak47_ProgramSpace.h
    memory/ak47_RingBuffer.cpp
    memory/ak47_RingBuffer.hpp
    memory/ak47_RingBuffer.h

    time/ak47_Timer.cpp
    time/ak47_Timer.hpp
    time/ak47_Timer.h

    interrupts/ak47_Atomic.cpp
    interrupts/ak47_Atomic.hpp
    interrupts/ak47_Atomic.h
    interrupts/ak47_PinChangeInterrupts.cpp
    interrupts/ak47_PinChangeInterrupts.hpp
    interrupts/ak47_PinChangeInterrupts.h
    interrupts/ak47_BadIsrCatcher.cpp

    io/ak47_Analog.cpp
    io/ak47_Analog.hpp
    io/ak47_Analog.h
    io/ak47_Gpio.cpp
    io/ak47_Gpio.hpp
    io/ak47_Gpio.h
    io/ak47_HardwareSerial.cpp
    io/ak47_HardwareSerial.hpp
    io/ak47_HardwareSerial.h
    io/ak47_HardwareSerial_Devices.h
    io/ak47_I2C.cpp
    io/ak47_I2C.hpp
    io/ak47_I2C.h
    io/ak47_Spi.cpp
    io/ak47_Spi.hpp
    io/ak47_Spi.h
)

append(ak47_DEFS
    AVR_AK47=1
    AVR_BREAK_ON_ASSERT=1
)

build_avr_library(ak47)
