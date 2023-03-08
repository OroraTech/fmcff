# Copyright 2023 OroraTech GmbH
# Licensed under the terms and conditions of the Apache 2.0 license.
#

add_library(support STATIC timer.cpp cycle_count.cpp)
target_link_libraries(support PUBLIC stm_hal)
