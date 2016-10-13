/*
 * ARM_RTC.c
 *
 * Created: 1.10.2016 21:13:03
 *  Author: Tomy2
 */ 

#include "sam.h"
#include "ARM_RTC.h"


/*
	No need to enable clock for RTC in the PMC's PCER0.
	The Real-time Clock is continuously clocked at 32768 Hz. The Power Management Controller has no effect on RTC behavior.
	RTC interrupt requires the interrupt controller to be programmed first (NVIC first, then RTC_IER).
*/
void RTC_init(uint8_t alren, uint8_t secen, uint8_t timen, uint8_t calen)
{
	NVIC_ClearPendingIRQ(RTC_IRQn);			// clear any pending RTC interrupts
	NVIC_EnableIRQ(RTC_IRQn);				// enable RTC interrupts in the Nested Vectored Interrupt Controller
	if(alren) RTC->RTC_IER |= (0x01 << 1);	// ALREN: Alarm Interrupt Enable
	if(secen) RTC->RTC_IER |= (0x01 << 2);	// SECEN: Second Event Interrupt Enable
	if(timen) RTC->RTC_IER |= (0x01 << 3);	// TIMEN: Time Event Interrupt Enable
	if(calen) RTC->RTC_IER |= (0x01 << 4);	// CALEN: Calendar Event Interrupt Enable
}


/*
	The RTC runs permanently. Irrespectively of PMC_PCER0 (ID_RTC) state.
*/
void RTC_deinit(void)
{
	RTC->RTC_IDR = 0x1F;					// disable all RTC interrupts
	NVIC_DisableIRQ(RTC_IRQn);				// disable RTC interrupts in the Nested Vectored Interrupt Controller
}


/*
	The time event is selected in the TIMEVSEL field in RTC_CR and can be any one of these: minute change, hour change, noon, midnight (day change).
	The calendar event is selected in the CALEVSEL field in RTC_CR and can be any one of these: week change, month change and year change.
*/
void RTC_Handler(void)
{
	uint32_t reg = RTC->RTC_SR;
	
	if(reg & (0x01 << 2))					// SEC: Second Event
	{
		/*
		
		code...
		
		*/		
		RTC->RTC_SCCR |= (0x01 << 2);		// SECCLR: Second Clear
	}
	
	if(reg & (0x01 << 1))					// ALARM: Alarm Flag
	{
		/*
		
		code...
		
		*/
		
		//udi_cdc_putc(0xA0);					// DEBUG
		
		RTC->RTC_SCCR |= (0x01 << 1);		// ALRCLR: Alarm Clear
	}
	
	if(reg & (0x01 << 3))					// TIMEV: Time Event
	{
		/*
		
		code...
		
		*/
		RTC->RTC_SCCR |= (0x01 << 3);		// TIMCLR: Time Clear
	}
	
	if(reg & (0x01 << 4))					// CALEV: Calendar Event
	{
		/*
		
		code...
		
		*/
		RTC->RTC_SCCR |= (0x01 << 4);		// CALCLR: Calendar Clear
	}
}


/*
	Returned values are in Binary-Coded Decimal format.
*/
uint8_t RTC_get_Time(void)
{
	uint32_t data = RTC->RTC_TIMR;
	uint32_t check = RTC->RTC_TIMR;
	
	if(data == check)
	{
		RTCampm = (data & (0x01 << 22)) >> 22;
		RTChour = (data & (0x3F << 16)) >> 16;
		RTCmin = (data & (0x7F << 8)) >> 8;
		RTCsec = (data & (0x7F << 0)) >> 0;
		
		return 1;
	}else{
		return 0;
	}
}


/*
	Returned values are in normal unsigned integer format.
*/
uint8_t RTC_get_Time_uint(void)
{
	uint32_t data = RTC->RTC_TIMR;
	uint32_t check = RTC->RTC_TIMR;
	
	if(data == check)
	{
		RTCampm = (data & (0x01 << 22)) >> 22;
		
		RTChour = ((data & (0x03 << 20)) >> 20) * 10 + ((data & (0x0F << 16)) >> 16);
		RTCmin = ((data & (0x07 << 12)) >> 12) * 10 + ((data & (0x0F << 8)) >> 8);
		RTCsec = ((data & (0x07 << 4)) >> 4) * 10 + ((data & (0x0F << 0)) >> 0);
		
		return 1;
	}else{
		return 0;
	}
}


/*
	Returned values are in Binary-Coded Decimal format.
*/
uint8_t RTC_get_Date(void)
{
	uint32_t data = RTC->RTC_CALR;
	uint32_t check = RTC->RTC_CALR;
	
	if(data == check)
	{
		RTCdate = (data & (0x3F << 24)) >> 24;
		RTCday = (data & (0x07 << 21)) >> 21;
		RTCmonth = (data & (0x1F << 16)) >> 16;
		RTCyear = ((data & (0x7F << 0)) << 8) | ((data & (0xFF << 8)) >> 8);
		RTCcent = (data & (0x7F << 0)) >> 0;
		
		return 1;
	}else{
		return 0;
	}
}


