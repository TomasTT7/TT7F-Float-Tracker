/*
TWD0 (PA3) - Peripheral A
TWCK0 (PA4) - Peripheral A
*/

#ifndef ARM_TWI_H
#define ARM_TWI_H

#include "stdint.h"

#define TWI_TIMEOUT 25000

static uint8_t nack = 0;

// Functions
void TWI_init_master(void);
void TWI_deinit(void);
void TWI_write(uint8_t addr, uint8_t intaddrlen, uint8_t intaddr16, uint8_t intaddr8, uint8_t intaddr0, uint8_t *data, uint8_t datalen);
void TWI_read(uint8_t addr, uint8_t intaddrlen, uint8_t intaddr16, uint8_t intaddr8, uint8_t intaddr0, uint8_t *data, uint8_t datalen);

#endif // ARM_TWI_H