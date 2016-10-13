/*
RTC - REAL TIME CLOCK
	The Real-time Clock is continuously clocked at 32768 Hz. The Power Management Controller has no effect on RTC behavior.
	The reference clock is Slow Clock (SLCK - 32.768kHz).
	The RTC is updated in real time at one-second intervals in normal mode for the counters of seconds.
	It is necessary to read the registers twice. If the data is the same both times, then it is valid.
	To update any of the time/calendar fields, the user must first stop the RTC by setting the corresponding field in the
	Control Register. Bit UPDTIM to update hour, minute, second and bit UPDCAL to update century, year, month, date, day.
	
*/

#ifndef ARM_RTC_H
#define ARM_RTC_H


#include "stdint.h"


// Variables
extern uint8_t RTCdate;
extern uint8_t RTCday;
extern uint8_t RTCmonth;
extern uint16_t RTCyear;
extern uint8_t RTCcent;
extern uint8_t RTCampm;
extern uint8_t RTChour;
extern uint8_t RTCmin;
extern uint8_t RTCsec;


// Functions
void RTC_init(uint8_t alren, uint8_t secen, uint8_t timen, uint8_t calen);
void RTC_deinit(void);
void RTC_Handler(void);
uint8_t RTC_get_Time(void);
uint8_t RTC_get_Time_uint(void);
uint8_t RTC_get_Date(void);
uint8_t RTC_get_Date_uint(void);
uint8_t RTC_set_Time(uint8_t ampm, uint8_t hour, uint8_t min, uint8_t sec);
uint8_t RTC_set_Date(uint8_t date, uint8_t day, uint8_t month, uint32_t year);
uint8_t RTC_set_Time_and_Date(uint8_t ampm, uint8_t hour, uint8_t min, uint8_t sec, uint8_t date, uint8_t day, uint8_t month, uint32_t year);
uint8_t RTC_set_Alarm(uint8_t secen, uint8_t sec, uint8_t minen, uint8_t min, uint8_t houren, uint8_t hour,
						 uint8_t ampm, uint8_t dateen, uint8_t date, uint8_t mthen, uint8_t month);
void RTC_correction(uint32_t correction, uint8_t highppm, uint8_t negppm);


#endif // ARM_RTC_H_