/*
	Returned values are in normal unsigned integer format.
*/
uint8_t RTC_get_Date_uint(void)
{
	uint32_t data = RTC->RTC_CALR;
	uint32_t check = RTC->RTC_CALR;
	
	if(data == check)
	{
		RTCdate = ((data & (0x03 << 28)) >> 28) * 10 + ((data & (0x0F << 24)) >> 24);
		RTCday = (data & (0x07 << 21)) >> 21;
		RTCmonth = ((data & (0x01 << 20)) >> 20) * 10 + ((data & (0x0F << 16)) >> 16);
		RTCcent = ((data & (0x07 << 4)) >> 4) * 10 + ((data & (0x0F << 0)) >> 0);
		RTCyear = ((data & (0x0F << 12)) >> 12) * 10 + ((data & (0x0F << 8)) >> 8) + (uint16_t)RTCcent * 100;
		
		return 1;
	}else{
		return 0;
	}
}


/*
	Automatic Error Checking. If one of the time fields is not correct, the data is not loaded into the register/counter
	and a flag is set in the validity register. The user can not reset this flag. It is reset as soon as an acceptable value is programmed.
*/
uint8_t RTC_set_Time(uint8_t ampm, uint8_t hour, uint8_t min, uint8_t sec)
{
	if(ampm > 1 || hour > 23 || min > 59 || sec > 59)
	{
		return 0;
	}
	else
	{
		if(ampm && hour > 12) hour = hour - 12;			// adjust the input for 12 hour mode if selected
		
		uint32_t regData = (ampm << 22) | ((hour / 10) << 20) | ((hour % 10) << 16) | ((min / 10) << 12) | ((min % 10) << 8) | ((sec / 10) << 4) | ((sec % 10) << 0);
		
		while(!(RTC->RTC_SR & (0x01 << 2)));			// wait for SEC bit (in case of successive updates)
		
		RTC->RTC_CR |= (0x01 << 0);						// set UPDTIM to stop the RTC
		while(!(RTC->RTC_SR & (0x01 << 0)));			// wait for ACKUPD bit
		RTC->RTC_SCCR |= (0x01 << 0);					// clear the ACKUPD flag
		
		if(ampm) RTC->RTC_MR |= (0x01 << 0);			// set HRMOD if in 12 hour mode
		else RTC->RTC_MR &= ~(0x01 << 0);				// clear HRMOD if in 24 hour mode
		
		RTC->RTC_TIMR = regData;						// update the TIME values
		
		RTC->RTC_CR &= ~(0x01 << 0);					// clear UPDTIM
		RTC->RTC_SCCR |= (0x01 << 2);					// clear the SECCLR flag
		
		if(RTC->RTC_VER & (0x01 << 0)) return 0;		// check for any errors while setting the new values
		else return 1;
	}
}


/*
	Automatic Error Checking. If one of the time fields is not correct, the data is not loaded into the register/counter
	and a flag is set in the validity register. The user can not reset this flag. It is reset as soon as an acceptable value is programmed.
*/
uint8_t RTC_set_Date(uint8_t date, uint8_t day, uint8_t month, uint32_t year)
{
	if(date > 31 || date == 0 || day > 7 || day == 0 || month > 12 || month == 0 || year < 1900 || year > 2099)
	{
		return 0;
	}
	else
	{
		uint32_t regData = ((date / 10) << 28) | ((date % 10) << 24) | (day << 21) | ((month / 10) << 20) | ((month % 10) << 16) | ((year % 100 / 10) << 12) | ((year % 10) << 8) | ((year / 1000) << 4) | ((year / 100 % 10) << 0);
		
		while(!(RTC->RTC_SR & (0x01 << 2)));			// wait for SEC bit (in case of successive updates)
		
		RTC->RTC_CR |= (0x01 << 1);						// set UPDCAL to stop the RTC
		while(!(RTC->RTC_SR & (0x01 << 0)));			// wait for ACKUPD bit
		RTC->RTC_SCCR |= (0x01 << 0);					// clear the ACKUPD flag
	
		RTC->RTC_CALR = regData;						// update the CALENDAR values
		
		RTC->RTC_CR &= ~(0x01 << 1);					// clear UPDCAL
		RTC->RTC_SCCR |= (0x01 << 2);					// clear the SECCLR flag
		
		if(RTC->RTC_VER & (0x01 << 1)) return 0;		// check for any errors while setting the new values
		else return 1;
	}
}


