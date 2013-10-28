/*!
 *  \file       ak47_Debug.hpp
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

BEGIN_AK47_NAMESPACE

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

inline void Debug::printNumber(unsigned long inNum)
{
    char buf[8 * sizeof(long) + 1]; // Assumes 8-bit chars plus zero byte.
    char *str = &buf[sizeof(buf) - 1];
    *str = 0;

    do
    {
        const unsigned long digit = inNum;
        inNum /= 10;
        const char c = digit - 10 * inNum;
        *--str = c < 10 ? c + '0' : c + 'a' - 10;
    }
    while(inNum);

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

END_AK47_NAMESPACE
