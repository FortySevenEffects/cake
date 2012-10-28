/*!
 *  \file       ak47_RingBuffer.h
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

#include "ak47.h"
#include "ak47_Types.h"

BEGIN_AK47_NAMESPACE

template <byte BufferSize, typename Type = byte>
class RingBuffer
{
public:
    explicit RingBuffer();
    ~RingBuffer();
    
    inline void init();
    
public:
    inline byte size() const;
    
public:
    inline void push(Type inData);
    inline Type pop();
    inline void flush();
    
protected:
    typedef volatile Type DataType;
    
    DataType mData[BufferSize];
    const DataType* volatile mRead;
    DataType* volatile  mWrite;
    byte mSize;
};

END_AK47_NAMESPACE

#include "ak47_RingBuffer.hpp"
