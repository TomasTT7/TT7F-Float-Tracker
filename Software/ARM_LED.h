

#ifndef ARM_LED_H
#define ARM_LED_H


#include "stdint.h"


// Functions
void LED_PA0_init(void);
void LED_PA0_toggle(void);
void LED_PA0_blink(uint32_t ms);
void LED_PA0_disable(void);
void LED_PB5_init(void);
void LED_PB5_toggle(void);
void LED_PB5_blink(uint32_t ms);
void LED_PB5_disable(void);


#endif // ARM_LED_H_