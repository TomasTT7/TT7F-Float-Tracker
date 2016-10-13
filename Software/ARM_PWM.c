/*
 * ARM_PWM.c
 *
 * Created: 21.6.2016 12:10:14
 *  Author: Tomy2
 */ 

#include "sam.h"
#include "ARM_PWM.h"


/*
	PB13 - PWML2 (Peripheral A) - 6.4MHz clock 50% duty cycle
*/
void PWM_init(void)
{
	PMC->PMC_PCER0 |= (1 << ID_PIOB);										// enable clock for PIOB
	PIOB->PIO_PDR |= PIO_PB13;												// disable PIO on the line
	PIOB->PIO_ABCDSR[0] &= ~(1 << 13);										// select Peripheral A function
	PIOB->PIO_ABCDSR[1] &= ~(1 << 13);										// select Peripheral A function
	PIOB->PIO_PUDR |= PIO_PB13;												// disable pull up
	
	PMC->PMC_PCER0 |= (1 << ID_PWM);										// enable clock
	PWM->PWM_DIS = (1 << 2);												// disable channel
	PWM->PWM_CH_NUM[2].PWM_CMR = (0x00 << 0);								// MCK clock (64MHz)

	if ((PWM->PWM_SR & (1 << 2)) == 0) PWM->PWM_CH_NUM[2].PWM_CPRD = 10;	// FINAL FREQUENCY = FREQUENCY / CPRD - 6.4MHz
	else PWM->PWM_CH_NUM[2].PWM_CPRDUPD = 10;								// double buffer for when the channel is already enabled
	
	if ((PWM->PWM_SR & (1 << 2)) == 0) PWM->PWM_CH_NUM[2].PWM_CDTY = 5;		// value between 0 and CPRD, DUTY CYCLE = (DUTY / PERIOD) * 100 - 50%
	else PWM->PWM_CH_NUM[2].PWM_CDTYUPD = 5;								// double buffer for when the channel is already enabled
	
	PWM->PWM_ENA = (1 << 2);												// enable channel
}


/*

*/
void PWM_stop(void)
{
	PWM->PWM_DIS = (1 << 2);												// disable channel
	PMC->PMC_PCDR0 |= (1 << ID_PWM);										// disable clock
}