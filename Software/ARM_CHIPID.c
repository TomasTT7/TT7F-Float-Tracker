/*
 * ARM_CHIPID.c
 *
 * Created: 5.9.2016 21:34:52
 *  Author: Tomy2
 */ 

#include "sam.h"
#include "ARM_CHIPID.h"

void CHIPID_read_EXID(void)
{
	CHIPID_exid = CHIPID->CHIPID_EXID;
}

void CHIPID_read_CIDR(void)
{
	uint32_t val = CHIPID->CHIPID_CIDR;
	
	CHIPID_version	= (val & 0x1f) >> 0;
	CHIPID_eproc	= (val & 0xE0) >> 5;
	CHIPID_nvpsiz	= (val & 0xF00) >> 8;
	CHIPID_nvpsiz2	= (val & 0xF000) >> 12;
	CHIPID_sramsiz	= (val & 0xF0000) >> 16;
	CHIPID_arch		= (val & 0xFF00000) >> 20;
	CHIPID_nvptyp	= (val & 0x70000000) >> 28;
	CHIPID_ext		= (val & 0x80000000) >> 31;
	
	if(CHIPID_ext) CHIPID_read_EXID();
}