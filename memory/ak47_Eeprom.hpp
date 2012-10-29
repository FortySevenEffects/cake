/*!
 *  \file       ak47_Eeprom.hpp
 *  \author     Francois Best
 *  \date       27/10/2012
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
