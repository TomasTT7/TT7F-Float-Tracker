/*
TT7F SPECIFIC CALCULATIONS
	uint32_t	AD3				=	((uint32_t)AD3data * 3300) / 4096;						Solar Cell Voltage
	uint32_t	AD9				=	((uint32_t)AD9data * 6600) / 4096;						Battery Voltage
	float		temperatureF	=	(float)AD15data * 0.30402 - 274.896 + TEMP_OFFSET;		MCU temperature
*/

#ifndef ARM_ADC_H
#define ARM_ADC_H

#include "stdint.h"


#define TEMP_OFFSET 10.0		// right after first startup it measured 15°C in a ~21°C room


// Functions
void ADC_init(void);
void ADC_deinit(void);
void ADC_start(void);
uint16_t ADC_sample(uint8_t channel, uint32_t n_averaged);
uint16_t ADC_sample_temperature(uint32_t n_averaged);
void ADC_stop(void);
uint16_t ADC_full_sample(uint8_t channel);
uint16_t ADC_full_sample_temperature(void);

#endif // ARM_ADC_H_