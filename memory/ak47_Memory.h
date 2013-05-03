/*!
 *  \file       ak47_Memory.h
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

#include "ak47.h"
#include "ak47_Types.h"
#include <avr/io.h>

BEGIN_AK47_NAMESPACE

inline uint16 getFreeMemory();
inline uint16 getHeapSize();
inline uint16 getStackSize();

inline void paintStack();
inline uint16 getMaxStackUsage();

END_AK47_NAMESPACE

// -----------------------------------------------------------------------------

#ifndef AK47_DYNAMIC_MEMORY
#   define AK47_DYNAMIC_MEMORY 1
#endif

#if AK47_DYNAMIC_MEMORY && defined(__cplusplus)

#include <stdlib.h>
inline void* operator new(size_t);
inline void* operator new[](size_t);
inline void* operator new(size_t size_,void *ptr_);

inline void operator delete(void*);
inline void operator delete[](void*);

#endif

#include "ak47_Memory.hpp"
