/*
	
*/

#include "sam3s8b.h"
#include "ARM_DELAY.h"
#include "ARM_WSPR.h"
#include "ARM_SI5351.h"
#include "ARM_WATCHDOG.h"
#include "nhash.h"


/*
	CALLSIGN may be up to 6 characters (A-Z, 0-9 and ' ').
	Values allocated to the characters are 0-9 for '0'-'9', 10-35 for 'A'-'Z' and 36 for ' '.
	Encoded into 28 bits.
*/
uint32_t WSPR_encode_callsign(uint8_t * call)
{
	uint8_t i = 0;
	uint32_t result = 0;

	// first character can be any of the 37 values
	if(call[0] > '9') result = call[0] - 55;
	else result = call[0] - 48;

	// second character can be only one of 36 values (can't be ' ')
	if(call[1] > '9') result = result * 36 + (call[1] - 55);
	else result = result * 36 + (call[1] - 48);

	// third character must be a number
	result = result * 10 + (call[2] - 48);

	// the remaining characters can't be numbers so only one of 27 values
	for(i = 3; i < 6; i++)
	{
		result = result * 27 + (call[i] - 55 - 10);
	}
  
	return result;
}


/*
	Encodes the 6-digit LOCATOR which was already byte shifted in place of the CALLSIGN. 
	JN99bl -> N99blJ
*/
uint32_t WSPR_encode_callsign_extended(uint8_t * call)
{
	uint8_t i = 0;
	uint32_t result = 0;
	
	result = call[0] - 55;
	result = result * 36 + (call[1] - 48);
	result = result * 10 + (call[2] - 48);
	result = result * 27 + (call[3] - 55) - 10;
	result = result * 27 + (call[4] - 55) - 10;
	result = result * 27 + (call[5] - 55) - 10;

	return result;
}


/*
	LOCATOR is 4 characters. First two A-Z, last two 0-9.
	Values allocated to the first pair are 0-17 for A-Z and 0-9 for the second pair.
	Encoded into 15 bits.
*/
uint32_t WSPR_encode_locator(uint8_t * locator)
{
	uint32_t result = 0;
	
	result = (179 - 10 * (locator[0] - 65) - (locator[2] - 48)) * 180 + 10 * (locator[1] - 65) + (locator[3] - 48);
	
	return result;
}


/*
	The power field in TT7F's WSPR message represents the tracker's rough altitude.
	
		0		0-1000m
		3		1000-1999m
		7		2000-2999m
		10		3000-3999m
		13		4000-4999m
		17		5000-5999m
		20		6000-6999m
		23		7000-7999m
		27		8000-8999m
		30		9000-9999m
		33		10000-10999m
		37		11000-11999m
		40		12000-12999m
		43		13000-13999m
		47		14000-14999m
		50		15000-15999m
		53		16000-16999m
		57		17000-17999m
		60		>18000m
*/
uint8_t WSPR_encode_power(uint32_t altitude)
{
	uint8_t n = altitude / 1000;
	
	if(n >= 18) return powerVals[18];
	else return powerVals[n];
}


/*
	The rough altitude is refined via the power field of the extended message.
	Add this amount of meters to the km estimate from the basic message.
	
	OK7DMT JN99 37		->	11000-11999m
	+
	<OK7DMT> JN99bl 10	->	11159-11211m
	
		0		0-52m
		3		53-105m
		7		106-158m
		10		159-211m
		13		212-264m
		17		265-317m
		20		318-370m
		23		371-423m
		27		424-476m
		30		477-529m
		33		530-582m
		37		583-635m
		40		636-688m
		43		689-741m
		47		742-794m
		50		795-847m
		53		848-900m
		57		901-953m
		60		954-999m
		
	Altitude higher than 18999 always sent as 60 and 60 -> 18999m.
*/
uint8_t WSPR_encode_power_extended(uint32_t altitude)
{
	uint8_t n = (altitude % 1000) / 53;
	
	if(n >= 18) return powerVals[18];
	else return powerVals[n];
}


