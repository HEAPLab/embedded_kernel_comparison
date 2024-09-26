#include <stdio.h>
#include "peripherals.h"
#include "FreeRTOS.h"
#include "task.h"
#include "exploit.h"
#include "stm32f4xx_it.h"

#define FUZZER_MAIN_STACK_SZ 4096

int main(void)
{
  SCB->SHCSR |= SCB_SHCSR_USGFAULTENA_Msk
             | SCB_SHCSR_BUSFAULTENA_Msk
             | SCB_SHCSR_MEMFAULTENA_Msk; //enable Usage-/Bus-/MPU Fault

  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_USART3_UART_Init();

  xTaskCreate(fuzzer, "fuzzer", FUZZER_MAIN_STACK_SZ/4, NULL, 2 | portPRIVILEGE_BIT, NULL);
  vTaskStartScheduler();

  *CRASH_REPORT_LOC = CRASH_FREERTOS_DEAD;
  NVIC_SystemReset();
}
