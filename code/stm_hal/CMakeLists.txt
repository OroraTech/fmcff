# © Copyright 2023 OroraTech GmbH
# Licensed under the terms and conditions of the Apache 2.0 license.
#

# See supported targets in targets/targets.cmake
set(TARGET_BOARD NUCLEO_L496ZG CACHE STRING "Board for which to compile. Must be present in targets.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/targets/targets.cmake")

add_library(stm_hal STATIC
    # cortex-m
    stm/cortex_m/cm4_fpu.cpp

    # startup
    stm/startup/irq_table.cpp
    stm/startup/startup.cpp

    # clock setup
    stm/periphs/rcc/clock_manager.cpp
    stm/periphs/rcc/rcc_periph.cpp

    # uart
    stm/periphs/uart/uart.cpp

    # gpio
    stm/periphs/gpio/pin_config.cpp
    stm/periphs/gpio/gpio.cpp

    # can
    stm/periphs/can/can.cpp
    stm/periphs/can/can_irq_handlers.cpp

    # i2c
    stm/periphs/i2c/i2c_master.cpp

    # ina209
    stm/drivers/ina/ina209.cpp
    stm/drivers/ina/ina226.cpp

    # rng
    stm/periphs/rng/rng.cpp

    # support & convenience
    stm/support/clock.cpp
    stm/support/interrupt_timer.cpp
    stm/support/cycle_count.cpp
    stm/support/stdout.cpp
    stm/support/timer.cpp

    # C++ language support
    stm/c_cxx/cxxabi.cpp
    )

add_library(stm_startup STATIC 
    stm/startup/weak_irq_handlers.cpp
)

target_include_directories(stm_startup PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_include_directories(stm_startup PUBLIC ${CMAKE_CURRENT_LIST_DIR}/targets/${TARGET_BOARD}/)

target_include_directories(stm_hal PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_include_directories(stm_hal PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_include_directories(stm_hal PUBLIC ${CMAKE_CURRENT_LIST_DIR}/targets/${TARGET_BOARD}/)

# Setup required for printf library
set(BUILD_STATIC_LIBRARY ON)
set(CMAKE_INSTALL_LIBDIR ${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/printf/" "${CMAKE_CURRENT_BINARY_DIR}/printf")
target_link_libraries(stm_hal PUBLIC printf stm_startup)

#
# Link options when building baremetal:
#
if("${CMAKE_SYSTEM_NAME}" STREQUAL "Generic")
    set(LINKER_SCRIPTS
        stm/linker_scripts/${MCU_NAME}.ld
        stm/linker_scripts/main.ld
        stm/linker_scripts/peripheral_symbols_${MCU_FAMILY}.ld
    )

    foreach(linker_script ${LINKER_SCRIPTS})
        set(linker_script ${CMAKE_CURRENT_LIST_DIR}/${linker_script})

        SET_SOURCE_FILES_PROPERTIES(
            ${CMAKE_CURRENT_LIST_DIR}/stm/startup/startup.cpp PROPERTIES OBJECT_DEPENDS
            ${linker_script}
        )
        target_link_options(stm_hal INTERFACE -T${linker_script})
    endforeach()
endif()
