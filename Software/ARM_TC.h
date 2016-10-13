

#ifndef ARM_TC_H
#define ARM_TC_H

#include "stdint.h"

static uint32_t interruptStatus = 0;

// Functions
void TC0_init(void);
void TC0_Handler(void);

#endif // ARM_TC_H_