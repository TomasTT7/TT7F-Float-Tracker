/*
 * ARM_UART.c
 *
 * Created: 20.6.2016 10:40:41
 *  Author: Tomy2
 */ 

#include "sam.h"
#include "ARM_UART.h"


/*

*/
void UART0_init(void)
{
	PMC->PMC_PCER0 |= (1 << ID_UART0);					// enable clock for UART
	PIOA->PIO_PDR |= PIO_PA9;							// disable PIO on RX line
	PIOA->PIO_PDR |= PIO_PA10;							// disable PIO on TX line
	PIOA->PIO_ABCDSR[0] &= ~(1 << 9);					// select Peripheral A function
	PIOA->PIO_ABCDSR[1] &= ~(1 << 9);					// select Peripheral A function
	PIOA->PIO_ABCDSR[0] &= ~(1 << 10);					// select Peripheral A function
	PIOA->PIO_ABCDSR[1] &= ~(1 << 10);					// select Peripheral A function
	PIOA->PIO_PUER |= (1 << 9);							// enable pull-up
	PIOA->PIO_PUER |= (1 << 10);						// enable pull-up
	
	UART0->UART_CR = UART_CR_RSTRX | UART_CR_RSTTX;		// reset and disable the RX and TX
	UART0->UART_BRGR = UART0_BAUD;						// set the baud rate to 250000, VALUE = 64000000 / (BAUD RATE * 16)
	UART0->UART_MR |= UART_MR_PAR_NO;					// no parity
	UART0->UART_IER |= UART_IER_RXRDY;					// enable RXRDY interrupt
	NVIC_EnableIRQ(UART0_IRQn);
	UART0->UART_CR = UART_CR_RXEN | UART_CR_TXEN;		// enable RX and TX
}


/*

*/
void UART1_init(void)
{
	PMC->PMC_PCER0 |= (1 << ID_UART1);					// enable clock for UART
	PIOB->PIO_PDR |= PIO_PB2;							// disable PIO on line
	PIOB->PIO_PDR |= PIO_PB3;							// disable PIO on TX line
	PIOB->PIO_ABCDSR[0] &= ~(1 << 2);					// select Peripheral A function
	PIOB->PIO_ABCDSR[1] &= ~(1 << 2);					// select Peripheral A function
	PIOB->PIO_ABCDSR[0] &= ~(1 << 3);					// select Peripheral A function
	PIOB->PIO_ABCDSR[1] &= ~(1 << 3);					// select Peripheral A function
	PIOB->PIO_PUER |= (1 << 2);							// enable pull-up
	PIOB->PIO_PUER |= (1 << 3);							// enable pull-up
	
	UART1->UART_CR = UART_CR_RSTRX | UART_CR_RSTTX;		// reset and disable the RX and TX
	UART1->UART_BRGR = UART1_BAUD;						// set the baud rate to 9600, VALUE = 64000000 / (BAUD RATE * 16)
	UART1->UART_MR |= UART_MR_PAR_NO;					// no parity
	UART1->UART_IER |= UART_IER_RXRDY;					// enable RXRDY interrupt
	NVIC_EnableIRQ(UART1_IRQn);
	UART1->UART_CR = UART_CR_RXEN | UART_CR_TXEN;		// enable RX and TX
}


/*

*/
void UART0_deinit(void)
{
	while(!(UART0->UART_SR & UART_SR_TXEMPTY));			// wait for the end of transmission
	PMC->PMC_PCDR0 |= (1 << ID_UART0);					// disable clock for UART0
}


/*

*/
void UART1_deinit(void)
{
	while(!(UART1->UART_SR & UART_SR_TXEMPTY));			// wait for the end of transmission
	PMC->PMC_PCDR0 |= (1 << ID_UART1);					// disable clock for UART1
}


/*

*/
void UART0_TX(uint8_t data)
{
	while(!(UART0->UART_SR & UART_SR_TXRDY)){}
	UART0->UART_THR = data;
}


/*

*/
void UART1_TX(uint8_t data)
{
	while(!(UART1->UART_SR & UART_SR_TXRDY)){}
	UART1->UART_THR = data;
}


/*

*/
uint8_t UART0_RX(void)
{
	while(!(UART0->UART_SR & UART_SR_RXRDY)){}
	return UART0->UART_RHR;
}


/*

*/
uint8_t UART1_RX(void)
{
	while(!(UART1->UART_SR & UART_SR_RXRDY)){}
	return UART1->UART_RHR;
}


/*

*/
/*
void UART0_Handler(void)
{
	if(UART0_buffer_pointer < UART0_BUFFER_SIZE)
	{
		UART0_RX_buffer[UART0_buffer_pointer] = UART0->UART_RHR;
		UART0_buffer_pointer++;
	}else{
		UART0_temp = UART0->UART_RHR;
	}
}
*/

/*

*/
void UART1_Handler(void)
{
	if(UART1_buffer_pointer < UART1_BUFFER_SIZE)
	{
		UART1_RX_buffer[UART1_buffer_pointer] = UART1->UART_RHR;
		UART1_buffer_pointer++;
	}else{
		UART1_temp = UART1->UART_RHR;
	}
}