/*
 * ARM_ADC.c
 *
 * Created: 20.6.2016 15:13:57
 *  Author: Tomy2
*/

#include "sam.h"
#include "ARM_ADC.h"
#include "ARM_DELAY.h"


/*

*/
void ADC_init(void)
{
	PMC->PMC_PCER0 |= (1 << ID_PIOA);					// enable clock to the peripheral
	PIOA->PIO_PDR |= (1 << 20);							// disable PIOC control on the pin (disable peripheral control)
	PIOA->PIO_PDR |= (1 << 22);							// disable PIOC control on the pin (disable peripheral control)
	PIOA->PIO_PUDR |= (1 << 20);						// disable pull-up
	PIOA->PIO_PUDR |= (1 << 22);						// disable pull-up
}


/*

*/
void ADC_deinit(void)
{
	PMC->PMC_PCDR0 |= (1 << ID_ADC);					// disable clock
	PIOA->PIO_PUER |= (1 << 20);						// enable pull-up
	PIOA->PIO_PUER |= (1 << 22);						// enable pull-up
}


/*
ADC Clock Frequency		Min: 1 MHz		Max: 20 MHz
Sampling Frequency		Max: 1 MHz
Current Consumption		4.3 mA <500kHz	5.4 mA >500kHz

PRESCAL
	ADCClock = MCK / ( (PRESCAL+1) * 2 )
	
STARTUP: Start Up Time
	ADC Startup time	Max: 40us
	80 periods of ADCClock (STARTUP: 5)
	
TRACKTIM: Tracking Time
	Tracking Time = (TRACKTIM + 1) * ADCClock periods
	
TRANSFER: Transfer Period
	Transfer Period = (TRANSFER * 2 + 3) ADCClock periods

ROUTINE for multiple ADC measurements:
	ADC_start()
	ADC_sample(1)
	ADC_sample(2)
	ADC_sample(3)
	ADC_sample_temperature()
	ADC_stop()
	
Timing Example
	ADC Clock Frequency:	1Mhz								1us
	ADC Startup time:		40us (max)							80us
	Transfer				?									5us
	Track and Hold Time:	160ns (min)							25us
	Conversion Time:		20 * ADC Clock Period				20us
	
	One Full ADC reading:										30us
	Averaged Readings:											100
	One ADC_sample():											80us + 3ms
*/
void ADC_start(void)
{
	PMC->PMC_PCER0 |= (1 << ID_ADC);					// enable clock for ADC
	ADC->ADC_CR = ADC_CR_SWRST;							// Reset the controller.
	ADC->ADC_MR = 0;									// Reset Mode Register.
	ADC->ADC_MR |= (0x01 << 28) | (0x18 << 24) | (0x05 << 16) | (0x05 << 8);	// TRANSFER, TRACKTIM, STARTUP, PRESCAL
}


/*
	Maximum of 1048832 n_averaged. Uint32_t can handle a value of 4294967295 before it overflows. Maximum ADC values of 4095 give 1048832 samples.
*/
uint16_t ADC_sample(uint8_t channel, uint32_t n_averaged)
{
	uint32_t ADCdata = 0;
	
	ADC->ADC_CHER = (1 << channel);						// enable channel
	
	for(uint32_t i = 0; i < n_averaged; i++)
	{
		ADC->ADC_CR = ADC_CR_START;						// begin AD conversion
		while(!(ADC->ADC_ISR & (0x01 << channel)));		// EOCx: End of Conversion x
		ADCdata += ADC->ADC_CDR[channel];				// read the value
	}
	
	ADC->ADC_CHDR = (1 << channel);						// channel disable
	
	ADCdata = ADCdata / n_averaged;						// finish the computation of the average
	
	return ADCdata;
}


/*
	Temperature sensor on AD15.
	
	Output Voltage:				0.8V		27°C
	Temperature Sensitivity:	2.65mV/°C
	
	Temperature = ADCreading / 4096 * 3.3 / 0.00265 - 274.896
*/
uint16_t ADC_sample_temperature(uint32_t n_averaged)
{
	uint32_t ADCdata = 0;
	
	ADC->ADC_ACR = (1 << 4);							// Temperature sensor on.
	SysTick_delay_ms(1);								// 40us start-up time
	ADC->ADC_CHER = (1 << 15);							// enable channel
	
	for(uint32_t i = 0; i < n_averaged; i++)
	{
		ADC->ADC_CR = ADC_CR_START;						// begin AD conversion
		while(!(ADC->ADC_ISR & (0x01 << 15)));			// EOCx: End of Conversion x
		ADCdata += ADC->ADC_CDR[15];
	}
	
	ADC->ADC_ACR = 0;									// Temperature sensor off.
	ADC->ADC_CHDR = (1 << 15);							// channel disable
	
	ADCdata = ADCdata / n_averaged;						// finish the computation of the average
	
	return ADCdata;
}


/*

*/
void ADC_stop(void)
{
	PMC->PMC_PCDR0 |= (1 << ID_ADC);		// disable clock
}


/*
	Noticed problems when measuring different channels in succession.
*/
uint16_t ADC_full_sample(uint8_t channel)
{
	PMC->PMC_PCER0 |= (1 << ID_ADC);		// enable clock for ADC
	ADC->ADC_CR = ADC_CR_SWRST;				// Reset the controller.
	ADC->ADC_MR = 0;						// Reset Mode Register.
	ADC->ADC_MR |= (0x1u << 28) | (0x00u << 24) | (0x03u << 20) | (0xFFu << 8) | (0x08u << 0); // 125kHz (minimum) ADC clock, disable External trigger, settling 17 periods
	ADC->ADC_CHER = (1 << channel);			// enable channel
	ADC->ADC_CR = ADC_CR_START;				// begin AD conversion
	uint32_t status = ADC->ADC_ISR;
	while((status & (0x1u << channel)) != (0x1u << channel)) status = ADC->ADC_ISR;	// wait for End of Conversion
	uint16_t data = (uint16_t)ADC->ADC_CDR[channel];
	
	ADC->ADC_CHDR = (1 << channel);			// channel disable
	PMC->PMC_PCDR0 |= (1 << ID_ADC);		// disable clock
	
	return data;
}


/*
	Noticed problems when measuring different channels in succession.
	Temperature sensor on AD15.
*/
uint16_t ADC_full_sample_temperature(void)
{
	PMC->PMC_PCER0 |= (1 << ID_ADC);		// enable clock for ADC
	ADC->ADC_ACR = (1 << 4);				// Temperature sensor on.
	SysTick_delay_ms(1);					// 40us start-up time
	ADC->ADC_CR = ADC_CR_SWRST;				// Reset the controller.
	ADC->ADC_MR = 0;						// Reset Mode Register.
	ADC->ADC_MR |= (0x1u << 28) | (0x00u << 24) | (0x03u << 20) | (0xFFu << 8) | (0x08u << 0); // 125kHz (minimum) ADC clock, disable External trigger, settling 17 periods
	ADC->ADC_CHER = (1 << 15);				// enable channel
	ADC->ADC_CR = ADC_CR_START;				// begin AD conversion
	
	uint32_t status = ADC->ADC_ISR;
	while((status & (0x1u << 15)) != (0x1u << 15)) status = ADC->ADC_ISR;	// wait for End of Conversion
	uint16_t data = (uint16_t)ADC->ADC_CDR[15];
	
	ADC->ADC_ACR = 0;						// Temperature sensor off.
	ADC->ADC_CHDR = (1 << 15);				// channel disable
	PMC->PMC_PCDR0 |= (1 << ID_ADC);		// disable clock
	
	return data;
}