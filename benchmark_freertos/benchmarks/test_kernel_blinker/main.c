#include <stdio.h>
#include <benchmark.h>
#include "stm32f469xx.h"
#include "stm32f4xx_hal.h"

void freertos_main(void)
{
    BEGIN_SMALL_BENCHMARK("blinker");

    iprintf("Blinker Kernel\n");

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    for (int i=0; i<2; i++) {
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);
        vTaskDelay(1000);
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET);
        vTaskDelay(1000);
    }

    for (;;) {
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET);
    }

    END_BENCHMARK;
    return 0;
}
