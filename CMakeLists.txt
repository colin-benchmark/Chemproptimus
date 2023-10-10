cmake_minimum_required(VERSION 3.23)
project(Xantus)

# Set compiler and linker options
add_compile_definitions(
    DEBUG
    __SAMV71Q21B__
    BOARD=SAMV71_XPLAINED_ULTRA
    scanf=iscanf
    ARM_MATH_CM7=true
    printf=iprintf
)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Add all .c files in the src directory to the SOURCES list
file(GLOB SOURCES "src/*.c")
file(GLOB LIBRARIES "src/bss_lib/**/*.c")

# Add additional library files
list(APPEND SOURCES ${LIBRARIES})

# Add additional specific source files
list(APPEND SOURCES
    asf/common/services/clock/samv71/sysclk.c
    asf/common/services/serial/usart_serial.c
    asf/common/utils/interrupt/interrupt_sam_nvic.c
    asf/common/utils/stdio/read.c
    asf/common/utils/stdio/write.c
    asf/sam/boards/samv71_xplained_ultra/init.c
    asf/sam/drivers/matrix/matrix.c
    asf/sam/drivers/mpu/mpu.c
    asf/sam/drivers/pio/pio.c
    asf/sam/drivers/pio/pio_handler.c
    asf/sam/drivers/pmc/pmc.c
    asf/sam/drivers/pmc/sleep.c
    asf/sam/drivers/tc/tc.c
    asf/sam/drivers/uart/uart.c
    asf/sam/drivers/usart/usart.c
    asf/sam/utils/cmsis/samv71/source/templates/gcc/startup_samv71.c
    asf/sam/utils/cmsis/samv71/source/templates/system_samv71.c
    asf/sam/utils/syscalls/gcc/syscalls.c
    asf/thirdparty/freertos/freertos-10.0.0/Source/croutine.c
    asf/thirdparty/freertos/freertos-10.0.0/Source/event_groups.c
    asf/thirdparty/freertos/freertos-10.0.0/Source/portable/GCC/ARM_CM7/r0p1/port.c
    asf/thirdparty/freertos/freertos-10.0.0/Source/portable/MemMang/heap_3.c
    asf/thirdparty/freertos/freertos-10.0.0/Source/list.c
    asf/thirdparty/freertos/freertos-10.0.0/Source/queue.c
    asf/thirdparty/freertos/freertos-10.0.0/Source/tasks.c
    asf/thirdparty/freertos/freertos-10.0.0/Source/timers.c
)

# Set the SOURCES variable
set(SOURCES ${SOURCES})

# Include directories
set(INCLUDE_DIRS
    src/
    src/config
    src/bss_lib
    asf
    asf/common
    asf/common/boards
    asf/common/services
    asf/common/services/clock
    asf/common/services/clock/samv71
    asf/common/services/gpio
    asf/common/services/gpio/sam_gpio
    asf/common/services/ioport
    asf/common/services/ioport/sam
    asf/common/services/serial
    asf/common/services/serial/sam_uart
    asf/common/utils
    asf/common/utils/interrupt
    asf/common/utils/stdio
    asf/common/utils/stdio/stdio_serial
    asf/sam
    asf/sam/boards
    asf/sam/boards/samv71_xplained_ultra
    asf/sam/drivers
    asf/sam/drivers/matrix
    asf/sam/drivers/mpu
    asf/sam/drivers/pio
    asf/sam/drivers/pmc
    asf/sam/drivers/tc
    asf/sam/drivers/uart
    asf/sam/drivers/usart
    asf/sam/utils
    asf/sam/utils/cmsis
    asf/sam/utils/cmsis/samv71
    asf/sam/utils/cmsis/samv71/include
    asf/sam/utils/cmsis/samv71/include/component
    asf/sam/utils/cmsis/samv71/include/instance
    asf/sam/utils/cmsis/samv71/include/pio
    asf/sam/utils/cmsis/samv71/source
    asf/sam/utils/cmsis/samv71/source/templates
    asf/sam/utils/cmsis/samv71/source/templates/gcc
    asf/sam/utils/fpu
    asf/sam/utils/header_files
    asf/sam/utils/linker_scripts
    asf/sam/utils/linker_scripts/samv71
    asf/sam/utils/linker_scripts/samv71/samv71q21
    asf/sam/utils/linker_scripts/samv71/samv71q21/gcc
    asf/sam/utils/make
    asf/sam/utils/preprocessor
    asf/sam/utils/syscalls
    asf/sam/utils/syscalls/gcc
    asf/thirdparty
    asf/thirdparty/CMSIS
    asf/thirdparty/CMSIS/Include
    asf/thirdparty/CMSIS/Lib
    asf/thirdparty/CMSIS/Lib/GCC
    asf/thirdparty/freertos
    asf/thirdparty/freertos/freertos-10.0.0
    asf/thirdparty/freertos/freertos-10.0.0/Source
    asf/thirdparty/freertos/freertos-10.0.0/Source/include
    asf/thirdparty/freertos/freertos-10.0.0/Source/portable
    asf/thirdparty/freertos/freertos-10.0.0/Source/portable/GCC
    asf/thirdparty/freertos/freertos-10.0.0/Source/portable/GCC/ARM_CM7
    asf/thirdparty/freertos/freertos-10.0.0/Source/portable/GCC/ARM_CM7/r0p1
    asf/thirdparty/freertos/freertos-10.0.0/Source/portable/MemMang/
)

include_directories(${INCLUDE_DIRS})
link_directories(${CMAKE_SOURCE_DIR}/samv71b/gcc/gcc)

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES})

add_subdirectory(libcsp)  # Include libcsp
target_link_libraries(${PROJECT_NAME} csp)  # Link against libcsp
