/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once

namespace ot {
enum class AbortType {
    STD_ABORT,
    BUILTIN_TRAP,
    EXCEPTION,
    CALLBACK
};

constexpr AbortType ABORT_TYPE = []() {
    AbortType abort_type = AbortType::BUILTIN_TRAP;
#if (defined(__unix__) && !defined(OT_ABORT_USE_EXCEPTION) && !defined(OT_ABORT_USE_CALLBACK)) || defined(OT_ABORT_USE_STD_ABORT)
    abort_type = AbortType::STD_ABORT;
#elif defined(OT_ABORT_USE_EXCEPTION)
    abort_type = AbortType::EXCEPTION;
#elif defined(OT_ABORT_USE_CALLBACK)
    abort_type = AbortType::CALLBACK;
#endif
    return abort_type;
}();

template <AbortType TYPE>
[[noreturn]] void abort_with();

template <>
[[noreturn]] inline void abort_with<AbortType::BUILTIN_TRAP>() {
    __builtin_trap();
}
} // namespace ot

#ifdef __unix__
#include <cstdlib>
namespace ot {
template <>
[[noreturn]] inline void abort_with<AbortType::STD_ABORT>() {
    std::abort();
}
} // namespace ot
#endif

#ifdef OT_ABORT_USE_EXCEPTION
#include <stdexcept>
namespace ot {
template <>
[[noreturn]] inline void abort_with<AbortType::EXCEPTION>() {
    throw std::runtime_error("Abort was called");
}
} // namespace ot
#endif

#ifdef OT_ABORT_USE_CALLBACK
#include <functional>
namespace ot {
std::function<void()> g_abort_callback = []() {}; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables) should only be used for testing/debugging
template <>
[[noreturn]] inline void abort_with<AbortType::CALLBACK>() {
    g_abort_callback();
    __builtin_unreachable();
}
} // namespace ot
#endif

namespace ot {
[[noreturn]] inline void abort() { abort_with<ABORT_TYPE>(); }
} // namespace ot
