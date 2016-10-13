/*
RTT - REAL TIME TIMER
	32bit counter of the Slow Clock (32.768kHz) dividable by a 16bit value (RTT_MR - RTPRES)
	current value of the timer in RTT_VR - CRTV
	current value compared with the value in RTT_AR; if they match, the bit ALMS in RTT_SR is set
	RTTINC in RTT_SR is set each time the counter is incremented
	reading RTT_SR resets RTTINC and ALMS flags
	example: RTPRES = 0x8000, ALMV = 2, alarm every 2 seconds
*/

#ifndef ARM_RTT_H
#define ARM_RTT_H

#include "stdint.h"


// Functions
void RTT_init(uint32_t almv, uint16_t rtpres, uint8_t interruptEN); // interruptEN 0 - disable Alarm Interrupt, 1 - enable Alarm Interrupt (ALMIEN)
void RTT_off(void);
void RTT_Handler(void);

#endif // ARM_RTT_H_