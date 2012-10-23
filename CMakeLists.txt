
target(ak47)

append(ak47_SOURCES
    
    ak47.cpp
    ak47.h
    ak47_Namespace.h
    ak47_Types.cpp
    ak47_Types.h
    ak47_Assert.cpp
    ak47_Assert.hpp
    ak47_Assert.h
    
    memory/ak47_Memory.cpp
    memory/ak47_Memory.hpp
    memory/ak47_Memory.h
    memory/ak47_RingBuffer.cpp
    memory/ak47_RingBuffer.hpp
    memory/ak47_RingBuffer.h
    
    interrupts/ak47_PinChangeInterrupts.cpp
    interrupts/ak47_PinChangeInterrupts.hpp
    interrupts/ak47_PinChangeInterrupts.h
    interrupts/ak47_BadIsrCatcher.cpp
)

append(ak47_DEFS
	AVR_AK47=1
	AVR_BREAK_ON_ASSERT=1
)

build_avr_library(ak47)
