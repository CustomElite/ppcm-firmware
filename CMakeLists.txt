cmake_minimum_required(VERSION 3.19)

project(ppcm-firmware
    VERSION 0.1.0
    LANGUAGES C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

set(STM32_MCU STM32F103xB)
set(STM32_FAMILY STM32F1xx)

# Linker script
set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/scripts/linker_stm32f1c8tx.ld)
# ST startup script
set(STARTUP_SCRIPT ${CMAKE_SOURCE_DIR}/scripts/startup_stm32f103xb.s)

add_subdirectory(libs/etl)

set(PROJECT_INCLUDE_DIR
    core/include
    core/peripherals)

set(DRIVER_INCLUDE_DIR 
    drivers/CMSIS/include
    drivers/CMSIS/st/include
    drivers/${STM32_FAMILY}/include)

set(LIBS_DIR
    libs/printf)

# Source files
file(GLOB_RECURSE PROJECT_SRC CONFIGURE_DEPENDS
    core/src/*.c
    core/src/*.cpp)

file(GLOB_RECURSE DRIVER_SRC
    drivers/*.c)

file(GLOB_RECURSE LIBS_SRC
    ${LIBS_DIR}/*.c)

# CPU Flags
set(CPU_FLAGS -march=armv7-m -mcpu=cortex-m3 -mthumb) #-mlittle-endian

# Warning flags
set(WFLAGS
    -Wall
    -Wextra
    -Wunused-variable
    -Wshadow)

add_executable(${PROJECT_NAME}
    ${PROJECT_SRC}
    ${DRIVER_SRC}
    ${LIBS_SRC}
    ${STARTUP_SCRIPT})

target_link_libraries(${PROJECT_NAME} PRIVATE etl::etl)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${PROJECT_INCLUDE_DIR}
    ${DRIVER_INCLUDE_DIR}
    ${LIBS_DIR})

# Compiled definitions
target_compile_definitions(${PROJECT_NAME} PRIVATE
    ${STM32_MCU}
    USE_FULL_LL_DRIVER
    HSE_STARTUP_TIMEOUT=100
    VDD_VALUE=3300)

# Compiler options
target_compile_options(${PROJECT_NAME} PRIVATE
    ${CPU_FLAGS}
    ${WFLAGS}
    $<$<COMPILE_LANGUAGE:CXX>:
        -Wno-register
        -ftemplate-backtrace-limit=0>
    $<$<CONFIG:Debug>: -g -Og -g3 -ggdb>
    $<$<CONFIG:Release>: -Os -g0>)

# Linker options
target_link_options(${PROJECT_NAME} PRIVATE
    -T${LINKER_SCRIPT}
    ${CPU_FLAGS}
    -lc
    -lm
    -Wl,--gc-sections
    -Wl,-Map=${PROJECT_NAME}.map,--cref
    -Wl,--print-memory-usage)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${PROJECT_NAME}>)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${PROJECT_NAME}>
    ${PROJECT_NAME}.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${PROJECT_NAME}>
    ${PROJECT_NAME}.bin)

add_custom_target(FLASH DEPENDS ${PROJECT_NAME})
add_custom_command(TARGET FLASH USES_TERMINAL
    COMMAND openocd -f interface/stlink.cfg -f target/stm32f1x.cfg -c "program $<TARGET_FILE:${PROJECT_NAME}> verify reset exit")