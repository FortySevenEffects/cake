#pragma once

#include "cake.h"
#include "cake_Types.h"

BEGIN_CAKE_NAMESPACE

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

END_CAKE_NAMESPACE

#include "cake_RingBuffer.hpp"
