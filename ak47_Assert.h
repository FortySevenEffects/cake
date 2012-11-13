/*!
 *  \file       ak47_Assert.h
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
#include "ak47_Debug.h"

#define AVR__STRINGIFY(s)       #s
#define AVR_STRINGIFY(s)        AVR__STRINGIFY(s)

#ifdef AVR_BREAK_ON_ASSERT
#   include <avr/interrupt.h>
#   define avr_assert_break     { cli(); while(1); }
#else
#   define avr_assert_break     ((void)0)
#endif

#define avr_assertion_str       "Assert:"__FILE__":"AVR_STRINGIFY(__LINE__)
#define avr_log_assertion       AK47_NAMESPACE::Debug::print(avr_assertion_str)

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
