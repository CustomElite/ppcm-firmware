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
set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/mcu/linker_stm32f1c8tx.ld)
# ST startup script
set(STARTUP_SCRIPT ${CMAKE_SOURCE_DIR}/mcu/startup_stm32f103xb.s)

add_subdirectory(libs/etl)
#add_subdirectory(drivers)

set(PROJECT_INCLUDE_DIR
    core/include
    core/general
    core/peripherals
    core/system)

set(DRIVER_INCLUDE_DIR 
    drivers/CMSIS/include
    drivers/CMSIS/st/include
    drivers/${STM32_FAMILY}/include)

set(LIBS_DIR
    libs/printf)

# Source files
file(GLOB PROJECT_SRC CONFIGURE_DEPENDS
    core/src/*.c
    core/src/*.cpp)

file(GLOB DRIVER_SRC
    drivers/CMSIS/st/src/*.c
    drivers/${STM32_FAMILY}/src/*.c)

file(GLOB LIBS_SRC
    ${LIBS_DIR}/*.c)

# CPU Flags
set(CPU_FLAGS -march=armv7-m -mcpu=cortex-m3 -mthumb -mfloat-abi=soft) #-mlittle-endian

# Warning flags
set(WFLAGS
    -Wall
    -Wextra
    -Wshadow)
    #-Wunused-variable | for my code only

add_executable(${CMAKE_PROJECT_NAME}
    ${PROJECT_SRC}
    ${DRIVER_SRC}
    ${LIBS_SRC}
    ${STARTUP_SCRIPT})

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE 
    etl)

# Include directories
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    ${PROJECT_INCLUDE_DIR}
    ${DRIVER_INCLUDE_DIR}
    ${LIBS_DIR})

# Compiled definitions
target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC
    ${STM32_MCU}
    USE_FULL_LL_DRIVER
    VDD_VALUE=3300
    HSI_VALUE=8000000
    HSE_VALUE=8000000
    HSE_STARTUP_TIMEOUT=100
    LSI_VALUE=40000
    LSE_VALUE=32768
    LSE_STARTUP_TIMEOUT=5000
    PREFETCH_ENABLE=1)

# Compiler options
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE
    ${CPU_FLAGS}
    ${WFLAGS}
    -flto
    $<$<COMPILE_LANGUAGE:CXX>:
        -Wno-register
        -ftemplate-backtrace-limit=0>
    $<$<CONFIG:Debug>: -g -O0 -g3 -ggdb>
    $<$<CONFIG:Release>: -Os>
    $<$<CONFIG:RelWithDebInfo>: -g -O2 -g2 -ggdb>)

# Linker options
target_link_options(${CMAKE_PROJECT_NAME} PRIVATE
    -T${LINKER_SCRIPT}
    ${CPU_FLAGS}
    -lm
    -Wl,-Map=${CMAKE_PROJECT_NAME}.map,--cref
    -Wl,--print-memory-usage)

add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${CMAKE_PROJECT_NAME}>)

add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${CMAKE_PROJECT_NAME}>
    ${CMAKE_PROJECT_NAME}.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${CMAKE_PROJECT_NAME}>
    ${CMAKE_PROJECT_NAME}.bin)

add_custom_target(FLASH DEPENDS ${CMAKE_PROJECT_NAME})
add_custom_command(TARGET FLASH USES_TERMINAL
    COMMAND openocd -f interface/stlink.cfg -f target/stm32f1x.cfg -c "program $<TARGET_FILE:${CMAKE_PROJECT_NAME}> verify reset exit")