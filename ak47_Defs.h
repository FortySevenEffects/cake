/*!
 *  \file       ak47_Defs.h
 *  \author     Francois Best
 *  \date       13/11/2012
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

#include "ak47_Namespace.h"

// -----------------------------------------------------------------------------

#if !defined(__AVR__)
#   error This library is supposed to be built for AVR targets.
#endif

// -----------------------------------------------------------------------------

#if __cplusplus > 199711L
#   define AVR_CPP11    // C++11 available
#endif

// -----------------------------------------------------------------------------

#if defined(DEBUG) || defined(_DEBUG)
#   define AVR_DEBUG   1
#elif defined(NDEBUG) || defined(_NDEBUG)
#   define AVR_RELEASE 1
#else
//#   error No Debug/Release flags provided.
#endif

// -----------------------------------------------------------------------------

#define AVR_BEGIN_EXTERN_C              extern "C" {
#define AVR_END_EXTERN_C                }

#define AVR_BEGIN_UNNAMED_NAMESPACE     namespace {
#define AVR_END_UNNAMED_NAMESPACE       }

// -----------------------------------------------------------------------------

#define AVR_NON_COPYABLE(Type)                                                  \
    private:                                                                    \
        Type (const Type&);                                                     \
        Type& operator= (const Type&);

// -----------------------------------------------------------------------------

#define AVR_TYPEDEF_FUNCTOR(ReturnType, Name, Arg)                              \
    typedef ReturnType (*Name) (Arg);

