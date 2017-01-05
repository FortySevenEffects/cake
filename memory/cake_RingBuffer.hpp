#pragma once

BEGIN_CAKE_NAMESPACE

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

END_CAKE_NAMESPACE
