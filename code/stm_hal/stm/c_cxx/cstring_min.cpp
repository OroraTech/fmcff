/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

/**
 * @file cstring_min.cpp
 *
 * Provides a simple implementation of the cstring methods that may be automatically be inserted by the compiler.
 * All methods are compiled with the weak attribute so that they may be linked twice into an executable(once with lto and once without).
 */

#include <cstddef>
#include <cstdint>
#include <span>

extern "C" [[gnu::used]] void* memset(void* ptr, int set, size_t size) {
    auto* arr = static_cast<unsigned char*>(ptr);
    for (size_t i = 0; i < size; i++) {
        arr[i] = (unsigned char)set; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    }
    return ptr;
}

extern "C" [[gnu::used]] void* memcpy(void* dst, const void* src, size_t size) {
    auto* arr_dst = static_cast<unsigned char*>(dst);
    const auto* arr_src = static_cast<const unsigned char*>(src);
    for (size_t i = 0; i < size; i++) {
        arr_dst[i] = arr_src[i]; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    }
    return dst;
}

extern "C" [[gnu::used]] void* memmove(void* dst, const void* src, size_t size) {
    auto* arr_dst = static_cast<unsigned char*>(dst);
    const auto* arr_src = static_cast<const unsigned char*>(src);
    if (src > dst) {
        for (size_t i = 0; i < size; i++) {
            arr_dst[i] = arr_src[i]; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        }
    } else {
        for (size_t i = size; i > 0; i--) {
            arr_dst[i - 1] = arr_src[i - 1]; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        }
    }
    return dst;
}

extern "C" [[gnu::used]] int memcmp(const void* ptr1, const void* ptr2, size_t size) {
    const auto* arr1 = static_cast<const unsigned char*>(ptr1);
    const auto* arr2 = static_cast<const unsigned char*>(ptr2);
    for (size_t i = 0; i < size; i++) {
        if (arr1[i] != arr2[i]) {               // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
            return (int)arr1[i] - (int)arr2[i]; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        }
    }
    return 0;
}

extern "C" char* strchr(const char* s, int c) {
    while (*s != '\0') {
        if (*s == c) {
            return const_cast<char*>(s); // NOLINT(cppcoreguidelines-pro-type-const-cast) C-style function for clarity
        }
        ++s; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic) C-style function for clarity
    }
    return NULL; // NOLINT(modernize-use-nullptr) since it is an extern C function
}

extern "C" [[gnu::used]] void* memchr(const void* s, int value, size_t num) {
    std::span chars { static_cast<const char*>(s), num };
    for (const char& c : chars) {
        if (c == char(value)) {
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast) The C standard makes me do it :(
            return const_cast<void*>(static_cast<const void*>(&c));
        }
    }
    return nullptr;
}

extern "C" int strcmp(const char* s1, const char* s2) {
    while ((*s1 != '\0') && (*s2 != '\0')) {
        int c = (*(s1++)) - *(s2++); // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic) C-style function for clarity
        if (c != 0) {
            return c;
        }
    }
    return *s1 - *s2;
}

extern "C" size_t strlen(const char* s) {
    const char* ss = s;
    while (*ss != '\0') {
        ++ss; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic) C-style function for clarity
    }
    return ss - s;
}

extern "C" int strncmp(const char* str1, const char* str2, size_t num) {
    while (--num > 0) {
        unsigned char c1 = (unsigned char)*(str1++); // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic, modernize-use-auto) C-style function for clarity
        unsigned char c2 = (unsigned char)*(str2++); // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic, modernize-use-auto) C-style function for clarity
        if (c1 != c2) {
            return c1 - c2;
        }
        if (c1 == '\0') {
            return 0;
        }
    }
    return 0;
}
