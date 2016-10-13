/*
Parallel Capture Mode - Peripheral D (PIO_ABCDSR1 - 1, PIO_ABCDSR2 - 1)
PA15 - PIODCEN1
PA16 - PIODCEN2
PA23 - PIODCCLK
PA24 - PIODC0
PA25 - PIODC1
PA26 - PIODC2
PA27 - PIODC3
PA28 - PIODC4
PA29 - PIODC5
PA30 - PIODC6
PA31 - PIODC7

-Enable PIOA peripheral clock
-Configure the PDC
-Configure the PIO Capture interrupt
-Enable the PDC
-Enable the PIO Capture
-Wait for interrupt
-Disable the interrupt
-Read the DATA
*/

#ifndef ARM_PIODC_H
#define ARM_PIODC_H

#include "stdint.h"

static uint8_t ENDRXflag = 0;

// Functions
void PDC_transfer(uint8_t *buffer, uint16_t counter);
void PIOA_Handler(void);

#endif // ARM_PIODC_H_