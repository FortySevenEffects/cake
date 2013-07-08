/*!
 *  \file       ak47_RingBuffer.h
 *  \author     Francois Best
 *  \date       23/10/2012
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

BEGIN_AK47_NAMESPACE

template <byte BufferSize, typename Type = byte>
class RingBuffer
{
public:
    explicit RingBuffer();
    ~RingBuffer();

public:
    inline bool empty() const;

public:
    inline void push(Type inData);
    inline Type pop();
    inline void clear();

protected:
    typedef volatile Type DataType;
    typedef volatile byte Index;

    DataType mData[BufferSize];
    Index mRead;
    Index mWrite;
};

END_AK47_NAMESPACE

#include "ak47_RingBuffer.hpp"
