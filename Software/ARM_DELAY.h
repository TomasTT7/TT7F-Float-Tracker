/*
SysTick
	24-bit system timer that counts down from the reload value to zero.
	CLK source is either MCK or MCK/8.
*/

#ifndef ARM_DELAY_H
#define ARM_DELAY_H

#include "stdint.h"

#define SYSTICK_LOAD 12000 // 64000 - 64MHz; 12000 - 12MHz; ...

static volatile uint32_t timestamp = 0;

// Functions
void SysTick_delay_init(void);
void SysTick_delay_ms(uint32_t ms);
void SysTick_Handler(void);

#endif // ARM_DELAY_H_