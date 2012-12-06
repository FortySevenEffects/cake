/*!
 *  \file       ak47_RingBuffer.hpp
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

BEGIN_AK47_NAMESPACE

template <byte BufferSize, typename Type>
RingBuffer<BufferSize, Type>::RingBuffer()
    : mRead(0)
    , mWrite(0)
{
    // Implement other sizes if needed.
    AVR_STATIC_ASSERT(sizeof(Type) == 1);
    // Check that buffer size is a power of two less than 256.
    AVR_STATIC_ASSERT(BufferSize <= 256 &&
                      (BufferSize != 0) && !(BufferSize & (BufferSize - 1)));
}

template <byte BufferSize, typename Type>
RingBuffer<BufferSize, Type>::~RingBuffer()
{
}

// -----------------------------------------------------------------------------

template <byte BufferSize, typename Type>
bool RingBuffer<BufferSize, Type>::empty() const
{
    return mRead == mWrite;
}

// -----------------------------------------------------------------------------

template <byte BufferSize, typename Type>
void RingBuffer<BufferSize, Type>::push(Type inData)
{
    mData[mWrite++] = inData;
    mWrite &= (BufferSize - 1); // Modulo for powers of two.
    
    // Overflow -> increment buffer size.
    AVR_ASSERT(mWrite != mRead);
}

template <byte BufferSize, typename Type>
Type RingBuffer<BufferSize, Type>::pop()
{
    // You should always check if there is available data before calling pop.
    AVR_ASSERT(!empty());
    
    const DataType data = mData[mRead++];
    mRead &= (BufferSize - 1);
    
    return data;
}

template <byte BufferSize, typename Type>
void RingBuffer<BufferSize, Type>::clear()
{
    mWrite = mRead = 0;
}

END_AK47_NAMESPACE
