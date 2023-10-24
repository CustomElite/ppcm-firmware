message("Running arm-toolchain.cmake")
set(CMAKE_SYSTEM_VERSION 1)
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(C_FLAGS "-ffunction-sections -fdata-sections -ffreestanding -fmessage-length=0 -specs=nano.specs -specs=nosys.specs")
set(CPP_FLAGS "-fno-threadsafe-statics -fno-rtti -fno-exceptions -fno-use-cxa-atexit -Wno-volatile")

set(TOOLCHAIN_PREFIX arm-none-eabi)
set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}-gcc ${C_FLAGS})
set(CMAKE_ASM_COMPILER ${CMAKE_C_COMPILER})
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}-g++ ${C_FLAGS} ${CPP_FLAGS})
set(CMAKE_OBJCOPY ${TOOLCHAIN_PREFIX}-objcopy)
set(CMAKE_SIZE ${TOOLCHAIN_PREFIX}-size)

set(CMAKE_EXECUTABLE_SUFFIX_ASM ".elf")
set(CMAKE_EXECUTABLE_SUFFIX_C ".elf")
set(CMAKE_EXECUTABLE_SUFFIX_CXX ".elf")

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
message("arm-none-eabi toolchain is configured")