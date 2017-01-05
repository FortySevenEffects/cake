#pragma once

#include "cake.h"
#include "cake_Types.h"
#include <avr/io.h>

BEGIN_CAKE_NAMESPACE

inline uint16 getFreeMemory();
inline uint16 getHeapSize();
inline uint16 getStackSize();

inline void paintStack();
inline uint16 getMaxStackUsage();

END_CAKE_NAMESPACE

// -----------------------------------------------------------------------------

#ifndef CAKE_DYNAMIC_MEMORY
#   define CAKE_DYNAMIC_MEMORY 1
#endif

#if CAKE_DYNAMIC_MEMORY && defined(__cplusplus)

#include <stdlib.h>
inline void* operator new(size_t);
inline void* operator new[](size_t);
inline void* operator new(size_t size_,void *ptr_);

inline void operator delete(void*);
inline void operator delete[](void*);

#endif

#include "cake_Memory.hpp"
