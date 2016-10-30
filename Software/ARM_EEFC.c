/*
 * ARM_EEFC.c
 *
 * Created: 29.10.2016 23:38:32
 *  Author: Tomy2
 */ 

#include <asf.h>
#include "ARM_EEFC.h"


/*
	 FRDY	Ready Interrupt Enable		
	 FWS	Flash Wait State							Number of cycles for Read/Write operations = FWS+1.
	 SCOD	Sequential Code Optimization Disable		0: The sequential code optimization is enabled.
														1: The sequential code optimization is disabled.
														(No Flash read should be done during change of this register.)
	 FAM	Flash Access Mode							0: 128-bit access in read Mode only, to enhance access speed.
														1: 64-bit access in read Mode only, to enhance power consumption.
														(No Flash read should be done during change of this register.)
*/
void EEFC_setup(uint8_t FRDY, uint8_t FWS, uint8_t SCOD, uint8_t FAM)
{
	FWS &= 0x0F;																		// 4-bit value
	
	EFC->EEFC_FMR = (FAM << 24) | (SCOD << 16) | (FWS << 8) | (FRDY << 0);
}


/*
	SAM3S8B DESCRIPTOR
								value				value(decimal)		address
		FL_ID					0x000F0710
		FL_SIZE					0x00080000			524288
		FL_PAGE_SIZE			0x00000100			256
		FL_NB_PLANE				0x00000001			1
		FL_PLANE[0]				0x00080000			524288
		FL_NB_LOCK				0x00000010			16
		FL_LOCK[0]				0x00000800			32768				0x00400000
		FL_LOCK[1]				0x00000800			32768				0x00408000
		FL_LOCK[2]				0x00000800			32768				0x00410000
		FL_LOCK[3]				0x00000800			32768				0x00418000
		FL_LOCK[4]				0x00000800			32768				0x00420000
		FL_LOCK[5]				0x00000800			32768				0x00428000
		FL_LOCK[6]				0x00000800			32768				0x00430000
		FL_LOCK[7]				0x00000800			32768				0x00438000
		FL_LOCK[8]				0x00000800			32768				0x00440000
		FL_LOCK[9]				0x00000800			32768				0x00448000
		FL_LOCK[10]				0x00000800			32768				0x00450000
		FL_LOCK[11]				0x00000800			32768				0x00458000
		FL_LOCK[12]				0x00000800			32768				0x00460000
		FL_LOCK[13]				0x00000800			32768				0x00468000
		FL_LOCK[14]				0x00000800			32768				0x00470000
		FL_LOCK[15]				0x00000800			32768				0x00478000
		?						0x00000009			9
*/
uint8_t EEFC_read_descriptor(void)
{
	uint8_t i = 0;
	uint32_t EEFC_FRRreg = 0;
	
	while(!(EFC->EEFC_FSR & (0x01 << 0)));												// wait for FRDY flag
	EFC->EEFC_FCR = (0x5A << 24);														// GETD command
	while(!(EFC->EEFC_FSR & (0x01 << 0)));												// wait for FRDY flag
	
	while(1)
	{
		EEFC_FRRreg = EFC->EEFC_FRR;													// read the response in EEFC_FRR
		if(EEFC_FRRreg == 0) break;
		EEFC_descriptor[i++] = EEFC_FRRreg;
	}
	
	return i;
}


/*
	Function to erase and write a PAGE in the internal FLASH.
	It uses IAP function located in ROM so it can be used for self programming.
	The EEFC utilizes a write buffer of the same size as one PAGE.
	One PAGE is 256 bytes and SAM3S8B has 2048 pages in its 524288 bytes of FLASH memory. 
*/
void EEFC_write_page(uint8_t * data, uint32_t len, uint32_t page)
{
	uint32_t status = 0;
	
	static uint32_t (*IAP_Function)(uint32_t, uint32_t);								// pointer on IAP function in ROM
	IAP_Function = (uint32_t(*)(uint32_t, uint32_t))*((uint32_t*)IAP_FUNCTION_ADDR);	// point it to the right address
	
	uint32_t *flashPageBuffer;															// pointer to the write start address
	flashPageBuffer = (uint32_t *)(INT_FLASH_START + page * PAGE_SIZE);					// full address calculated from the PAGE parameter
	
	for(uint8_t i = 0; i < len / 4; i++)												// fill the flash write buffer with the data
	{
		flashPageBuffer[i] = ((uint32_t)data[i * 4 + 0] << 24) |
							((uint32_t)data[i * 4 + 1] << 16) |
							((uint32_t)data[i * 4 + 2] << 8) |
							((uint32_t)data[i * 4 + 3] << 0);
	}
	
	__disable_irq();																	// ensure no attempts to access the FLASH
	status = IAP_Function(0, (0x5A << 24) | (page << 8) | (0x03 << 0));					// EWP - Erase page and write page command
	__enable_irq();
}


/*
	Reads LEN bytes from FLASH memory starting at ADDRESS. Bytes get saved into the BUFFER.
*/
void EEFC_read_bytes(uint32_t * address, uint32_t len, uint8_t * buffer)
{
	for(uint32_t i = 0; i < len; i += 4)
	{
		buffer[i] = *address >> 24;
		buffer[i + 1] = *address >> 16;
		buffer[i + 2] = *address >> 8;
		buffer[i + 3] = *address >> 0;
		
		address++;
	}
}