/*!
 *  \file       cake_Assert.h
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

#include "cake_Namespace.h"
#include "cake_Debug.h"

#define AVR__STRINGIFY(s)       #s
#define AVR_STRINGIFY(s)        AVR__STRINGIFY(s)

#ifdef AVR_BREAK_ON_ASSERT
#   include <avr/interrupt.h>
#   define avr_assert_break     { cli(); while(1); }
#else
#   define avr_assert_break     ((void)0)
#endif

#define avr_assertion_str       "Assert:" __FILE__ ":" AVR_STRINGIFY(__LINE__)
#define avr_log_assertion       CAKE_NAMESPACE::Debug::log(avr_assertion_str)

#ifdef NDEBUG
#   define avr_assert(...)      ((void)0)
#else
#   define avr_assert(condition)                                                \
{                                                                               \
    if (!(condition))                                                           \
    {                                                                           \
        avr_log_assertion;                                                      \
        avr_assert_break;                                                       \
    }                                                                           \
}
#endif

// -----------------------------------------------------------------------------

BEGIN_CAKE_NAMESPACE

template<bool Predicate> struct StaticAssert;
template<> struct StaticAssert<true> { static void ok() {} };

END_CAKE_NAMESPACE

#define AVR_ASSERT(Predicate, ...)      avr_assert(Predicate)
#define AVR_ASSERT_FALSE(...)           avr_assert(false)
#define AVR_STATIC_ASSERT(Predicate)    cake::StaticAssert<Predicate>::ok()

#define AVR_IMPLEMENT_ME(...)                                                   \
{                                                                               \
    static const bool ImplementMe = false;                                      \
    assert(ImplementMe);                                                        \
}
