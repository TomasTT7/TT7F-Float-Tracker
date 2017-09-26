/*
	Example WSPR message:	OK7DMT JN99 30
		CALLSIGN:			OK7DMT
		LOCATOR:			JN99
		POWER:				30			(0,3,7,10,13,17,20,23,27,30,33,37,40,43,47,50,53,57,60) -> 0-999m, 1000-1999m, 2000-2999m... >18000m
		50 bits -> 28 bits callsign, 15 bits locator, 7 bits power (rough altitude)
	
	Extended WSPR message:	<OK7DMT> JN99bl 30
		HASHED CALLSIGN:	<OK7DMT>
		LOCATOR:			JN99bl
		POWER:				30			(0,3,7,10,13,17,20,23,27,30,33,37,40,43,47,50,53,57,60) -> 0-52m, 53-105m, 106-158m... 954-999m
		50 bits -> 15 bits hashed callsign, 28 bits 6-character locator, 7 bits power (refined altitude)
		
	Frequencies
		Band		Dial frequency (MHz)		TX frequency (MHz)
		40m			7.038600					7.040000 - 7.040200
		30m			10.138700					10.140100 - 10.140300
		20m			14.095600					14.097000 - 14.097200
		
	Transmission
		synchronized with GPS time
		begins at the start of an even minute
		should start within +-1s
		162 symbols, one symbol 0.6827s
		4 tones spaced 1.46Hz apart
		6Hz bandwidth, 110.6s message duration
		allowed drift ~1Hz
		minimum S/N for reception –28 dB in 2500 Hz reference bandwidth
*/

#ifndef ARM_WSPR_H
#define ARM_WSPR_H


#include "stdint.h"


#define WSPR_CALLSIGN "OK7DMT"					// 6 character callsign


extern uint8_t WSPRcallsign[6];
extern uint8_t WSPRlocator[6];

static uint8_t WSPRbits[11];
static uint8_t WSPRmsg[162];
static uint8_t WSPRtones[162];

static uint8_t WSPRsync[162] = {1,1,0,0,0,0,0,0,1,0,0,0,1,1,1,0,0,0,1,0,0,1,0,1,1,1,1,0,0,0,0,0,0,0,1,0,0,1,0,1,0,0,0,0,0,0,1,0,1,1,0,0,1,1,0,1,0,0,0,1,
								1,0,1,0,0,0,0,1,1,0,1,0,1,0,1,0,1,0,0,1,0,0,1,0,1,1,0,0,0,1,1,0,1,0,1,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,1,1,1,0,1,1,0,0,1,1,
								0,1,0,0,0,1,1,1,0,0,0,0,0,1,0,1,0,0,1,1,0,0,0,0,0,0,0,1,1,0,1,0,1,1,0,0,0,1,1,0,0,0};
								
static uint8_t field[]		 = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R'};
static uint8_t square[]		 = {'0','1','2','3','4','5','6','7','8','9'};
static uint8_t subsquare[]	 = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X'};
static uint8_t powerVals[]	 = {0, 3, 7, 10, 13, 17, 20, 23, 27, 30, 33, 37, 40, 43, 47, 50, 53, 57, 60};


// Functions
uint32_t WSPR_encode_callsign(uint8_t * call);
uint32_t WSPR_encode_callsign_extended(uint8_t * call);
uint32_t WSPR_encode_locator(uint8_t * locator);
uint8_t WSPR_encode_power(uint32_t altitude);
uint8_t WSPR_encode_power_extended(uint32_t altitude);
void WSPR_encode_msg(float lat, float lon, uint32_t alt, uint8_t * callsign);
void WSPR_encode_msg_extended(float lat, float lon, uint32_t alt, uint8_t * callsign);
void WSPR_create_tones(void);
void WSPR_transmit(void);
void GPS_to_Maidenhead(float lat, float lon);

char get_callsign_character_code(char ch);

#endif // ARM_WSPR_H_