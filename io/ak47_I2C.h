/*!
 *  \file       ak47_I2C.h
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

#include "ak47.h"
#include "ak47_Types.h"
#include "io/ak47_I2C_Devices.h"

BEGIN_AK47_NAMESPACE

class I2c
{
public:
    static inline void openMaster(byte inAddress);
    static inline void openSlave(byte inAddress);
    static inline void close();
    
public:
    static inline void write(byte inData);
    static inline byte read();
    
private:
    static byte mAddress;
    
};


END_AK47_NAMESPACE

#include "io/ak47_I2C.hpp"
