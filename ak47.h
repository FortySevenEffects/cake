/*!
 *  \file       ak47.h
 *  \author     Francois Best
 *  \date       22/10/2012
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

#include "ak47_Namespace.h"

// -----------------------------------------------------------------------------

#if defined(DEBUG) || defined(_DEBUG)
#   define AVR_DEBUG   1
#elif defined(NDEBUG) || defined(_NDEBUG)
#   define AVR_RELEASE 1
#else
//#   error No Debug/Release flags provided.
#endif

// -----------------------------------------------------------------------------

#include <ak47_Assert.h>

BEGIN_AK47_NAMESPACE

template<bool Predicate> struct StaticAssert;
template<> struct StaticAssert<true> { static void ok() {} };

END_AK47_NAMESPACE

#define AVR_ASSERT(Predicate, ...)      avr_assert(Predicate)
#define AVR_ASSERT_FALSE(...)           avr_assert(false)
#define AVR_STATIC_ASSERT(Predicate)    ak47::StaticAssert<Predicate>::ok()

#define AVR_IMPLEMENT_ME(...)                                                   \
{                                                                               \
    static const bool ImplementMe = false;                                      \
    assert(ImplementMe);                                                        \
}

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

