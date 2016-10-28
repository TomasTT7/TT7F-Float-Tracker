#ifndef ARM_WATCHDOG_H
#define ARM_WATCHDOG_H


#include "stdint.h"


// FUNCTIONS
void WATCHDOG_enable(uint16_t period, uint8_t idleHalt);
void WATCHDOG_disable(void);
void WATCHDOG_restart(void);


#endif // ARM_WATCHDOG_H_