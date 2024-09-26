# Tell CMake that we are building for an embedded ARM system
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

# Select compiler
set(MIOSIX_COMPILER_PREFIX arm-none-eabi-)

# From compiler prefix form the name of the compiler and other tools
set(CMAKE_C_COMPILER   ${MIOSIX_COMPILER_PREFIX}gcc)
set(CMAKE_CXX_COMPILER ${MIOSIX_COMPILER_PREFIX}g++)
set(CMAKE_AR           ${MIOSIX_COMPILER_PREFIX}ar)
set(CMAKE_OBJCOPY      ${MIOSIX_COMPILER_PREFIX}objcopy)
set(CMAKE_OBJDUMP      ${MIOSIX_COMPILER_PREFIX}objdump)
set(CMAKE_SIZE         ${MIOSIX_COMPILER_PREFIX}size)

# Reset default compiler flags
set(CMAKE_C_FLAGS_DEBUG     "" CACHE INTERNAL "c debug compiler flags")
set(CMAKE_C_FLAGS_RELEASE   "" CACHE INTERNAL "c release compiler flags")
set(CMAKE_CXX_FLAGS_DEBUG   "" CACHE INTERNAL "cxx debug compiler flags")
set(CMAKE_CXX_FLAGS_RELEASE "" CACHE INTERNAL "cxx release compiler flags")

# Disable compiler checks.
set(CMAKE_C_COMPILER_FORCED TRUE)
set(CMAKE_CXX_COMPILER_FORCED TRUE)
