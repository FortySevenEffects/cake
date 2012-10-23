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

template <uint16 BufferSize, typename Type>
RingBuffer<BufferSize, Type>::RingBuffer()
    : mRead(mData)
    , mWrite(mData)
{
}

template <uint16 BufferSize, typename Type>
RingBuffer<BufferSize, Type>::~RingBuffer()
{
}

template <uint16 BufferSize, typename Type>
void RingBuffer<BufferSize, Type>::init()
{
    mRead  = mData;
    mWrite = mData;
}

// -----------------------------------------------------------------------------

template <uint16 BufferSize, typename Type>
uint16 RingBuffer<BufferSize, Type>::available() const
{
    if (mRead < mWrite)
        return mWrite - mRead;
    else if (mRead == mWrite)
        return 0;
    else 
        return (BufferSize - (mRead - mWrite));
}

// -----------------------------------------------------------------------------

template <uint16 BufferSize, typename Type>
void RingBuffer<BufferSize, Type>::push(Type inData)
{
    *mWrite++ = inData;
    if (mWrite >= mData + BufferSize)
        mWrite = mData;
    
    // Overflow -> increment buffer size.
    AVR_ASSERT(mWrite != mRead);
}

template <uint16 BufferSize, typename Type>
Type RingBuffer<BufferSize, Type>::pop()
{
    // You should always check if there is available data
    // before calling pop..
    AVR_ASSERT(available() > 0); 
    
    const DataType data = *mRead++;
    
    if (mRead >= mData + BufferSize)
        mRead = mData;

    return data;
}

template <uint16 BufferSize, typename Type>
void RingBuffer<BufferSize, Type>::flush()
{
    mWrite = mRead;
}

END_AK47_NAMESPACE
