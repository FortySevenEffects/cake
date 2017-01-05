/*!
 *  \file       cake_Debug.hpp
 *  \author     Francois Best
 *  \date       22/10/2012
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

BEGIN_CAKE_NAMESPACE

inline void Debug::print(char inChar)
{
    mPrintCallback(inChar);
}

inline void Debug::print(const char* inString)
{
    if (inString != 0 && mPrintCallback != 0)
    {
        do
        {
            mPrintCallback(*inString);
        }
        while (*inString++);
    }
}

inline void Debug::printNumber(long inNum)
{
    const bool negative = inNum < 0;
    unsigned long num = negative ? -1 * inNum : inNum;
    char buf[8 * sizeof(long) + 1]; // Assumes 8-bit chars plus zero byte.
    char *str = &buf[sizeof(buf) - 1];
    *str = 0;

    do
    {
        const long digit = num;
        num /= 10;
        const char c = digit - 10 * num;
        *--str = c < 10 ? c + '0' : c + 'a' - 10;
    }
    while(num);

    if (negative)
        print('-');
    print(str);
}

inline void Debug::log(const char* inString)
{
    print(inString);
    print('\n');
    print('\r');
}

// -----------------------------------------------------------------------------

void Debug::setPrintCallback(PrintCallback inCallback)
{
    mPrintCallback = inCallback;
}

END_CAKE_NAMESPACE
