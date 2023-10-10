# the name of the target operating system
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_C_COMPILER_FORCED TRUE)
set(CMAKE_CXX_COMPILER_FORCED TRUE)

#Tell cmake to not check the compiler for this build because we're cross compiling and it will fail.
set(CMAKE_SKIP_COMPILER_CHECK TRUE)

# Set the toolchain prefix (adjust this to match your ARM GCC installation)
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)

# Set the linker and objcopy programs
set(CMAKE_LINKER arm-none-eabi-ld)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_SIZE arm-none-eabi-size)

# Specify compiler flags and options
set(CMAKE_C_FLAGS_INIT "-mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16")
set(CMAKE_CXX_FLAGS_INIT "")
set(CMAKE_ASM_FLAGS_INIT "")

# Specify additional compiler flags (e.g., optimization, debugging, and warning flags)
set(CMAKE_C_FLAGS_DEBUG "-O0 -g")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")
set(CMAKE_ASM_FLAGS_DEBUG "-g")

set(CMAKE_C_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_ASM_FLAGS_RELEASE "")

# Set the default linker script
set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/asf/sam/utils/linker_scripts/samv71/samv71q21/gcc/flash.ld) #Set linker script in cmakelists
set(CMAKE_EXE_LINKER_FLAGS_INIT "-T ${LINKER_SCRIPT} -Wl,-Map=Mapfile.map --specs=nosys.specs")

# Specify linker flags and options
#set(CMAKE_EXE_LINKER_FLAGS_DEBUG "-Wl,-Map=Mapfile.map --specs=nosys.specs")
#set(CMAKE_EXE_LINKER_FLAGS_RELEASE "")

# Specify preprocessor definitions if needed
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DDEFINITION1 -DDEFINITION2")

# Specify include directories
# include_directories(${CMAKE_SOURCE_DIR}/Include)
# Add any other necessary include paths

# Specify the default output directory for build artifacts (optional)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Specify the architecture and platform (optional)
# set(CMAKE_SYSTEM_NAME Generic)
# set(CMAKE_SYSTEM_PROCESSOR arm)