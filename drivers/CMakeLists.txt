#cmake_minimum_required(VERSION 3.12)
#
#project(ppcm-drivers)
#
#file(GLOB SRC_FILES
#    CMSIS/st/src/*.c
#    STM32F1xx/src/*.c)
#
#set(INCLUDE_DIRS
#    CMSIS/include
#    CMSIS/st/include
#    STM32F1xx/include)
#
#add_library(ppcm-drivers STATIC ${SRC_FILES})
#
#target_include_directories(ppcm-drivers PUBLIC ${INCLUDE_DIRS})
#
#target_compile_definitions(ppcm-drivers PUBLIC
#    STM32F103xB
#    USE_FULL_LL_DRIVER)