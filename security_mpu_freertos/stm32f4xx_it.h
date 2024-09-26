#ifndef STM32F4XX_IT_H
#define STM32F4XX_IT_H

#include <stdint.h>

#define CRASH_REPORT_LOC ((uint32_t*)0x20001000UL)
#define CRASH_GOOD          0x00000000
#define CRASH_NMI           0xbadf00d0
#define CRASH_HARDFAULT     0xbadf00d1
#define CRASH_BUS           0xbadf00d2
#define CRASH_USAGE         0xbadf00d3
#define CRASH_FREERTOS_DEAD 0xbadf00d4
#define CRASH_MEM_MANG      0xbadf00d5

#endif
