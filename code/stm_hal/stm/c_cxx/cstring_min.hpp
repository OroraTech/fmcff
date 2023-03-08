/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once
#include <cstddef>
#include <cstring>

namespace stm {
[[gnu::nonnull, gnu::returns_nonnull]] void* memcpy(void* dst, const void* src, size_t size) {
    return __builtin_memcpy(dst, src, size);
}
[[gnu::nonnull, gnu::returns_nonnull]] void* memmove(void* dst, const void* src, size_t size) {
    return __builtin_memmove(dst, src, size);
}
[[gnu::nonnull]] int memcmp(const void* ptr1, const void* ptr2, size_t size) {
    return __builtin_memcmp(ptr1, ptr2, size);
}
[[gnu::nonnull, gnu::returns_nonnull]] void* memset(void* ptr, int set, size_t size) {
    return __builtin_memset(ptr, set, size);
}
} // namespace stm
