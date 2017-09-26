/*
	
*/

#ifndef ARM_SI5351_H
#define ARM_SI5351_H

#include "stdint.h"


#define SI5351_ADDRESS 0x60

#define SI5351_FREQUENCY 14097405000		// units 0.001Hz, this specific Si5351 seems to transmit 215Hz at 23.5°C (ambient) lower in frequency
#define VCO_FREQUENCY 690039077				// units Hz (chosen to minimize rounding)


extern uint64_t SI5351frequency001Hz;

static uint64_t PLLAfreq = 0;				// units Hz
static uint64_t XTALfreq = 25000000;		// units Hz


// Functions
uint8_t SI5351_register_write(uint8_t address, uint8_t data);
uint8_t SI5351_register_read(uint8_t address);
void SI5351_init(void);
void SI5351_deinit(void);
void SI5351_start_TX(void);
void SI5351_stop_TX(void);
void SI5351_PLLA_frequency(uint64_t freqHZ);
void SI5351_MS0_frequency(uint64_t freq001HZ);
void SI5351_PLLA_frequency_ABC(uint32_t a, uint32_t b, uint32_t c);
void SI5351_MS0_frequency_ABC(uint32_t a, uint32_t b, uint32_t c);
void SI5351_frequency(uint64_t freq001Hz);


#endif // ARM_SI5351_H_