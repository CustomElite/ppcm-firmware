cmake_minimum_required(VERSION 3.12)

project(ppcm-firmware)

set(STM32_MCU STM32F103xB)
set(STM32_FAMILY STM32F1xx)
set(CPU_FLAGS -march=armv7-m -mcpu=cortex-m3 -mthumb) #-mlittle-endian

set(LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/drivers/linker_stm32f1c8tx.ld)
set(STARTUP_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/drivers/startup_stm32f103xb.s)

set(EXECUTABLE ${CMAKE_PROJECT_NAME})
enable_language(C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

set(WFLAGS
    -Wall
    -Wextra
    -Wunused-variable
    -Wshadow)
    #-Wuseless-cast)

set(DRIVER_INCLUDE_DIR 
    drivers/CMSIS/include
    drivers/CMSIS/st/include
    drivers/${STM32_FAMILY}/include)

set(PROJECT_INCLUDE_DIR
    core/include)

file(GLOB_RECURSE DRIVER_SRC
    drivers/CMSIS/st/src/*.c
    drivers/${STM32_FAMILY}/src/*.c)

file(GLOB_RECURSE PROJECT_SRC
    core/src/*.c
    core/src/*.cpp)

add_executable(${EXECUTABLE}
    ${DRIVER_SRC}
    ${PROJECT_SRC}
    ${STARTUP_SCRIPT})

target_compile_definitions(${EXECUTABLE} PRIVATE
    ${STM32_MCU}
    USE_FULL_LL_DRIVER
    HSE_VALUE=8000000
    HSE_STARTUP_TIMEOUT=100
    VDD_VALUE=3300)

# Project Directories
target_include_directories(${EXECUTABLE} PRIVATE
    ${DRIVER_INCLUDE_DIR}
    ${PROJECT_INCLUDE_DIR})

target_compile_options(${EXECUTABLE} PRIVATE
    ${CPU_FLAGS}
    ${WFLAGS}
    $<$<COMPILE_LANGUAGE:CXX>:
        -Wno-register
        -ftemplate-backtrace-limit=0>
    $<$<CONFIG:Debug>: -g -Og -g3 -ggdb>
    $<$<CONFIG:Release>: -Os -g0>)

target_link_options(${EXECUTABLE} PRIVATE
    -T${LINKER_SCRIPT}
    ${CPU_FLAGS}
    -lc
    -lm
    -lnosys
    #-lstdc++
    #-lsupc++
    -Wl,--gc-sections
    -Wl,-Map=${CMAKE_PROJECT_NAME}.map,--cref
    -Wl,--print-memory-usage)

add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
    COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${EXECUTABLE}>)

add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${EXECUTABLE}>
    ${EXECUTABLE}.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${EXECUTABLE}>
    ${EXECUTABLE}.bin)