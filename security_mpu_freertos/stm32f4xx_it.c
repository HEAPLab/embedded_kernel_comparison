#include <stdio.h>
#include "stm32f469xx.h"
#include "stm32f4xx_it.h"

void logMPUFault(uint32_t *faultStackAddr)
{
  MPU->CTRL = 0; // disable mpu in case it's misconfigured
  __DMB();
  iprintf("MPU fault\n");
  iprintf("SP=%p PC=%p\n", faultStackAddr, faultStackAddr[6]);
  uint32_t mmfar = SCB->MMFAR;
  iprintf("MMFAR=%p CFSR=%08x\n", mmfar, SCB->CFSR);
  for (int i=0; i<8; i++) {
    MPU->RNR = i;
    uint32_t rasr = MPU->RASR;
    uint32_t rbar = MPU->RBAR;
    uint32_t size = 1 << ((rasr & 0x3E)/2 + 1);
    uint32_t base = rbar & 0xFFFFFFF0;
    int mmfarIn = base <= mmfar && mmfar < (base+size);
    iprintf("Region %d: RBAR=%08x RASR=%08x (size=%08x) %c\n", i, rbar, rasr, size, mmfarIn ? '*' : ' ');
  }
  //unsigned int base=regValues[2*i] & (~0x1f);
  //unsigned int end=base+(1<<(((regValues[2*i+1]>>1) & 31)+1));
  //char w=regValues[2*i+1] & (1<<MPU_RASR_AP_Pos) ? 'w' : '-';
  //char x=regValues[2*i+1] & MPU_RASR_XN_Msk ? '-' : 'x';
  //iprintf("* MPU region %d 0x%08x-0x%08x r%c%c\n",i+6,base,end,w,x);
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  uint32_t *sp;
  asm volatile(
		"tst lr, #4\n"
		"ite eq\n"
		"mrseq %0, msp\n"
		"mrsne %0, psp\n":"=r"(sp)::"cc");
  logMPUFault(sp);
  *CRASH_REPORT_LOC = CRASH_MEM_MANG;
  NVIC_SystemReset();
}

/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  *CRASH_REPORT_LOC = CRASH_NMI;
  NVIC_SystemReset();
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  *CRASH_REPORT_LOC = CRASH_HARDFAULT;
  NVIC_SystemReset();
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  *CRASH_REPORT_LOC = CRASH_BUS;
  NVIC_SystemReset();
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  *CRASH_REPORT_LOC = CRASH_USAGE;
  NVIC_SystemReset();
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
}
