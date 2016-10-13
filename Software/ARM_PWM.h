
#ifndef ARM_PWM_H
#define ARM_PWM_H

#include "stdint.h"

// Functions
void PWM_init(void); // PB13 - PWML2 (Peripheral A) - 6.4MHz clock 50% duty cycle
void PWM_stop(void); // PB13 - PWML2 (Peripheral A)

#endif //  ARM_PWM_H_