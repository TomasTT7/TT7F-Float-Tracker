/*
BAUD RATE
	BAUD RATE = MCK / SCBR
	SI4060 max speed is 10MHz
	
	64MHz MCK
		6	-	10.666MHz
		8	-	8MHz
		32	-	2MHz
	12MHz MCK
		2	-	6MHz
		6	-	2MHz
		32	-	375kHz
*/

#ifndef ARM_SPI_H
#define ARM_SPI_H

#include "stdint.h"


#define SPI_TIMEOUT 15000
#define SPI_SCBR 8					// MCK divider for effective BAUD RATE


// Functions
void SPI_init(void);
void SPI_deinit(void);
uint16_t SPI_write(uint16_t data, uint8_t lastxfer);

#endif // ARM_SPI_H_