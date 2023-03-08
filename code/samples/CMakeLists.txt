function(add_sample TARGET_NAME)
    add_executable(${TARGET_NAME} ${TARGET_NAME}.cpp)
    target_link_libraries(${TARGET_NAME} PRIVATE fmcff)

    #
    # Create a .bin file for flashing the STM targets
    #
    if ("${CMAKE_SYSTEM_NAME}" STREQUAL "Generic")  
        target_link_options(${TARGET_NAME} PRIVATE -Wno-maybe-uninitialized)
        add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
            COMMAND arm-none-eabi-objcopy -O binary $<TARGET_FILE:${TARGET_NAME}> $<TARGET_FILE_DIR:${TARGET_NAME}>/${TARGET_NAME}.bin
            COMMAND arm-none-eabi-size $<TARGET_FILE:${TARGET_NAME}>
            COMMAND mv $<TARGET_FILE:${TARGET_NAME}> $<TARGET_FILE:${TARGET_NAME}>.elf
            COMMAND echo -n "bin-size: "
            COMMAND wc -c $<TARGET_FILE_DIR:${TARGET_NAME}>/${TARGET_NAME}.bin
            COMMENT "Creating flashable ${TARGET_NAME}.bin"
        )
    endif()
endfunction()


#
# Begin Samples here:
#
add_sample(health_monitor_benchmark)
add_sample(health_monitor_recovery_timer)
add_sample(health_monitor_recovery)
add_sample(health_monitor_value_ranges)
add_sample(modules)
add_sample(simple_failure_no_recovery)
add_sample(fmcff_full)
