/*!
 *  \file       ak47_Eeprom.hpp
 *  \author     Francois Best
 *  \date       27/10/2012
 *  \license    GPL v3.0 - Copyright Forty Seven Effects 2012
 *
 *	This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details: http://www.gnu.org/licenses
 */

#pragma once

BEGIN_AK47_NAMESPACE

byte Eeprom::read(uint16 inAddress)
{
    return eeprom_read_byte((const byte*)inAddress);
}

void Eeprom::write(uint16 inAddress, byte inData)
{
    eeprom_write_byte((byte*)inAddress, inData);
    eeprom_busy_wait();
}

void Eeprom::write(uint16 inAddress, const byte* inData, uint16 inSize)
{
    for (unsigned i = 0; i < inSize; ++i)
    {
        write(inAddress + i, inData[i]);
    }
}

END_AK47_NAMESPACE
