/*!
 *  \file       ak47_Memory.hpp
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

BEGIN_AK47_NAMESPACE

END_AK47_NAMESPACE

// -----------------------------------------------------------------------------

#if AK47_DYNAMIC_MEMORY && defined(__cplusplus)

AVR_BEGIN_EXTERN_C

void* operator new(size_t size)
{
    return malloc(size);
}

void operator delete(void* ptr) 
{
    if (ptr != 0)
    {
        free(ptr);
    }
}

void* operator new[](size_t size)
{
    return malloc(size);
}

void operator delete[](void* ptr)
{
    if (ptr != 0)
    {
        free(ptr);
    }
}

AVR_END_EXTERN_C

#endif // AK47_DYNAMIC_MEMORY
