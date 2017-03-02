/*
 * ARM_PIODC.c
 *
 * Created: 21.6.2016 11:32:54
 *  Author: Tomy2
 */ 

#include "sam.h"
#include "ARM_PIODC.h"


/*
	Initializes the Peripheral DMA Controller and starts a data transfer from the Parallel Capture Mode pins to a selected buffer.
	A byte of data is sampled at rising edge of the sensor clock (PIODCCLK) when both enable signals (PIODCEN1 and PIODCEN2) are set.
	After each transfered byte the Receive Counter set by COUNTER is decreased until it reads zero and the ENDRX interrupt fires. 
*/
void PDC_transfer(uint8_t *buffer, uint16_t counter)
{
	PMC->PMC_PCER0 |= (1 << ID_PIOA);							// enable clock to the peripheral
	PIOA->PIO_PCIER = (1 << 2);									// enable ENDRX interrupt
	NVIC_EnableIRQ(PIOA_IRQn);
	PIOA->PIO_PTCR = (1 << 1);									// RXTDIS Receiver Transfer Disable
	PIOA->PIO_RPR = buffer;										// Receive Pointer
	PIOA->PIO_RCR = counter;									// Receive Counter
	PIOA->PIO_PTCR = (1 << 0);									// enable PDC receiver
	PIOA->PIO_PCMR = 0;											// configure Parallel Capture Mode, 8-bit data, sample when both ENABLEs are active
	PIOA->PIO_PCMR = 1;											// enable Parallel Capture Mode
}


/*
	Handler that sets the disables the Parallel Capture Mode when ENDRX (End of Reception Transfer) interrupt fires.
*/
void PIOA_Handler(void)
{
	if(PIOA->PIO_PCISR & PIO_PCISR_ENDRX)
	{
		PIOA->PIO_PCMR = 0;										// disable Parallel Capture Mode
		PIOA->PIO_PCIDR = (1 << 2);								// disable ENDRX interrupt
	}
}