/*
	In successive update operations, the user must wait at least one second after resetting the UPDTIM/UPDCAL bit in the RTC_CR
	before setting these bits again. Therefore it is faster to do both updates at the same time.
*/
uint8_t RTC_set_Time_and_Date(uint8_t ampm, uint8_t hour, uint8_t min, uint8_t sec, uint8_t date, uint8_t day, uint8_t month, uint32_t year)
{
	if(ampm > 1 || hour > 23 || min > 59 || sec > 59 || date > 31 || date == 0 || day > 7 || day == 0 || month > 12 || month == 0 || year < 1900 || year > 2099)
	{
		return 0;
	}
	else
	{
		if(ampm && hour > 12) hour = hour - 12;			// adjust the input for 12 hour mode if selected
		
		uint32_t regDataT = (ampm << 22) | ((hour / 10) << 20) | ((hour % 10) << 16) | ((min / 10) << 12) | ((min % 10) << 8) | ((sec / 10) << 4) | ((sec % 10) << 0);
		uint32_t regDataC = ((date / 10) << 28) | ((date % 10) << 24) | (day << 21) | ((month / 10) << 20) | ((month % 10) << 16) | ((year % 100 / 10) << 12) | ((year % 10) << 8) | ((year / 1000) << 4) | ((year / 100 % 10) << 0);
		
		while(!(RTC->RTC_SR & (0x01 << 2)));			// wait for SEC bit (in case of successive updates)
		
		RTC->RTC_CR |= (0x01 << 1) | (0x01 << 0);		// set UPDTIM and UPDCAL to stop the RTC
		while(!(RTC->RTC_SR & (0x01 << 0)));			// wait for ACKUPD bit
		RTC->RTC_SCCR |= (0x01 << 0);					// clear the ACKUPD flag
		
		if(ampm) RTC->RTC_MR |= (0x01 << 0);			// set HRMOD if in 12 hour mode
		else RTC->RTC_MR &= ~(0x01 << 0);				// clear HRMOD if in 24 hour mode
		
		RTC->RTC_TIMR = regDataT;						// update the TIME values
		RTC->RTC_CALR = regDataC;						// update the CALENDAR values
	
		RTC->RTC_CR &= ~(0x03 << 0);					// clear UPDTIM and UPDCAL
		RTC->RTC_SCCR |= (0x01 << 2);					// clear the SECCLR flag
	
		uint32_t VERreg = RTC->RTC_VER;
		if(VERreg & (0x01 << 0) || VERreg & (0x01 << 1)) return 0;		// check for any errors while setting the new values
		else return 1;
	}
}


/*

*/
uint8_t RTC_set_Alarm(uint8_t secen, uint8_t sec, uint8_t minen, uint8_t min, uint8_t houren, uint8_t hour,
						 uint8_t ampm, uint8_t dateen, uint8_t date, uint8_t mthen, uint8_t month)
{
	uint32_t regDataT = 0;
	uint32_t regDataC = 0;
	
	if(secen)
	{
		if(sec > 59) return 0;							// check for erroneous input
		regDataT |= (0x01 << 7) | ((sec / 10) << 4) | ((sec % 10) << 0);
	}
	
	if(minen)
	{
		if(min > 59) return 0;							// check for erroneous input
		regDataT |= (0x01 << 15) | ((min / 10) << 12) | ((min % 10) << 8);
	}
	
	if(houren)
	{
		if(ampm > 1 || hour > 23) return 0;				// check for erroneous input
		if(ampm && hour > 12) hour = hour - 12;			// adjust the input for 12 hour mode if selected
		regDataT |= (0x01 << 23) | (ampm << 22) | ((hour / 10) << 20) | ((hour % 10) << 16);
	}
	
	if(dateen)
	{
		if(date > 31 || date == 0) return 0;			// check for erroneous input
		regDataC |= (0x01 << 31) | ((date / 10) << 28) | ((date % 10) << 24);
	}else{
		regDataC |= (0x01 << 24);						// apparently requires a value even when not enabled
	}
	
	if(mthen)
	{
		if(month > 12 || month == 0) return 0;			// check for erroneous input
		regDataC |= (0x01 << 23) | ((month / 10) << 20) | ((month % 10) << 16);
	}else{
		regDataC |= (0x01 << 16);						// apparently requires a value even when not enabled
	}
	
	RTC->RTC_SCCR |= (0x01 << 1);						// ALRCLR: Alarm Clear
	
	RTC->RTC_TIMALR = regDataT;							// update the TIME values
	RTC->RTC_CALALR = regDataC;							// update the CALENDAR values
		
	uint32_t VERreg = RTC->RTC_VER;
	if(VERreg & (0x01 << 2) || VERreg & (0x01 << 3)) return 0;		// check for any errors while setting the new values
	else return 1;
}


/*
	NEGPPM: NEGative PPM Correction (the divider will be slightly higher than 32768).
	HIGHPPM: HIGH PPM Correction. HIGHPPM set to 1 is recommended for 30 ppm correction and above.
	CORRECTION: 1..127 = The slow clock will be corrected according to the formula given below.
	
	CORRECTION = ( 3906 / (20 * PPM) ) - 1
	
	Applies to both the 32kHz Crystal Oscillator and the RC Oscillator. However, the DATASHEET states the frequency range for the RC Oscillator
	to be 20 to 44kHz. While the RTC peripheral can correct only for about +-65Hz at 32768Hz (+-1950ppm).
*/
void RTC_correction(uint32_t correction, uint8_t highppm, uint8_t negppm)
{
	RTC->RTC_MR &= ~((0xFF << 8) | (0x01 << 4));							// prepare the NEGPPM, HIGHPPM and CORRECTION field for new values
	RTC->RTC_MR |= (highppm << 15) | (correction << 8) | (negppm << 4);
}