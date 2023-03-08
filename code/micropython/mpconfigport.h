/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#include <alloca.h>
#include <stdint.h>

// Use the minimal starting configuration (disables all optional features).
#define MICROPY_CONFIG_ROM_LEVEL (MICROPY_CONFIG_ROM_LEVEL_MINIMUM)
#define MP_STATE_PORT MP_STATE_VM

// Compiler configuration
#define MICROPY_ENABLE_COMPILER (1)
// Toggle GC as needed - alternatively will use custom heap
#define MICROPY_ENABLE_GC (1)
#define MICROPY_GC_ALLOC_THRESHOLD (1)

// Python error features
#define MICROPY_ERROR_REPORTING (MICROPY_ERROR_REPORTING_NONE)
#define MICROPY_ENABLE_SOURCE_LINE (1)

// REPL features
#define MICROPY_HELPER_REPL (1)
#define MICROPY_REPL_AUTO_INDENT (1)
#define MICROPY_PY_SYS (1)
#define MICROPY_PY_SYS_PS1_PS2 \
    (1) // used to define a custom prompt - supply function
        // mp_repl_get_psx(MP_SYS_MUTABLE_PS1), see repl.h
#define MICROPY_PY_SYS_ATTR_DELEGATION (1)
#define MICROPY_PORT_ROOT_POINTERS const char* readline_hist[8];

#ifndef __unix__
// Type definitions for the specific machine
typedef int mp_int_t;       // must be pointer size
typedef unsigned mp_uint_t; // must be pointer size
typedef long mp_off_t;

// Name board and MCU
#define MICROPY_HW_BOARD_NAME "NUCLEO_L496ZG"
#define MICROPY_HW_MCU_NAME "NUCLEO_L496ZG"

#else

#if !(defined(MICROPY_GCREGS_SETJMP) || defined(__x86_64__) || defined(__i386__) || defined(__thumb2__) || defined(__thumb__) || defined(__arm__))
// Fall back to setjmp() implementation for discovery of GC pointers in registers.
#define MICROPY_GCREGS_SETJMP (1)
#endif

#define MICROPY_NLR_SETJMP (1)
#include <unistd.h>

// assume that if we already defined the obj repr then we also defined types
#ifndef MICROPY_OBJ_REPR
#ifdef __LP64__
typedef long mp_int_t;           // must be pointer size
typedef unsigned long mp_uint_t; // must be pointer size
#else
// These are definitions for machines where sizeof(int) == sizeof(void*),
// regardless of actual size.
typedef int mp_int_t;           // must be pointer size
typedef unsigned int mp_uint_t; // must be pointer size
#endif
#endif

// Name board and MCU
#define MICROPY_HW_BOARD_NAME "Linux"
#define MICROPY_HW_MCU_NAME "x86_64"

#endif

// Cannot include <sys/types.h>, as it may lead to symbol name clashes
#if _FILE_OFFSET_BITS == 64 && !defined(__LP64__)
typedef long long mp_off_t;
#else
typedef long mp_off_t;
#endif

// Choose implementation of long types
#define MICROPY_FLOAT_IMPL MICROPY_FLOAT_IMPL_FLOAT
#define MICROPY_LONGINT_IMPL MICROPY_LONGINT_IMPL_MPZ

// Necessary for upywrap
#define MICROPY_MODULE_BUILTIN_INIT (1)

// MicroPython GC module
#define MICROPY_PY_GC (1)
