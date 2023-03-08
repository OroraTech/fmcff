# Copyright 2023 OroraTech GmbH
# Licensed under the terms and conditions of the Apache 2.0 license.
#

#list with all possible targets. Boards must be in even indexes and the corresponding MCUs in odd indices.
set(POSSIBLE_TARGETS
    NUCLEO_L432KC STM32L432KC
    NUCLEO_L496ZG STM32L496ZG
)

list(FIND POSSIBLE_TARGETS ${TARGET_BOARD} TARGET_INDEX)
math(EXPR LIST_INDEX_MOD2 "${TARGET_INDEX}%2")
if(${LIST_INDEX_MOD2} EQUAL 0)
    math(EXPR MCU_INDEX "${TARGET_INDEX}+1")
    list(GET POSSIBLE_TARGETS ${MCU_INDEX} MCU_NAME)
else()
    message(FATAL_ERROR "invalid TARGET_BOARD: ${TARGET_BOARD}")
endif()

string(SUBSTRING "${MCU_NAME}" 5 2 MCU_FAMILY)
message(STATUS "Compiling for board ${TARGET_BOARD} with MCU ${MCU_NAME} from family ${MCU_FAMILY}")
