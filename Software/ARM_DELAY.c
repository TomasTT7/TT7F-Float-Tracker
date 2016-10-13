/*
 * ARM_DELAY.c
 *
 * Created: 20.6.2016 15:24:25
 *  Author: Tomy2
 */ 

#include "sam.h"
#include "ARM_DELAY.h"

void SysTick_delay_init(void)
{
	// configure SysTick to 1ms
	SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk; // disables SysTick and chooses MCK as the clock
	SysTick->VAL = 0; // reset the counter
	SysTick->LOAD = SYSTICK_LOAD; // for every 1ms
	SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
}

void SysTick_delay_ms(uint32_t ms)
{
	timestamp = 0;
	while((timestamp < ms));
}

void SysTick_Handler(void)
{
	timestamp++;
}