/*
 * ARM_LED.c
 *
 * Created: 21.6.2016 12:01:16
 *  Author: Tomy2
 */ 


#include "sam.h"
#include "ARM_LED.h"
#include "ARM_DELAY.h"


/*
	TT7F's lower LED.
*/
void LED_PA0_init(void)
{
	PMC->PMC_PCER0 |= (1 << ID_PIOA);										// enable clock to the peripheral
	PIOA->PIO_PER |= (1 << 0);												// enable PIOC control on the pin (disable peripheral control)
	PIOA->PIO_OER |= PIO_PA0;												// enable Output
	PIOA->PIO_PUDR |= (1 << 0);												// disable pull-up
}


/*

*/
void LED_PA0_toggle(void)
{
	if(!(PIOA->PIO_ODSR & PIO_PA0)) PIOA->PIO_SODR |= PIO_PA0;				// Set Output Data Register
	else PIOA->PIO_CODR |= PIO_PA0;											// Clear Output Data Register
}


/*

*/
void LED_PA0_blink(uint32_t ms)
{
	PIOA->PIO_SODR |= PIO_PA0;												// Set Output Data Register
	SysTick_delay_ms(ms);
	PIOA->PIO_CODR |= PIO_PA0;												// Clear Output Data Register
}


/*

*/
void LED_PA0_disable(void)
{
	PMC->PMC_PCER0 |= (1 << ID_PIOA);										// enable clock to the peripheral
	PIOA->PIO_PER |= PIO_PA0;												// enable PIOC control on the pin (disable peripheral control)
	PIOA->PIO_PUDR |= PIO_PA0;												// disable pull-up
	PIOA->PIO_CODR |= PIO_PA0;												// Clear Output Data Register
}


/*
	TT7F's upper LED.
*/
void LED_PB5_init(void)
{
	MATRIX->CCFG_SYSIO |= (1 << 5);				// System I/O lines must be configured in this register as well (PB4, PB5, PB6, PB7, PB10, PB11, PB12)
	PMC->PMC_PCER0 |= (1 << ID_PIOB);			// enable clock to the peripheral
	PIOB->PIO_OER |= PIO_PB5;					// enable Output on PB5
	PIOB->PIO_PER |= (1 << 5);					// enable PIOC control on the pin (disable peripheral control)
	PIOB->PIO_PUDR |= (1 << 5);					// disable pull-up
}


/*

*/
void LED_PB5_toggle(void)
{
	if(!(PIOB->PIO_ODSR & PIO_PB5)) PIOB->PIO_SODR |= PIO_PB5;				// Set Output Data Register
	else PIOB->PIO_CODR |= PIO_PB5;											// Clear Output Data Register
}


/*

*/
void LED_PB5_blink(uint32_t ms)
{
	PIOB->PIO_SODR |= PIO_PB5;												// Set Output Data Register
	SysTick_delay_ms(ms);
	PIOB->PIO_CODR |= PIO_PB5;												// Clear Output Data Register
}


/*

*/
void LED_PB5_disable(void)
{
	MATRIX->CCFG_SYSIO |= (1 << 5);				// System I/O lines must be configured in this register as well (PB4, PB5, PB6, PB7, PB10, PB11, PB12)
	PMC->PMC_PCER0 |= (1 << ID_PIOB);			// enable clock to the peripheral
	PIOB->PIO_PER |= PIO_PB5;					// enable PIOC control on the pin (disable peripheral control)
	PIOB->PIO_PUDR |= PIO_PB5;					// disable pull-up
	PIOB->PIO_CODR |= PIO_PB5;					// Clear Output Data Register
}