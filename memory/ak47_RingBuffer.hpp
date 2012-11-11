/*!
 *  \file       ak47_RingBuffer.hpp
 *  \author     Francois Best
 *  \date       23/10/2012
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

template <byte BufferSize, typename Type>
RingBuffer<BufferSize, Type>::RingBuffer()
    : mRead(0)
    , mWrite(0)
{
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
void RingBuffer<BufferSize, Type>::flush()
{
    mWrite = mRead = 0;
}

END_AK47_NAMESPACE
