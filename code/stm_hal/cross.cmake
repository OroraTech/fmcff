# Copyright 2023 OroraTech GmbH
# Licensed under the terms and conditions of the Apache 2.0 license.
#

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_AR arm-none-eabi-gcc-ar)
set(CMAKE_RANLIB arm-none-eabi-gcc-ranlib)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE NEVER)

SET(CMAKE_C_FLAGS "-fno-exceptions -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Os -flto -ffreestanding -ggdb -ffunction-sections -fdata-sections" CACHE STRING "" FORCE)
SET(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -fno-rtti  -fno-threadsafe-statics" CACHE STRING "" FORCE)
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_C_FLAGS} -nostartfiles -nodefaultlibs -nostdlib -Xlinker --gc-sections -Xlinker --emit-relocs -fno-unwind-tables -fno-asynchronous-unwind-tables -lgcc -lm -ggdb" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS_RELEASE "-Os")
set(CMAKE_C_FLAGS_RELEASE "-Os")
