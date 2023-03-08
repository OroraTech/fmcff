# Copyright 2023 OroraTech GmbH
# Licensed under the terms and conditions of the Apache 2.0 license.
#

cmake_minimum_required(VERSION 3.20)

option(FMCFF_UNIX "Build for unix using a shim instead of targeting the STM32" OFF)

if (NOT FMCFF_UNIX)
    # Defines the compiler and flags to use for STM32 builds
    set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_LIST_DIR}/stm_hal/cross.cmake CACHE FILEPATH "Toolchain file for cross compilation. Empty string results in native build.")
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(FMCFF VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ggdb")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb -Wall -Wextra -Wpedantic -Wnull-dereference -Wconversion -Wcast-qual -Werror -Wno-predefined-identifier-outside-function")
set(CMAKE_LINKER_EXE_FLAGS "${CMAKE_CXX_FLAGS} -ggdb -Wall -Wextra -Wpedantic -Wnull-dereference -Wconversion -Wcast-qual -Werror -Wno-predefined-identifier-outside-function")

add_subdirectory(micropython)

add_library(fmcff STATIC)
target_link_libraries(fmcff PUBLIC stm_hal)
target_sources(fmcff PRIVATE src/chunk_table.cpp src/context_switch.cpp)
target_include_directories(fmcff PUBLIC src)
target_link_libraries(fmcff INTERFACE micropython)

# Using `cmake -S. -Bbuild -DCMAKE_TOOLCHAIN_FILE=` the linux based build may be chosen
if (FMCFF_UNIX)
    message(STATUS "Building for Unix")
    add_subdirectory(unix_shim)
    target_link_libraries(fmcff INTERFACE unix_shim)
else ()
    message(STATUS "Building for STM32")
    add_subdirectory(stm_hal)
    target_link_libraries(fmcff INTERFACE stm_hal)
endif()

add_subdirectory(samples)