/*
	Encodes the standard WSPR message: OK7DMT JN99 30
	Allocates the MESSAGE bits to single array and appends FEC bits.
*/
void WSPR_encode_msg(float lat, float lon, uint32_t alt, uint8_t * callsign)
{
	for(uint8_t i = 0 ; i < 6; i++) WSPRcallsign[i] = callsign[i];
	
	GPS_to_Maidenhead(lat, lon);
	
	uint32_t N = WSPR_encode_callsign(WSPRcallsign);
	uint32_t M = WSPR_encode_locator(WSPRlocator) * 128 + WSPR_encode_power(alt) + 64;
	
	// Actual Message
	WSPRbits[0] = (N & 0x0FF00000) >> 20;
	WSPRbits[1] = (N & 0x000FF000) >> 12;
	WSPRbits[2] = (N & 0x00000FF0) >> 4;
	WSPRbits[3] = ((N & 0x0000000F) << 4) | ((M & 0x003C0000) >> 18);
	WSPRbits[4] = (M & 0x0003FC00) >> 10;
	WSPRbits[5] = (M & 0x000003FC) >> 2;
	WSPRbits[6] = (M & 0x00000003) << 6;
	WSPRbits[7] = 0;
	WSPRbits[8] = 0;
	WSPRbits[9] = 0;
	WSPRbits[10] = 0;
	
	// Forward Error Correction
	uint32_t FECval0 = 0xF2D05351;
	uint32_t FECval1 = 0xE4613C47;
	uint32_t FECreg = 0;
  
	uint8_t i = 0;
	uint8_t x = 0;

	for(i = 0; i < 81; i++)
	{
		uint8_t temp = WSPRbits[i/8] >> (7 - (i % 8));
		FECreg = (FECreg << 1) | (temp & 0x01);

		uint32_t FECparity0 = FECreg & 0xF2D05351;
		uint32_t FECparity1 = FECreg & 0xE4613C47;
    
		uint8_t parBit0 = 0;
		uint8_t parBit1 = 0;

		while(FECparity0 != 0)
		{
			parBit0++;
			FECparity0 = FECparity0 & (FECparity0 - 1);
		}
    
		while(FECparity1 != 0)
		{
			parBit1++;
			FECparity1 = FECparity1 & (FECparity1 - 1);
		}
    
		WSPRmsg[x++] = parBit0 & 0x01;
		WSPRmsg[x++] = parBit1 & 0x01;
	}
}


/*
	Encodes the extended WSPR message: <OK7DMT> JN99bl 30
	Based on: https://github.com/Guenael/airspy-wsprd/blob/master/wsprsim_utils.c
*/
void WSPR_encode_msg_extended(float lat, float lon, uint32_t alt, uint8_t * callsign)
{
	for(uint8_t i = 0 ; i < 6; i++) WSPRcallsign[i] = callsign[i];
	
	uint32_t ihash = nhash(WSPRcallsign, 6, 146);											// computes the HASH of the callsign
	
	GPS_to_Maidenhead(lat, lon);															// constructs the 6-digit LOCATOR
	
	uint8_t locator6[6];																	// LOCATOR is shifted by one byte
	locator6[0] = WSPRlocator[1];
	locator6[1] = WSPRlocator[2];
	locator6[2] = WSPRlocator[3];
	locator6[3] = WSPRlocator[4];
	locator6[4] = WSPRlocator[5];
	locator6[5] = WSPRlocator[0];
	
	uint32_t N = WSPR_encode_callsign_extended(locator6);									// 6-digit LOCATOR is encoded as CALLSIGN
	uint32_t M = ihash * 128 - (WSPR_encode_power_extended(alt) + 1) + 64;					// CALLSIGN HASH is encoded with POWER
	
	// Actual Message
	WSPRbits[0] = (N & 0x0FF00000) >> 20;
	WSPRbits[1] = (N & 0x000FF000) >> 12;
	WSPRbits[2] = (N & 0x00000FF0) >> 4;
	WSPRbits[3] = ((N & 0x0000000F) << 4) | ((M & 0x003C0000) >> 18);
	WSPRbits[4] = (M & 0x0003FC00) >> 10;
	WSPRbits[5] = (M & 0x000003FC) >> 2;
	WSPRbits[6] = (M & 0x00000003) << 6;
	WSPRbits[7] = 0;
	WSPRbits[8] = 0;
	WSPRbits[9] = 0;
	WSPRbits[10] = 0;
	
	// Forward Error Correction
	uint32_t FECval0 = 0xF2D05351;
	uint32_t FECval1 = 0xE4613C47;
	uint32_t FECreg = 0;
  
	uint8_t i = 0;
	uint8_t x = 0;

	for(i = 0; i < 81; i++)
	{
		uint8_t temp = WSPRbits[i/8] >> (7 - (i % 8));
		FECreg = (FECreg << 1) | (temp & 0x01);

		uint32_t FECparity0 = FECreg & 0xF2D05351;
		uint32_t FECparity1 = FECreg & 0xE4613C47;
    
		uint8_t parBit0 = 0;
		uint8_t parBit1 = 0;

		while(FECparity0 != 0)
		{
			parBit0++;
			FECparity0 = FECparity0 & (FECparity0 - 1);
		}
    
		while(FECparity1 != 0)
		{
			parBit1++;
			FECparity1 = FECparity1 & (FECparity1 - 1);
		}
    
		WSPRmsg[x++] = parBit0 & 0x01;
		WSPRmsg[x++] = parBit1 & 0x01;
	}
}


