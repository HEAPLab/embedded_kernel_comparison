cmake_minimum_required(VERSION 3.15)

set(CMAKE_TOOLCHAIN_FILE "cmake/toolchains/arm-none-eabi.cmake")

project(FreeRTOSMPUTest C CXX ASM)

set(FREERTOS_CONFIG_FILE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}" CACHE STRING "" FORCE)
set(FREERTOS_PORT "GCC_ARM_CM4_MPU" CACHE STRING "" FORCE)

include_directories(
  CMSIS/Include
  CMSIS/Device/ST/STM32F4xx/Include
  STM32F4xx_HAL_Driver/Inc
  FreeRTOS/include
)
add_compile_options(
  -O2 -g
  -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard -u _printf_float
  -fdata-sections -ffunction-sections
  -DSTM32F469xx -DDATA_IN_ExtSDRAM 
)
add_link_options(
  -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard -u _printf_float
  -Wl,--gc-sections "-T${CMAKE_CURRENT_SOURCE_DIR}/STM32F469NIHx_FLASH.ld"
  "-Wl,-Map=${CMAKE_CURRENT_BINARY_DIR}/binary.map"
)

add_subdirectory(FreeRTOS)

add_executable(freertos_mpu_test.elf
  startup_stm32f469xx.S
  newlib_lock_glue.c
  syscalls.c
  sysmem.c
  system_stm32f4xx.c
  stm32f4xx_it.c
  freertos.c
  peripherals.c
  main.c
  exploit.c
  STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c
  STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c
  STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.c
  STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c
  STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_sram.c
  STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.c
  STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.c
  STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_uart.c
  STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_usart.c
  STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.c
  STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c
  STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_fmc.c
  STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_fsmc.c
  STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_gpio.c
  STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_rcc.c
  STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_tim.c
  STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_usart.c
  STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_utils.c
)
target_link_libraries(freertos_mpu_test.elf PUBLIC freertos_kernel)
add_custom_target(freertos_mpu_test.bin ALL
  COMMAND arm-none-eabi-objcopy -O binary -S freertos_mpu_test.elf freertos_mpu_test.bin
  DEPENDS freertos_mpu_test.elf
)
