# © Copyright 2023 OroraTech GmbH
# Licensed under the terms and conditions of the Apache 2.0 license.
#

list(APPEND MICROPY_SOURCE_USERMOD ${CMAKE_CURRENT_LIST_DIR}/adcsmodule.c)

# Create an INTERFACE library for our CPP module.
add_library(usermod_adcsmodule INTERFACE)

# Add our source files to the library.
target_sources(usermod_adcsmodule INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/adcsmodule.c
    ${CMAKE_CURRENT_LIST_DIR}/adcsmodule.cpp
)

# Add the current directory as an include directory.
target_include_directories(usermod_adcsmodule INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/
    ${MICROPY_DIR}/
)

# Link our INTERFACE library to the usermod target.
target_link_libraries(usermod INTERFACE usermod_adcsmodule)
