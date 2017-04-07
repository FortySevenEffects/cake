#pragma once

#include "cake_Namespace.h"

// -----------------------------------------------------------------------------

#if !defined(__AVR__)
#   error This library is supposed to be built for AVR targets.
#endif

// -----------------------------------------------------------------------------

#if defined(DEBUG) || defined(_DEBUG)
#   define AVR_DEBUG   1
#elif defined(NDEBUG) || defined(_NDEBUG)
#   define AVR_RELEASE 1
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

