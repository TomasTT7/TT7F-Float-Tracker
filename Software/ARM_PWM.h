
#ifndef ARM_PWM_H
#define ARM_PWM_H


#include "stdint.h"


// Functions
void PWM_init(uint32_t cprd_period, uint32_t cdty_duty_cycle);
void PWM_deinit(void);


#endif //  ARM_PWM_H_