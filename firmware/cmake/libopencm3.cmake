# Set variable to be libopencm3 path
set(LIBOPENCM3_DIR ${CMAKE_SOURCE_DIR}/lib/libopencm3)

# This is the directory that gets included in our library
set(LIBOPENCM3_INC_DIR ${LIBOPENCM3_DIR}/include)

# Creates the libopencm3 target
#   The command to build it uses the Makefile in lib/libopencm3
#   WORKING_DIRECTORY sets it to run in lib/libopencm3
add_custom_target(libopencm3
    COMMAND make -j8 PREFIX=${TOOLCHAIN_BIN_DIR}/${TOOL_CHAIN_PREFIX} TARGETS=stm32/f1 all
    WORKING_DIRECTORY ${LIBOPENCM3_DIR}
)

# Set lib directory to be linked
link_directories(${LIBOPENCM3_DIR}/lib)
include_directories(${LIBOPENCM3_INC_DIR})

# Used in compiling to set -lopencm3_stm32f1
set(LIBOPENCM3_LIB opencm3_stm32f1)
set(LINKER_FILE "${CMAKE_SOURCE_DIR}/stm32f103c8.ld")

# Avoid known bug in linux giving: 
#    arm-none-eabi-gcc: error: unrecognized command line option '-rdynamic'
set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")


set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --static -nostartfiles ")

set(LIBOPENCM3_LINKER_FLAGS " --static -nostartfiles ")

# Add libopencm3 to the external libs and dependencies
set(EXTERNAL_LIBS ${EXTERNAL_LIBS} ${LIBOPENCM3_LIB})
set(EXTERNAL_DEPENDENCIES ${EXTERNAL_DEPENDENCIES} libopencm3)
set(EXTERNAL_EXECUTABLES ${EXTERNAL_EXECUTABLES} opencm3.c)
