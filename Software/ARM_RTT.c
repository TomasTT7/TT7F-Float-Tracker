/*
 * ARM_RTT.c
 *
 * Created: 8.9.2016 14:37:49
 *  Author: Tomy2
 */ 

#include "sam.h"
#include "ARM_RTT.h"


/*
	ALMIEN		disable Alarm Interrupt		enable Alarm Interrupt
				0							1
	
	RTPRES defines the number of SLCK periods required to increment the Real-time timer.
		RTPRES = 0: The prescaler period is equal to 2^16 * SCLK period.
		RTPRES ? 0: The prescaler period is equal to RTPRES * SCLK period.
	
	ALMV defines the alarm value (ALMV+1) compared with the Real-time Timer.
*/
void RTT_init(uint32_t almv, uint16_t rtpres, uint8_t almien)
{
	uint32_t SRreg = 0;
	
	SRreg = RTT->RTT_SR;									// Clear any pending flags
	
	PMC->PMC_PCER0 |= (1 << ID_RTT);						// enable clock for RTT
	RTT->RTT_AR = almv;										// set the alarm value (ALMV + 1) to compare with the counter
	RTT->RTT_MR = (0x01u << 18) | (almien << 16) | rtpres;	// set the PRESCALER, reset the counter (RTPRES * SCLK period), enable/disable interrupt
	
	if(almien) NVIC_EnableIRQ(RTT_IRQn);
	else NVIC_DisableIRQ(RTT_IRQn);
}


/*

*/
void RTT_off(void)
{
	uint32_t SRreg = 0;
	
	SRreg = RTT->RTT_SR;									// Clear any pending flags
	
	PMC->PMC_PCDR0 |= (1 << ID_RTT);						// disable clock for RTT
}


/*

*/
void RTT_Handler(void)
{
	uint32_t SRreg = 0;
	
	SRreg = RTT->RTT_SR;									// Read the Status Register and clear any pending interrupts.
}