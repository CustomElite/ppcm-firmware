message("Running arm-none-eabi-gcc.cmake")

set(CMAKE_SYSTEM_VERSION 1)
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
set(CMAKE_AR arm-none-eabi-gcc-ar)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP arm-none-eabi-objdump)
set(CMAKE_SIZE arm-none-eabi-size)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

set(CMAKE_EXECUTABLE_SUFFIX_ASM ".elf")
set(CMAKE_EXECUTABLE_SUFFIX_C ".elf")
set(CMAKE_EXECUTABLE_SUFFIX_CXX ".elf")

set(DEFAULT_C_FLAGS "-ffunction-sections -fdata-sections -ffreestanding -fmessage-length=0")
set(DEFAULT_CXX_FLAGS "-fno-threadsafe-statics -fno-rtti -fno-exceptions -fno-use-cxa-atexit -Wno-volatile")

set(CMAKE_C_FLAGS_INIT
    "${DEFAULT_C_FLAGS}"
    CACHE
    INTERNAL "Default C compiler flags.")
set(CMAKE_CXX_FLAGS_INIT
    "${DEFAULT_C_FLAGS} ${DEFAULT_CXX_FLAGS}"
    CACHE
    INTERNAL "Default CXX compiler flags.")
set(CMAKE_ASM_FLAGS_INIT
    "-x assembler-with-cpp"
    CACHE
    INTERNAL "Default ASM compiler flags.")
set(CMAKE_EXE_LINKER_FLAGS_INIT
    "-specs=nosys.specs -flto -Wl,--gc-sections"
    CACHE
    INTERNAL "Default linker flags.")
    
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
message("arm-none-eabi-gcc is configured")