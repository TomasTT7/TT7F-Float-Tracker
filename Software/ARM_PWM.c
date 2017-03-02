/*
 * ARM_PWM.c
 *
 * Created: 21.6.2016 12:10:14
 *  Author: Tomy2
 */ 

#include "sam.h"
#include "ARM_PWM.h"


/*
	Generates clock signal for MT9D111 on PB13 - PWML2 (Peripheral A).
		
	CPRD	Period of the output wave form. PERIOD = CPRD / MCK
	CDTY	Duty cycle must be between 0 and CPRD.
	
	MCK		64MHz
	CPRD	10		8		6		4
	CDTY	5		4		3		2
	CLK		6.4MHz	8MHz	10.7MHz	16MHz
	
	Running the MT9D111 with a 10.7MHz clock seems to be the maximum at which the PDC manages to transfer all of the bits.
*/
void PWM_init(uint32_t cprd_period, uint32_t cdty_duty_cycle)
{
	uint32_t CPRD = cprd_period & 0x00FFFFFF;
	uint32_t CDTY = cdty_duty_cycle & 0x00FFFFFF;
	
	PMC->PMC_PCER0 |= (1 << ID_PIOB);											// enable clock for PIOB
	PIOB->PIO_PDR |= PIO_PB13;													// disable PIO on the line
	PIOB->PIO_ABCDSR[0] &= ~(1 << 13);											// select Peripheral A function
	PIOB->PIO_ABCDSR[1] &= ~(1 << 13);											// select Peripheral A function
	PIOB->PIO_PUDR |= PIO_PB13;													// disable pull up
	
	PMC->PMC_PCER0 |= (1 << ID_PWM);											// enable clock
	PWM->PWM_DIS = (1 << 2);													// disable channel
	PWM->PWM_CH_NUM[2].PWM_CMR = (0x00 << 0);									// MCK clock (64MHz)

	if ((PWM->PWM_SR & (1 << 2)) == 0) PWM->PWM_CH_NUM[2].PWM_CPRD = CPRD;		// FINAL FREQUENCY = FREQUENCY / CPRD - 6.4MHz
	else PWM->PWM_CH_NUM[2].PWM_CPRDUPD = CPRD;									// double buffer for when the channel is already enabled
	
	if ((PWM->PWM_SR & (1 << 2)) == 0) PWM->PWM_CH_NUM[2].PWM_CDTY = CDTY;		// value between 0 and CPRD, DUTY CYCLE = (DUTY / PERIOD) * 100 - 50%
	else PWM->PWM_CH_NUM[2].PWM_CDTYUPD = CDTY;									// double buffer for when the channel is already enabled
	
	PWM->PWM_ENA = (1 << 2);													// enable channel
}


/*
	Disables the PWM signal on PB13.
*/
void PWM_deinit(void)
{
	PWM->PWM_DIS = (1 << 2);													// disable channel
	PMC->PMC_PCDR0 |= (1 << ID_PWM);											// disable clock
}