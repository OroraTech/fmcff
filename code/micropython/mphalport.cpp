/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#include <cstdio>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#pragma GCC diagnostic ignored "-Wcast-qual"
#pragma GCC diagnostic ignored "-Wunused-parameter"

extern "C" {
#include "mphalport.h"
#include "py/runtime.h"
#include "shared/runtime/gchelper.h"
#include "shared/runtime/stdout_helpers.c"
}

#pragma GCC diagnostic pop

#if MICROPY_ENABLE_GC == 1
extern "C" {
#include "py/gc.h"
}
#endif

constexpr size_t MPY_HEAPSIZE = 64000;
char heap[MPY_HEAPSIZE] {};

void gc_init_port(void) {
#if MICROPY_ENABLE_GC == 1
    void* heap_base = heap;
    MP_STATE_THREAD(stack_top) = reinterpret_cast<char*>(&heap_base);
    uintptr_t heap_end = reinterpret_cast<uintptr_t>(heap_base) + MPY_HEAPSIZE;
    gc_init(heap_base, reinterpret_cast<void*>(heap_end));
    MP_STATE_MEM(gc_alloc_threshold) = MPY_HEAPSIZE / (MICROPY_BYTES_PER_GC_BLOCK)-1024;
#endif
}

void gc_collect(void) {
#if MICROPY_ENABLE_GC == 1
    gc_collect_start();
    gc_helper_collect_regs_and_stack();
    gc_collect_end();
#endif
}

extern "C" {
// Called if an exception is raised outside all C exception-catching handlers.
void nlr_jump_fail(void* /*val*/) {
    printf("Uncaught NLR\r\n");
    for (;;) {
    }
}

void mp_hal_stdout_tx_strn(const char* str, size_t len) {
    char buf[10] {};

    // Create a %.<len>s format for making sure to only print len bytes
    buf[0] = '%';
    buf[1] = '.';
    size_t s = snprintf(buf + 2, 7, "%lu", (long unsigned)len);
    buf[2 + s] = 's';

    printf(buf, str);
}
}
