# Author: Jack Greenberg <j@jackgreenberg.co>

# Define minimum CMake version (required)
cmake_minimum_required(VERSION 3.2)

# Define the project name
project(stm32-buildchain
    VERSION 0.0.1
    LANGUAGES C
)

# Set the CMake Toolchain (arm-none-eabi)
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/toolchain.cmake")
include("${CMAKE_TOOLCHAIN_FILE}")
set(TOOLCHAIN_DIR /opt/gcc-arm-none-eabi)

# Check to make sure the build architecture is arm-none-eabi
if (NOT CMAKE_SYSTEM_PROCESSOR STREQUAL "arm-none-eabi")
    message(FATAL_ERROR "Invalid CMAKE_SYSTEM_PROCESSOR: ${CMAKE_SYSTEM_PROCESSOR}")
else()
    message(STATUS "Using CMAKE_SYSTEM_PROCESSOR: ${CMAKE_SYSTEM_PROCESSOR}")
endif()

# SoC-specific defines
set(STM32_DEFINES " \
    -DIVECT_TAB_OFFset=0x0 \
    -DSTM32F1 \
    -DSTM32F103C8Tx \
    -DSTM32 \
    -DSTM32F10X_MD \
")

set(COMPILER_OPTIMISATION "-O3")

# Include the CMakeLists.txt for libopencm3 (effectively jumps to the file)
include(cmake/libopencm3.cmake)
include(cmake/freertos.cmake)

# At this point, we have defined the LINKER_FILE, set the EXTERNAL_LIBS
# and EXTERNAL_DEPENDENCIES to include libopencm3, and added the custom 
# target to be built

# enable asm for stm startup.s file
enable_language(ASM)

# Set custom flags for compiling and for the STM32
set(STM32_ASM_OPTIONS "-march=armv7-m -mcpu=cortex-m3 -mthumb -mlittle-endian -mthumb-interwork")
set(CMAKE_ASM_FLAGS "${STM32_ASM_OPTIONS}" CACHE INTERNAL "asm compiler flags")

set(STM32_COMPILER_OPTIONS "${STM32_ASM_OPTIONS} \
    -ffunction-sections \
    -fdata-sections \
    -mfloat-abi=soft \
    -fmessage-length=0 \
    -Wall -Werror \
    -Wl,-Map=output.map -Wl,--gc-sections \
    -lm -lc"
)
set(CMAKE_C_FLAGS "${STM32_COMPILER_OPTIONS} ${COMPILER_OPTIMISATION} -std=c11" CACHE INTERNAL "c compiler flags")

set(EXTRA_LINKER_FLAGS "-lm -lc --specs=nano.specs --specs=nosys.specs ")
set(CMAKE_EXE_LINKER_FLAGS "${STM32_COMPILER_OPTIONS} ${LIBOPENCM3_LINKER_FLAGS} -Wl,-Map=linker.map -Wl,-cref " CACHE INTERNAL "exe link flags")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${EXTRA_LINKER_FLAGS} -T${LINKER_FILE}")

add_custom_target(flash
    DEPENDS ${PROJECT_NAME}.elf
    COMMAND openocd -f board/stm32_bluepill.cfg -c "program src/${PROJECT_NAME}.elf verify reset exit"
)

message(STATUS
    "BUILD FLAGS:\n"
    "   STM32_DEFINES   : ${STM32_DEFINES}\n\n"
    "   c flags         : ${CMAKE_C_FLAGS}\n\n"
    "   ld flags        : ${CMAKE_EXE_LINKER_FLAGS}\n\n"
    "   asm flags       : ${CMAKE_ASM_FLAGS}\n"
    "   optimizations   : ${COMPILER_OPTIMISATION}\n"
    "   FreeRTOS        : ${FREERTOS_INC_DIR}\n"
    "   libopencm3      : ${LIBOPENCM3_INC_DIR}\n"
    "                     ${LIBOPENCM3_LINKER_FLAGS}\n"
)

# Add the source subdirectory
add_subdirectory("${CMAKE_SOURCE_DIR}/src")
