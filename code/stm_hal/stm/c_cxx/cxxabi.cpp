/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#include <functional>

/**
 * @brief Called by std::function in case operator() is called and no function is defined.
 */
void std::__throw_bad_function_call() {
    __builtin_trap();
}

/**
 * @brief used by the compiler to register destructors for global objects
 *
 * Not implemented because it is irrelevant for us
 */
extern "C" void __aeabi_atexit() { // NOLINT(bugprone-reserved-identifier, readability-identifier-naming)
}

void operator delete([[maybe_unused]] void* ptr) {}
void operator delete([[maybe_unused]] void* ptr, [[maybe_unused]] unsigned int size) {}

extern "C" void __cxa_pure_virtual() { // NOLINT(bugprone-reserved-identifier, readability-identifier-naming)
    __builtin_trap();
}
