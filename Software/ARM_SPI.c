/*
 * ARM_SPI.c
 *
 * Created: 20.6.2016 14:46:21
 *  Author: Tomy2
 */ 

#include "sam.h"
#include "ARM_SPI.h"


/*
	Initializes the pins and SPI peripheral in master mode.
*/
void SPI_init(void)
{
	PMC->PMC_PCER0 |= (1 << ID_PIOA);							// enable clock for PIOA

	PIOA->PIO_PDR |= PIO_PA12;									// MISO (PIO Disable Register) - disable the PIO and enable Peripheral control
	PIOA->PIO_ODR |= PIO_PA12;									// MISO input (Output Disable Register)
	PIOA->PIO_ABCDSR[0] &= ~(1 << 12);							// select Peripheral A function
	PIOA->PIO_ABCDSR[1] &= ~(1 << 12);							// select Peripheral A function
	
	PIOA->PIO_PDR |= PIO_PA13;									// MOSI (PIO Disable Register)
	PIOA->PIO_OER |= PIO_PA13;									// MOSI output (Output Enable Register)
	PIOA->PIO_ABCDSR[0] &= ~(1 << 13);							// select Peripheral A function
	PIOA->PIO_ABCDSR[1] &= ~(1 << 13);							// select Peripheral A function
	
	PIOA->PIO_PDR |= PIO_PA14;									// SPCK (PIO Disable Register)
	PIOA->PIO_OER |= PIO_PA14;									// SPCK output (Output Enable Register)
	PIOA->PIO_ABCDSR[0] &= ~(1 << 14);							// select Peripheral A function
	PIOA->PIO_ABCDSR[1] &= ~(1 << 14);							// select Peripheral A function
	
	PIOA->PIO_PDR |= PIO_PA11;									// NPCS0 (PIO Disable Register)
	PIOA->PIO_OER |= PIO_PA11;									// NPCS0 output (Output Enable Register)
	PIOA->PIO_ABCDSR[0] &= ~(1 << 11);							// select Peripheral A function
	PIOA->PIO_ABCDSR[1] &= ~(1 << 11);							// select Peripheral A function
	PIOA->PIO_PUER |= PIO_PA11;									// enable pull-up
	
	PMC->PMC_PCER0 |= (1 << ID_SPI);							// enable clock for SPI
	
	SPI->SPI_CR = SPI_CR_SPIDIS;								// disable SPI to configure it
	SPI->SPI_CR = SPI_CR_SWRST;									// reset
	SPI->SPI_MR |= SPI_MR_MSTR;									// master mode
	SPI->SPI_MR |= SPI_MR_MODFDIS;								// disable mode fault detection
	SPI->SPI_MR &= ~(0xFu << 16);
	SPI->SPI_MR |= (0xE << 16);									// select NPCS0
	SPI->SPI_CSR[0] &= ~(SPI_CSR_CPOL);							// SPCK inactive state is LOW
	SPI->SPI_CSR[0] |= SPI_CSR_NCPHA;
	SPI->SPI_CSR[0] |= SPI_CSR_CSAAT;							// chip select remains active
	SPI->SPI_CSR[0] &= ~(0xFu << 4);
	SPI->SPI_CSR[0] |= (0 << 4);								// 8 bits for transfer
	SPI->SPI_CSR[0] &= ~(0xFFu << 8);
	SPI->SPI_CSR[0] |= (SPI_SCBR << 8);							// BAUDRATE = MCK / SCBR (32 for 2000000 - SI4060 max 10000000)
	SPI->SPI_CSR[0] &= ~((0xFFu << 24) | (0xFFu << 16));
	SPI->SPI_CSR[0] |= (0 << 24) | (0 << 16);					// delay before SPCK and delay between transfers
	SPI->SPI_CR = SPI_CR_SPIEN;									// enable SPI
}


/*
	
*/
void SPI_deinit(void)
{
	while(!(SPI->SPI_SR & SPI_SR_TXEMPTY));						// wait for the end of transmission
	SPI->SPI_CR = SPI_CR_SPIDIS;								// disable SPI
	PMC->PMC_PCDR0 |= (1 << ID_SPI);							// disable clock for SPI
	PIOA->PIO_PUER |= PIO_PA11;									// enable pull-up
	PIOA->PIO_PUER |= PIO_PA12;									// enable pull-up
	PIOA->PIO_PUER |= PIO_PA13;									// enable pull-up
	PIOA->PIO_PUER |= PIO_PA14;									// enable pull-up
}


/*
	Send/receive one byte.
	
		LASTXFER	0 = The Peripheral Chip Select Line rises as soon as the last transfer is achieved.
					1 = The Peripheral Chip Select remains active until a new transfer is requested on a different chip select.
*/
uint16_t SPI_write(uint16_t data, uint8_t lastxfer)
{
	SPI->SPI_CR = SPI_CR_SPIEN;									// enable SPI if disabled
	
	uint32_t timeout = SPI_TIMEOUT;
	uint32_t val;
	static uint32_t reg_value = 0;
	
	while (!(SPI->SPI_SR & SPI_SR_TDRE))
	{
		if (!timeout--)
		{
			return 0;
		}
	}
	
	if (lastxfer)
	{
		val = data;
		SPI->SPI_CSR[0] &= ~(SPI_CSR_CSAAT);
	}else{
		val = data;
		SPI->SPI_CSR[0] |= SPI_CSR_CSAAT;
	}
	
	SPI->SPI_TDR = val;
		
	timeout = SPI_TIMEOUT;
	
	while(!(SPI->SPI_SR & SPI_SR_RDRF))
	{
		if (!timeout--)
		{
			return 0;
		}
	}
	
	reg_value = SPI->SPI_RDR;
	
	return (uint16_t)reg_value;
}