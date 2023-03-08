# Copyright 2023 OroraTech GmbH
# Licensed under the terms and conditions of the Apache 2.0 license.
#

add_library(unix_shim STATIC)

# Keeping the stm/ prefix here to keep maximum compat with upstream stm_hal
target_sources(unix_shim PRIVATE
    interrupt_timer.cpp
    cycle_count.cpp
    clock.cpp
    )

# The shim doesn't contain any headers currently, reusing the ones from stm_hal
target_include_directories(unix_shim PUBLIC ${PROJECT_SOURCE_DIR}/stm_hal)