/*
	Interleaves and merges the WSPRmsg with WSPRsync.
	FEC tackles random errors better then a burst of errors. Hence the algorithm moves away adjacent bits.
*/
void WSPR_create_tones(void)
{
	uint8_t P = 0;
	uint8_t I = 0;
	uint8_t J = 0;
	uint8_t h = 0;
	uint16_t g = 0;
  
	for(g = 0; g < 256; g++)
	{
		I = g;
		J = 0;
		
		for(h = 0; h < 8; h++)
		{
			J <<= 1;
			if(I & 1) J = J | 1;
			I >>= 1;
		}

		if(J < 162)
		{
			WSPRtones[J] = WSPRsync[J] + 2 * WSPRmsg[P];
			P++;
		}
	}
}


/*
	Transmits the 162 tones corresponding to the encoded WSPR message.
*/
void WSPR_transmit(void)
{
  uint8_t Tone = 0;

  SI5351_start_TX();
  
  for(Tone = 0; Tone < 162; Tone++)
  {
    WATCHDOG_restart();														// whole transmission takes 110.6s, watchdog period is only 16s
	
	switch(WSPRtones[Tone])
    {
      case 0:
        SI5351_MS0_frequency(SI5351frequency001Hz);							// 0.001 Hz, Tone 0
        break;
      case 1:
        SI5351_MS0_frequency(SI5351frequency001Hz + 1465);					// 0.001 Hz, Tone 1
        break;
      case 2:
        SI5351_MS0_frequency(SI5351frequency001Hz + 2930);					// 0.001 Hz, Tone 2
        break;
      case 3:
        SI5351_MS0_frequency(SI5351frequency001Hz + 4394);					// 0.001 Hz, Tone 3
        break;
      default:
        break;
    }
    SysTick_delay_ms(683);
  }

  SI5351_stop_TX();
}


/*
	Converts decimal degree GPS coordinates to Maidenhead symbols.
	Result gets stored in WSPRlocator[].
*/
void GPS_to_Maidenhead(float lat, float lon)
{
	uint32_t result;

	lon += 180;
	lat += 90;

	uint32_t lon32 = lon * 10000;
	uint32_t lat32 = lat * 10000;

	result = lon32 / 200000;
	WSPRlocator[0] = field[result];
	result = lat32 / 100000;
	WSPRlocator[1] = field[result];

	result = (lon32 % 200000) / 20000;
	WSPRlocator[2] = square[result];
	result = (lat32 % 100000) / 10000;
	WSPRlocator[3] = square[result];

	result = ((lon32 % 200000) % 20000) / 834;
	WSPRlocator[4] = subsquare[result];
	result = ((lat32 % 100000) % 10000) / 417;
	WSPRlocator[5] = subsquare[result];
}