#ifndef ARM_EEFC_H
#define ARM_EEFC_H


#include "stdint.h"


#define INT_FLASH_START			0x00400000										// Internal FLASH start address
#define INT_FLASH_END			0x00480000										// SAM3S8B
#define INT_FLASH_SIZE			524288											// SAM3S8B
#define PAGE_SIZE				256
#define IAP_FUNCTION_ADDR		0x00800008										// IAP function address in ROM


// VARIABLES
extern uint32_t EEFC_descriptor[32];


// FUNCTIONS
void EEFC_setup(uint8_t FRDY, uint8_t FWS, uint8_t SCOD, uint8_t FAM);
uint8_t EEFC_read_descriptor(void);
void EEFC_write_page(uint8_t * data, uint32_t len, uint32_t page);
void EEFC_read_bytes(uint32_t * address, uint32_t len, uint8_t * buffer);


#endif // ARM_EEFC_H_