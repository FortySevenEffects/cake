#pragma once

#include "cake.h"
#include <avr/io.h>

BEGIN_CAKE_NAMESPACE

// -----------------------------------------------------------------------------
// Hardware Abstraction

#ifdef UDR0
#   define UART0
#endif
#ifdef UDR1
#   define UART1
#endif
#ifdef UDR2
#   define UART2
#endif
#ifdef UDR3
#   define UART3
#endif
#if !defined(UART0) && !defined(UART1) && !defined(UART2) && !defined(UART3)
#   define NO_UART
#endif

END_CAKE_NAMESPACE
