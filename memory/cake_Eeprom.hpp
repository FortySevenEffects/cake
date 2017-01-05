#pragma once

BEGIN_CAKE_NAMESPACE

inline byte Eeprom::read(uint16 inAddress)
{
    return eeprom_read_byte((const byte*)inAddress);
}

inline void Eeprom::write(uint16 inAddress, byte inData)
{
    eeprom_write_byte((byte*)inAddress, inData);
    eeprom_busy_wait();
}

inline void Eeprom::writeNoBlock(uint16 inAddress, byte inData)
{
    eeprom_write_byte((byte*)inAddress, inData);
}

inline void Eeprom::write(uint16 inAddress, const byte* inData, uint16 inSize)
{
    for (unsigned i = 0; i < inSize; ++i)
    {
        write(inAddress + i, inData[i]);
    }
}

END_CAKE_NAMESPACE
