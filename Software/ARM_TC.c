/*
 * ARM_TC.c
 *
 * Created: 21.6.2016 12:17:29
 *  Author: Tomy2
 */ 

#include "sam.h"
#include "ARM_TC.h"

void TC0_init(void)
{
	// disable and clear any pending interrupt input before configuring it
	NVIC_DisableIRQ(TC0_IRQn);
	NVIC_ClearPendingIRQ(TC0_IRQn);
	NVIC_SetPriority(TC0_IRQn, 0);
	
	PMC->PMC_PCER0 |= (1 << ID_TC0); // enable clock to the peripheral
	TC0->TC_CHANNEL[0].TC_CMR = 3 | (1 << 14); // TIMER_CLOCK4, CPCTRG
	TC0->TC_CHANNEL[0].TC_RC = 10000; // compare value
	TC0->TC_CHANNEL[0].TC_IER = (1 << 4); // CPCS enable RC Compare interrupt
	TC0->TC_CHANNEL[0].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG; // enable the clock
	
	// enable interrupt input (system exceptions/interrupts don't use NVIC)
	NVIC_EnableIRQ(TC0_IRQn);
}

void TC0_Handler(void)
{
	interruptStatus = TC0->TC_CHANNEL[0].TC_SR; // read the Status Register and clear the interrupt
	/*
	
	
	
	*/
}