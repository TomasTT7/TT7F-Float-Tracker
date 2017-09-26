/*
 * ARM_TWI.c
 *
 * Created: 21.6.2016 10:38:53
 *  Author: Tomy2
 */ 

#include "sam3s8b.h"
#include "ARM_TWI.h"


/*
	Initializes TWI interface in master mode.
*/
void TWI_init_master(void)
{
	uint32_t temp;
	
	PMC->PMC_PCER0 |= (1 << ID_PIOA);									// enable clock to the peripheral
	PIOA->PIO_PDR |= PIO_PA3;											// disable the PIO and enable Peripheral control of the pin
	PIOA->PIO_ABCDSR[0] &= ~PIO_PA3;									// select Peripheral A function
	PIOA->PIO_ABCDSR[1] &= ~PIO_PA3;									// select Peripheral A function
	PIOA->PIO_PUDR |= PIO_PA3;											// disable pull up
	PIOA->PIO_PDR |= PIO_PA4;											// disable the PIO and enable Peripheral control of the pin
	PIOA->PIO_ABCDSR[0] &= ~PIO_PA4;									// select Peripheral A function
	PIOA->PIO_ABCDSR[1] &= ~PIO_PA4;									// select Peripheral A function
	PIOA->PIO_PUDR |= PIO_PA4;											// disable pull up
	
	PMC->PMC_PCER0 |= (1 << ID_TWI0);									// enable clock
	TWI0->TWI_IDR = ~0UL;												// disable TWI interrupts
	temp = TWI0->TWI_SR;												// dummy read in status register
	TWI0->TWI_CR = TWI_CR_SWRST;										// reset TWI peripheral
	temp = TWI0->TWI_RHR;												// dummy read in receive holding register
	TWI0->TWI_CR = TWI_CR_MSDIS;										// master disable
	TWI0->TWI_CR = TWI_CR_SVDIS;										// slave disable
	TWI0->TWI_CR = TWI_CR_MSEN;											// set master enable bit
	TWI0->TWI_CWGR = (CKDIV << 16) | (CHDIV << 8) | (CLDIV << 0);		// for 100kHz TWI speed
	//TWI0->TWI_CR = TWI_CR_QUICK;										// SMBUS Quick command
}


/*
	Disables TWI and enables pull-ups for power saving.
*/
void TWI_deinit(void)
{
	uint32_t timeout = TWI_TIMEOUT;
	
	while(!(TWI0->TWI_SR & TWI_SR_TXCOMP) && timeout) timeout--;		// wait for the end of transmission
	
	TWI0->TWI_CR = TWI_CR_MSDIS;										// master disable
	PMC->PMC_PCDR0 |= (1 << ID_TWI0);									// disable clock
	PIOA->PIO_PUER |= PIO_PA3;											// enable pull up
	PIOA->PIO_PUER |= PIO_PA4;											// enable pull up
}


/*
	General write function. For MT9D111 use dedicated write function in MT9D111 library.
*/
void TWI_write(uint8_t addr, uint8_t intaddrlen, uint8_t intaddr16, uint8_t intaddr8, uint8_t intaddr0, uint8_t *data, uint8_t datalen)
{
	TWI0->TWI_MMR = 0;													// set write mode, slave address and internal address byte lengths
	TWI0->TWI_MMR = (addr << 16) | (intaddrlen << 8);					// device address ADDR, internal device address length LEN 0/1/2/3
	
	TWI0->TWI_IADR = 0;													// set internal address for device
	TWI0->TWI_IADR = (intaddr16 << 16) | (intaddr8 << 8) | (intaddr0 << 0);
	
	uint32_t status;
	while(datalen > 0)													// Send all bytes
	{
		status = TWI0->TWI_SR;
		if (status & TWI_SR_NACK) {nack++; return;}
		if (!(status & TWI_SR_TXRDY)) continue;
		TWI0->TWI_THR = *data++;
		datalen--;
	}

	while(1)
	{
		status = TWI0->TWI_SR;
		if (status & TWI_SR_NACK) {nack++; return;}
		if (status & TWI_SR_TXRDY) break;
	}

	TWI0->TWI_CR = TWI_CR_STOP;											// send STOP bit
	while (!(TWI0->TWI_SR & TWI_SR_TXCOMP));
}


/*
	General read function. For MT9D111 use dedicated read function in MT9D111 library.
*/
uint8_t TWI_read(uint8_t addr, uint8_t intaddrlen, uint8_t intaddr16, uint8_t intaddr8, uint8_t intaddr0, uint8_t *data, uint8_t datalen)
{
	uint8_t stop_sent = 0;
	uint32_t timeout = TWI_TIMEOUT;

	TWI0->TWI_MMR = 0;													// set read mode, slave address and internal address byte lengths
	TWI0->TWI_MMR = TWI_MMR_MREAD | (addr << 16) | (intaddrlen << 8);

	TWI0->TWI_IADR = 0;													// set internal address for remote chip
	TWI0->TWI_IADR = (intaddr16 << 16) | (intaddr8 << 8) | (intaddr0 << 0);
	
	uint32_t status;
	if(datalen == 1)													// send a START condition
	{
		TWI0->TWI_CR = TWI_CR_START | TWI_CR_STOP;
		stop_sent = 1;
	}else{
		TWI0->TWI_CR = TWI_CR_START;
		stop_sent = 0;
	}

	while (datalen > 0)
	{
		status = TWI0->TWI_SR;
		if(status & TWI_SR_NACK) return;
		if(!timeout--) return;
		
		if(datalen == 1  && !stop_sent)									// last byte?
		{
			TWI0->TWI_CR = TWI_CR_STOP;
			stop_sent = 1;
		}

		if(!(status & TWI_SR_RXRDY)) continue;
		
		*data++ = TWI0->TWI_RHR;
		datalen--;
		timeout = TWI_TIMEOUT;
	}

	while(!(TWI0->TWI_SR & TWI_SR_TXCOMP));
	TWI0->TWI_SR;														// dummy read in status register
	
	return 0; // NEW
}