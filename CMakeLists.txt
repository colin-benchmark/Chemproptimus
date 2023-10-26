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
    CSP_FREERTOS
)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Add all .c files in the src directory to the SOURCES list
file(GLOB SOURCES "src/*.c")
file(GLOB BSS_LIB "src/lib/**/*.c")
file(GLOB RB_LIB "src/rb/**/**/*.c")

# Add additional library files
list(APPEND SOURCES ${BSS_LIB} ${RB_LIB})

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
    asf/sam/drivers/wdt/wdt.c
    asf/sam/utils/cmsis/samv71/source/templates/gcc/startup_samv71.c
    asf/sam/utils/cmsis/samv71/source/templates/system_samv71.c
    asf/sam/utils/syscalls/gcc/syscalls.c
    asf/thirdparty/freertos/freertos-202212.01/Source/croutine.c
    asf/thirdparty/freertos/freertos-202212.01/Source/event_groups.c
    asf/thirdparty/freertos/freertos-202212.01/Source/portable/GCC/ARM_CM7/r0p1/port.c
    asf/thirdparty/freertos/freertos-202212.01/Source/portable/MemMang/heap_4.c
    asf/thirdparty/freertos/freertos-202212.01/Source/list.c
    asf/thirdparty/freertos/freertos-202212.01/Source/queue.c
    asf/thirdparty/freertos/freertos-202212.01/Source/tasks.c
    asf/thirdparty/freertos/freertos-202212.01/Source/timers.c
    libcsp/src/arch/freertos/csp_malloc.c
    libcsp/src/arch/freertos/csp_queue.c
    libcsp/src/arch/freertos/csp_semaphore.c
    libcsp/src/arch/freertos/csp_system.c
    libcsp/src/arch/freertos/csp_thread.c
    libcsp/src/arch/freertos/csp_time.c
    libcsp/src/arch/freertos/csp_clock.c
    libcsp/src/arch/csp_system.c
    libcsp/src/arch/csp_time.c
    libcsp/src/crypto/csp_hmac.c
    libcsp/src/crypto/csp_sha1.c
    libcsp/src/crypto/csp_xtea.c
    libcsp/src/csp_bridge.c
    libcsp/src/csp_buffer.c
    libcsp/src/csp_conn.c
    libcsp/src/csp_crc32.c
    libcsp/src/csp_debug.c
    libcsp/src/csp_dedup.c
    libcsp/src/csp_endian.c
    libcsp/src/csp_iflist.c
    libcsp/src/csp_io.c
    libcsp/src/csp_port.c
    libcsp/src/csp_promisc.c
    libcsp/src/csp_qfifo.c
    libcsp/src/csp_route.c
    libcsp/src/csp_services.c
    libcsp/src/csp_service_handler.c
    libcsp/src/csp_sfp.c
    libcsp/src/interfaces/csp_if_kiss.c
    libcsp/src/interfaces/csp_if_lo.c
    libcsp/src/rtable/csp_rtable_static.c
    libcsp/src/rtable/csp_rtable.c
    libcsp/src/transport/csp_rdp.c
    libcsp/src/transport/csp_udp.c
    libcsp/src/drivers/usart/usart_kiss.c
    libcsp/src/csp_init.c 
)

# Set the SOURCES variable
set(SOURCES ${SOURCES})

# Include directories
set(INCLUDE_DIRS
    src/
    src/config
    src/lib
    src/rb
    src/rb/interfaces
    src/rb/components
    src/rb/instances
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
    asf/sam/drivers/wdt
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
    asf/thirdparty/freertos/freertos-202212.01
    asf/thirdparty/freertos/freertos-202212.01/Source
    asf/thirdparty/freertos/freertos-202212.01/Source/include
    asf/thirdparty/freertos/freertos-202212.01/Source/portable
    asf/thirdparty/freertos/freertos-202212.01/Source/portable/GCC
    asf/thirdparty/freertos/freertos-202212.01/Source/portable/GCC/ARM_CM7
    asf/thirdparty/freertos/freertos-202212.01/Source/portable/GCC/ARM_CM7/r0p1
    asf/thirdparty/freertos/freertos-202212.01/Source/portable/MemMang/
    libcsp
    libcsp/include
    libcsp/include/csp
    libcsp/include/csp/arch
    libcsp/include/csp/drivers
    libcsp/include/csp/interfaces
    libcsp/src
    libcsp/src/arch
    libcsp/src/crypto
    libcsp/src/interfaces
    libcsp/src/transport
    libcsp/src/rtable
)

include_directories(${INCLUDE_DIRS})
link_directories(${CMAKE_SOURCE_DIR}/samv71b/gcc/gcc)

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES})
