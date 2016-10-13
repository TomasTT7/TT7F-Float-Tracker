/*
 * ARM_APRS.c
 *
 * Created: 21.6.2016 11:41:32
 *  Author: Tomy2
 */ 

#include "sam.h"
#include "math.h"
#include "ARM_APRS.h"


#define lo8(x) ((x)&0xff)
#define hi8(x) ((x)>>8)


/*
	Function to calculate the Frame Check Sequence (FCS) of the APRS packet. 
*/
uint16_t crc_ccitt_update(uint16_t crc, uint8_t data)
{
	data ^= lo8 (crc);
	data ^= data << 4;
	
	return ((((uint16_t)data << 8) | hi8 (crc)) ^ (uint8_t)(data >> 4) ^ ((uint16_t)data << 3));
}


/*
	Function to encode values (max 8280) to Base91 format for APRS telemetry.
*/
void Base91_u16_2DEC_encode(uint16_t number, uint8_t *buffer)
{
	if(number > 8280)											// maximum acceptable value
	{
		 buffer[num++] = '!';									// decoded as 0
		 buffer[num++] = '!';									// decoded as 0
	}else{
		buffer[num++] = (number / 91) + '0';
		buffer[num++] = (number % 91) + '0';
	}
}


/*
	Base91 uint32_t number encoder. Output number of characters dependent on the size of the number. 
*/
void Base91_u32_encode(uint32_t number, uint8_t *buffer)
{
	uint32_t temp = number;
	uint8_t part1 = 0;
	uint8_t part2 = 0;
	uint8_t part3 = 0;
	uint8_t part4 = 0;
	uint8_t part5 = 0;
	
	part1 = temp / 68574961;
	temp = temp % 68574961;
	part2 = temp / 753571;
	temp = temp % 753571;
	part3 = temp / 8281;
	temp = temp % 8281;
	part4 = temp / 91;
	part5 = temp % 91;
	
	if(number >= 68574961) buffer[num++] = part1 + '0';
	if(number >= 753571) buffer[num++] = part2 + '0';
	if(number >= 8281) buffer[num++] = part3 + '0';
	if(number >= 91) buffer[num++] = part4 + '0';
	buffer[num++] = part5 + '0';
}


/*
	Splits a uint8_t value to individual bits and fills 8 places in a buffer for APRS telemetry with correspondent ASCII characters.
*/
void ASCII_8bitfield_transmit_APRS(uint8_t number, uint8_t *buffer)
{
	buffer[num++] = ((number >> 7) & 0x01) + '0';				// bit 7
	buffer[num++] = ((number >> 6) & 0x01) + '0';				// bit 6
	buffer[num++] = ((number >> 5) & 0x01) + '0';				// bit 5
	buffer[num++] = ((number >> 4) & 0x01) + '0';				// bit 4
	buffer[num++] = ((number >> 3) & 0x01) + '0';				// bit 3
	buffer[num++] = ((number >> 2) & 0x01) + '0';				// bit 2
	buffer[num++] = ((number >> 1) & 0x01) + '0';				// bit 1
	buffer[num++] = ((number >> 0) & 0x01) + '0';				// bit 0
}


/*
	Converts a uint16_t value to ASCII characters. Output number of characters is dependent on the INTS parameter.
*/
void ASCII_16bit_transmit_APRS(uint16_t number, uint8_t *buffer, uint8_t ints)
{
	uint8_t ascii1 = 0;											// 16bit numbers - 5 decimal places max
	uint8_t ascii2 = 0;
	uint8_t ascii3 = 0;
	uint8_t ascii4 = 0;
	uint8_t ascii5 = 0;
	uint16_t numb = number;
	ascii1 = numb / 10000;
	numb = number;
	ascii2 = (numb - (ascii1 * 10000)) / 1000;
	numb = number;
	ascii3 = (numb - (ascii1 * 10000) - (ascii2 * 1000)) / 100;
	numb = number;
	ascii4 = (numb - (ascii1 * 10000) - (ascii2 * 1000) - (ascii3 * 100)) / 10;
	numb = number;
	ascii5 = (numb - (ascii1 * 10000) - (ascii2 * 1000) - (ascii3 * 100)) % 10;
	ascii1 += '0';
	ascii2 += '0';
	ascii3 += '0';
	ascii4 += '0';
	ascii5 += '0';
	if(ints == 5) buffer[num++] = ascii1;
	if(ints >= 4) buffer[num++] = ascii2;
	if(ints >= 3) buffer[num++] = ascii3;
	if(ints >= 2) buffer[num++] = ascii4;
	if(ints >= 1) buffer[num++] = ascii5;
	else buffer[num++] = 0;
}


/*
	Converts a uint16_t value to ASCII characters. Output number of characters is dependent on the size of the input value.
*/
void ASCII_16bit_transmit_APRS_auto(uint16_t number, uint8_t *buffer)
{
	uint8_t ascii1 = 0;											// 16bit numbers - 5 decimal places max
	uint8_t ascii2 = 0;
	uint8_t ascii3 = 0;
	uint8_t ascii4 = 0;
	uint8_t ascii5 = 0;
	uint16_t numb = number;
	ascii1 = numb / 10000;
	numb = number;
	ascii2 = (numb - (ascii1 * 10000)) / 1000;
	numb = number;
	ascii3 = (numb - (ascii1 * 10000) - (ascii2 * 1000)) / 100;
	numb = number;
	ascii4 = (numb - (ascii1 * 10000) - (ascii2 * 1000) - (ascii3 * 100)) / 10;
	numb = number;
	ascii5 = (numb - (ascii1 * 10000) - (ascii2 * 1000) - (ascii3 * 100)) % 10;
	ascii1 += '0';
	ascii2 += '0';
	ascii3 += '0';
	ascii4 += '0';
	ascii5 += '0';
	if(number >= 10000) buffer[num++] = ascii1;
	if(number >= 1000) buffer[num++] = ascii2;
	if(number >= 100) buffer[num++] = ascii3;
	if(number >= 10) buffer[num++] = ascii4;
	buffer[num++] = ascii5;
}


/*
	Function to convert uint32_t value to ASCII characters of the decimal part of Latitude and Longitude (2 chars) or Altitude (6 chars).
	Used in the uncompressed position APRS packet.
	
	ALTITUDE:		'0' for lat_dec/lon_dec			'1' for altitude
*/
void ASCII_32bit_LATLON_transmit_APRS(uint32_t number, uint8_t *buffer, uint8_t altitude)
{
	uint8_t ascii1 = 0;											// 32bit numbers - 10 decimal places max
	uint8_t ascii2 = 0;
	uint8_t ascii3 = 0;
	uint8_t ascii4 = 0;
	uint8_t ascii5 = 0;
	uint8_t ascii6 = 0;
	uint8_t ascii7 = 0;
	uint8_t ascii8 = 0;
	uint8_t ascii9 = 0;
	uint8_t ascii10 = 0;
	uint16_t num1 = number % 1000;
	uint16_t num2 = ((number % 1000000) - num1) / 1000;
	uint16_t num3 = ((number % 1000000000) - num1 - num2) / 1000000;
	uint16_t num4 = number / 1000000000;
	ascii1 = num4;
	ascii2 = num3 / 100;
	ascii3 = (num3 - (ascii2 * 100)) / 10;
	ascii4 = (num3 - (ascii2 * 100)) % 10;
	ascii5 = num2 / 100;
	ascii6 = (num2 - (ascii5 * 100)) / 10;
	ascii7 = (num2 - (ascii5 * 100)) % 10;
	ascii8 = num1 / 100;
	ascii9 = (num1 - (ascii8 * 100)) / 10;
	ascii10 = (num1 - (ascii8 * 100)) % 10;
	ascii1 += '0';
	ascii2 += '0';
	ascii3 += '0';
	ascii4 += '0';
	ascii5 += '0';
	ascii6 += '0';
	ascii7 += '0';
	ascii8 += '0';
	ascii9 += '0';
	ascii10 += '0';
	//buffer[num++] = ascii4;
	if(altitude)
	{
		buffer[num++] = ascii5;
		buffer[num++] = ascii6;
		buffer[num++] = ascii7;
		buffer[num++] = ascii8;
		buffer[num++] = ascii9;
		buffer[num++] = ascii10;
	}else{
		buffer[num++] = ascii6;
		buffer[num++] = ascii7;
	}
}


/*
	Experimental packet.
*/
void APRS_base91_SSDV_encode(uint8_t *BASE91buffer, uint8_t *SSDVpacket)
{
	uint32_t numb = 0;
	uint32_t z = 0;
	
	for(uint8_t i = 0; i < 64; i++)
	{
		numb = 0;
		numb = (SSDVpacket[i*4] << 24) | (SSDVpacket[i*4+1] << 16) | (SSDVpacket[i*4+2] << 8) | SSDVpacket[i*4+3];
		BASE91buffer[z++] = (uint8_t)(numb / 68574961) + 33;
		BASE91buffer[z++] = (uint8_t)((numb % 68574961) / 753571) + 33;
		BASE91buffer[z++] = (uint8_t)(((numb % 68574961) % 753571) / 8281) + 33;
		BASE91buffer[z++] = (uint8_t)((((numb % 68574961) % 753571) % 8281) / 91) + 33;
		BASE91buffer[z++] = (uint8_t)((((numb % 68574961) % 753571) % 8281) % 91) + 33;
	}
}


/*
	Experimental packet.
*/
void APRS_SSDV_packet(uint8_t *buffer, uint8_t *packet)
{
	// SSDV packet in the Comment Field
	
	buffer[num++] = '{';										// User-Defined APRS packet format
	//buffer[num++] = '{';										// Experimental (DL7AD)
	//buffer[num++] = 'I';										// Image (DL7AD)
	
	for(uint16_t i = 0; i < 50; i++) buffer[num++] = packet[i];
	//for(uint16_t i = 33; i < 62; i++) buffer[num++] = i;
	//for(uint16_t i = 63; i < 95; i++) buffer[num++] = i;
	//for(uint16_t i = 96; i < 124; i++) buffer[num++] = i;
}


/*
	Format: "HHMMSSh"
*/
void APRS_time_short(uint8_t *buffer, uint8_t hour, uint8_t minute, uint8_t second)
{
	buffer[num++] = (hour / 10) + '0';
	buffer[num++] = (hour % 10) + '0';
	buffer[num++] = (minute / 10) + '0';
	buffer[num++] = (minute % 10) + '0';
	buffer[num++] = (second / 10) + '0';
	buffer[num++] = (second % 10) + '0';
	buffer[num++] = 'h';										// 'h' designates 24h GMT
}


/*
	Format: "DDHHMMz"
*/
void APRS_time_mid(uint8_t *buffer, uint8_t hour, uint8_t minute, uint8_t day)
{
	buffer[num++] = (day / 10) + '0';
	buffer[num++] = (day % 10) + '0';
	buffer[num++] = (hour / 10) + '0';
	buffer[num++] = (hour % 10) + '0';
	buffer[num++] = (minute / 10) + '0';
	buffer[num++] = (minute % 10) + '0';
	buffer[num++] = 'z';										// 'z' designates 24h ZULU (UTC)
}


/*
	Format: "MMDDhhmm"
*/
void APRS_time_long(uint8_t *buffer, uint8_t hour, uint8_t minute, uint8_t month, uint8_t day)
{
	buffer[num++] = (month / 10) + '0';
	buffer[num++] = (month % 10) + '0';
	buffer[num++] = (day / 10) + '0';
	buffer[num++] = (day % 10) + '0';
	buffer[num++] = (hour / 10) + '0';
	buffer[num++] = (hour % 10) + '0';
	buffer[num++] = (minute / 10) + '0';
	buffer[num++] = (minute % 10) + '0';
}


/*
	Uncompressed format:	"YYYY.YYy/XXXXX.XXxO/A=FFFFFF"
	Default Null Position:	"0000.00N\00000.00W."				(\.	symbol for unknown/indeterminate position)
	
	Latitude and Longitude in degrees and decimal minutes (to two decimal places) format.
	Latitude and Longitude are separated by a display Symbol Table Identifier '/' and followed by a Symbol Code 'O' designating a balloon.
	Altitude in Comment Text in the form "/A=FFFFFF" in feet.
*/
void APRS_position_uncompressed(uint8_t *buffer, uint16_t lat_int, uint16_t lon_int, uint32_t lat_dec,
								uint32_t lon_dec, uint8_t NS, uint8_t EW, uint32_t alt)
{
	ASCII_16bit_transmit_APRS(lat_int, buffer, 4);				// Latitude
	buffer[num++] = '.';
	ASCII_32bit_LATLON_transmit_APRS(lat_dec, buffer, 0);
	
	if(NS == 0) buffer[num++] = 'S';							// South / North
	else if(NS == 1) buffer[num++] = 'N';
	else buffer[num++] = '?';
	
	buffer[num++] = '/';										// Symbol Table Identifier
	
	ASCII_16bit_transmit_APRS(lon_int, buffer, 5);				// Longitude
	buffer[num++] = '.';
	ASCII_32bit_LATLON_transmit_APRS(lon_dec, buffer, 0);
	
	if(EW == 0) buffer[num++] = 'W';							// East / West
	else if(EW == 1) buffer[num++] = 'E';
	else buffer[num++] = '?';
	
	buffer[num++] = 'O';										// Symbol Code for Balloon
	
	uint32_t altitude = alt * 328;								// Altitude - has to be in the Comment Text and in feet
	altitude /= 100;
	
	buffer[num++] = '/';
	buffer[num++] = 'A';
	buffer[num++] = '=';
	ASCII_32bit_LATLON_transmit_APRS(altitude, buffer, 1);		// doesn't do negative altitude (don't know the APRS format for that)
}


/*
	Position compressed in Base91 format. The result is ASCII characters between 33-124 (! through |).
	
	Compressed Format: "/YYYYXXXXOcsT"
	
	LAT:	float input degrees in decimal format
	LON:	float input degrees in decimal format
	ALT:	float input in meters
	
	SHOWALT:	'0'	don't show		'1'	show altitude in B91 encoded position
	
	"cs"	Can instead of altitude optionally contain Course/Speed or Pre-calculated Radio Range information.
	
	Can be used in '!', '/', '@' and '=' message formats.
	Compressed format can be used in place of lat/long position format anywhere that ...ddmm.hhN/dddmm.hhW$xxxxxxx... occurs.
	The presence of the leading Symbol Table Identifier instead of a digit indicates that this is a compressed Position Report
	and not a normal lat/long report.
*/
void APRS_position_base91(uint8_t *buffer, float lat, float lon, float alt, uint8_t showAlt)
{
	lat = (90.0f - lat) * 380926.0f;
	lon = (180.0f + lon) * 190463.0f;
	alt = log((float)alt * 3.28f) / log(1.002f);
	alt = (uint16_t)alt % 8281;
		
	buffer[num++] = '/';										// the Symbol Table Identifier
	
	buffer[num++] = (lat / 753571) + 33;						// Latitude
	lat = (uint32_t)lat % 753571;
	buffer[num++] = (lat / 8281) + 33;
	lat = (uint32_t)lat % 8281;
	buffer[num++] = (lat / 91) + 33;
	buffer[num++] = ((uint32_t)lat % 91) + 33;
	
	buffer[num++] = (lon / 753571) + 33;						// Longitude
	lon = (uint32_t)lon % 753571;
	buffer[num++] = (lon / 8281) + 33;
	lon = (uint32_t)lon % 8281;
	buffer[num++] = (lon / 91) + 33;
	buffer[num++] = ((uint32_t)lon % 91) + 33;
	
	buffer[num++] = 'O';										// the Symbol Code (Balloon)
	
	if(showAlt)
	{
		buffer[num++] = (alt / 91) + 33;						// Altitude
		buffer[num++] = ((uint16_t)alt % 91) + 33;
		buffer[num++] = 0x57;									// the Compression Type Identifier - 00110110 -> 54 + 33 -> 0x57 'W'
	}else{
		buffer[num++] = ' ';									// if 'c' byte is space ' ', csT bytes are ignored
		buffer[num++] = ' ';
		buffer[num++] = ' ';
	}
}


/*
	Uncompressed Format: "T#XXX,111,222,333,444,555,BBBBBBBB"
	
	Input should be int16_t to preserve negative/positive sign. Function handles this.
	
	First option is to use negative values and transmit the negative sign as well.
	Second option is to send the original ADC readings (always positive) and let the ":CALL-SSID:EQNS." message inform
	the receiver on the format of the sent values and how to calculate the actual value.
*/
void APRS_telemetry_uncompressed(uint8_t *buffer, uint16_t sequence, int16_t value1, int16_t value2,
									int16_t value3, int16_t value4, int16_t value5, uint8_t bitfield)
{
	buffer[num++] = 'T';										// APRS Data Type Identifier (Telemetry Data)
	buffer[num++] = '#';
	
	ASCII_16bit_transmit_APRS_auto(sequence, buffer);			// "XXX" - sequence
	buffer[num++] = ',';
	
	if(value1 < 0)												// "111" - value 1
	{
		buffer[num++] = '-';
		value1 = 65535 - value1 + 1;
	}
	ASCII_16bit_transmit_APRS_auto((uint16_t)value1, buffer);	
	buffer[num++] = ',';
	
	if(value2 < 0)												// "222" - value 2
	{
		buffer[num++] = '-';
		value2 = 65535 - value2 + 1;
	}
	ASCII_16bit_transmit_APRS_auto((uint16_t)value2, buffer);	
	buffer[num++] = ',';
	
	if(value3 < 0)												// "333" - value 3
	{
		buffer[num++] = '-';
		value3 = 65535 - value3 + 1;
	}
	ASCII_16bit_transmit_APRS_auto((uint16_t)value3, buffer);	
	buffer[num++] = ',';
	
	if(value4 < 0)												// "444" - value 4
	{
		buffer[num++] = '-';
		value4 = 65535 - value4 + 1;
	}
	ASCII_16bit_transmit_APRS_auto((uint16_t)value4, buffer);	
	buffer[num++] = ',';
	
	if(value5 < 0)												// "555" - value 5
	{
		buffer[num++] = '-';
		value5 = 65535 - value5 + 1;
	}
	ASCII_16bit_transmit_APRS_auto((uint16_t)value5, buffer);
	buffer[num++] = ',';
	
	ASCII_8bitfield_transmit_APRS(bitfield, buffer);			// "BBBBBBBB" - 8 bit bitfield
}


/*
	Compressed Format: "|SSAAAAAAAAAADD|"
	
	Maximum Value:	8280
	
	Doesn't handle negative values. Input values greater than 8280 are output as '!!' which corresponds to '00' after decode.
*/
void APRS_telemetry_base91(uint8_t *buffer, uint32_t sequence, uint16_t value1, uint16_t value2,
							uint16_t value3, uint16_t value4, uint16_t value5, uint8_t bitfield)
{
	uint16_t seq = sequence & 0x1FFF;							// handles the maximum value in case of the SEQUENCE counter
	
	buffer[num++] = '|';
	Base91_u16_2DEC_encode(seq, buffer);						// "SS" - sequence
	Base91_u16_2DEC_encode(value1, buffer);						// "AA" - value 1
	Base91_u16_2DEC_encode(value2, buffer);						// "AA" - value 2
	Base91_u16_2DEC_encode(value3, buffer);						// "AA" - value 3
	Base91_u16_2DEC_encode(value4, buffer);						// "AA" - value 4
	Base91_u16_2DEC_encode(value5, buffer);						// "AA" - value 5
	Base91_u16_2DEC_encode(bitfield, buffer);					// "DD" - 8 bit bitfield
	buffer[num++] = '|';
}


/*
	This and the following three APRS messages are tied to APRS TELEMETRY packets.
	They inform the receiver about the format of the values in telemetry packets.
	
	Contains information on what the values represent for the individual telemetry fields.
	
	Format: ":CALL-SSID:PARM."
	
	STRING: given the complexity of this message the information is passed as a string and needs to be constructed according to the rules
		example:	"Vsolar,Vbatt,Tcpu,Sats,-"
		
	ADDRESSEE: must have 9 characters (fill the rest with 'space')
		example:	"OK7DMT-0 "
*/
void APRS_telemetry_PARM(uint8_t *buffer, char *string, char *addressee)
{
	buffer[num++] = ':';
	
	for(uint8_t i = 0; i < 9; i++)								// Addressee
	{
		buffer[num++] = *addressee++;
	}
		
	buffer[num++] = ':';
	buffer[num++] = 'P';
	buffer[num++] = 'A';
	buffer[num++] = 'R';
	buffer[num++] = 'M';
	buffer[num++] = '.';
	
	while(*string)
	{
		buffer[num++] = *string++;
	}
}


/*
	Contains the UNITS for the individual telemetry fields.
	
	Format: ":CALL-SSID:UNIT."
	
	STRING: given the complexity of this message the information is passed as a string and needs to be constructed according to the rules
		example:	"V,V,C,n,-"
	
	ADDRESSEE: must have 9 characters (fill the rest with 'space')
		example:	"OK7DMT-0 "
*/
void APRS_telemetry_UNIT(uint8_t *buffer, char *string, char *addressee)
{
	buffer[num++] = ':';
	
	for(uint8_t i = 0; i < 9; i++)								// Addressee
	{
		buffer[num++] = *addressee++;
	}
	
	buffer[num++] = ':';
	buffer[num++] = 'U';
	buffer[num++] = 'N';
	buffer[num++] = 'I';
	buffer[num++] = 'T';
	buffer[num++] = '.';
	
	while(*string)
	{
		buffer[num++] = *string++;
	}
}


/*
	Contains the coefficients and offsets to adjust the values of individual telemetry fields.
	
	Format: ":CALL-SSID:EQNS."
	
	STRING: given the complexity of this message the information is passed as a string and needs to be constructed according to the rules
		example:	"0,0.0008,0,0,0.0016,0,0,0.304,-273.15,0,1,0,0,1,0"
	
	ADDRESSEE: must have 9 characters (fill the rest with 'space')
		example:	"OK7DMT-0 "
	
	APRS Message Format is defined to be 1 byte (identifier), 9 bytes (addressee), 1 byte (identifier) and 0-67 bytes (message text).
	However, in this case a 54 byte EQNS. message did not get decoded while a 51 byte one did. No difference in message structure.
*/
void APRS_telemetry_EQNS(uint8_t *buffer, char *string, char *addressee)
{
	buffer[num++] = ':';
	
	for(uint8_t i = 0; i < 9; i++)								// Addressee
	{
		buffer[num++] = *addressee++;
	}
	
	buffer[num++] = ':';
	buffer[num++] = 'E';
	buffer[num++] = 'Q';
	buffer[num++] = 'N';
	buffer[num++] = 'S';
	buffer[num++] = '.';
	
	while(*string)
	{
		buffer[num++] = *string++;
	}
}


/*
	Contains the information on the polarity (whether '0' or '1' signals active) of the bits in the bitfield and the name of the project.
	
	Format: ":CALL-SSID:BITS."
	
	STRING: given the complexity of this message the information is passed as a string and needs to be constructed according to the rules
		example:	"11111111,TT7F High Altitude Balloon"
	
	ADDRESSEE: must have 9 characters (fill the rest with 'space')
		example:	"OK7DMT-0 "
*/
void APRS_telemetry_BITS(uint8_t *buffer, char *string, char *addressee)
{
	buffer[num++] = ':';
	
	for(uint8_t i = 0; i < 9; i++)								// Addressee
	{
		buffer[num++] = *addressee++;
	}
	
	buffer[num++] = ':';
	buffer[num++] = 'B';
	buffer[num++] = 'I';
	buffer[num++] = 'T';
	buffer[num++] = 'S';
	buffer[num++] = '.';
	
	while(*string)
	{
		buffer[num++] = *string++;
	}
}


/*
	Function to add a STRING to the APRS packet. Can be used to add comments or the whole message instead of using the other functions.
*/
void APRS_comment(uint8_t *buffer, char *string)
{
	while(*string)
	{
		buffer[num++] = *string++;
	}
}


/*
	Function to add altitude (meters) in to the comment section of a packet.
*/
void APRS_comment_altitude(uint8_t *buffer, uint32_t alt)
{
	
	uint32_t altitude = alt * 328;								// Altitude will be expressed in feet (input is in meters)
	altitude /= 100;
	
	buffer[num++] = '/';
	buffer[num++] = 'A';
	buffer[num++] = '=';
	ASCII_32bit_LATLON_transmit_APRS(altitude, buffer, 1);		// doesn't do negative altitude (don't know the APRS format for that)
}


/*
	The main PACKET constructor. Fills a buffer with all the individual parts of the APRS packet ready to be transmitted.
		Inserts the 0x7E FLAGS.
		Adds DESTINATION and SOURCE ADDRESSES with their SSIDs.
		Optionally adds PATH 'WIDE2-1'.
		Left shifts the address and path bytes and adds '1' at the end to signal the end of address fields.
		Adds CONTROL FIELD byte 0x03.
		And PROTOCOL ID byte 0xF0 as well.
		Constructs the selected INFORMATION FIELD
		Calculates the FRAME CHECK SEQUENCE and appends it to the end of the packet.
		Adds three 0x7E FLAGS to signal the end of the packet.
	
	DESTINATION ADDRESSES
		APDSXX		SP9UOB for dsDigi and ds-tracker
		APDWxx		DireWolf, WB2OSZ
		APECAN		Pecan Pico APRS Balloon Tracker
		APNxxx		Network nodes, digis, etc
		APRS		Generic, (Obsolete. Digis should use APNxxx instead.)
		APSTMx		W7QO's Balloon Trackers
	
	APRS PATH EXAMPLES
		WIDE1-1						One hop			(Any digi will respond to this.)
		WIDE2-1						One hop			(Only true wides respond to this.)
		WIDE1-1,WIDE2-1				Two hops		(Today's recommended universal mobile setting.)
		WIDE1-1,WIDE2-2				Three hops
		WIDE3-3						Three hops
		WIDE1-1,WIDE3-3				Four hops		(Don't do this!)
		WIDE1-1,WIDE3-1				Two hops		(Same as WIDE1-1,WIDE2-1.)
		WIDE2-2,WIDE2-2,WIDE2-2		Six hops		(Network abuse.)
		WIDE1-1,WIDE2-2,WIDE7-7		Ten hops		(Network abuse.)
		WIDE2-1,WIDE1-1				Two hops		(Each mountain top that hears the first hop, can potentially trigger dozens "down below".)
		
	APRS  DATA TYPE IDENTIFIERS
		!	Position without timestamp (no APRS messaging)
		/	Position with timestamp (no APRS messaging)
		=	Position without timestamp (with APRS messaging)
		@	Position with timestamp (with APRS messaging)
		T	Telemetry data
		:	Message
		>	Status
		_	Weather Report (without position)
		‘	Current Mic-E Data (not used in TM-D700)
		{	User-Defined APRS packet format
	
	APRS DATA
		Position.
		Time and Position.
		Telemetry.
		
	APRS DATA EXTENSIONS
		Course and Speed.												CSE/SPD
		Wind Direction and Wind Speed.									DIR/SPD
		Station Power and Effective Antenna Height/Gain/Directivity.	PHGphgd
		Pre-Calculated Radio Range.										RNGrrrr
		DF Signal Strength and Effective Antenna Height/Gain.			DFSshgd
		Area Object Descriptor.											Tyy/Cxx
	
	COMMENT FIELD
		Any APRS packet can contain a plain text comment.
		No separator between the APRS data and the comment.
		May contain any printable ASCII characters (except | and ~ which are reserved for TNC channel switching).
	
	APRS SYMBOLS
		Information Field			4903.50N/07201.75W>		'/' Primary Symbol Table	'>' car symbol
		Destination Address			GPSMV3					'MV' car symbol				'3' with number 3 overlay
		Source Address SSID			G3NRW-11				'11' balloon symbol
		
		Conflicting symbols in Information Field and Destination Address led to NO DECODE.
	
	
	
	WORKING FORMATS
		"/HHMMSShYYYY.YYy/XXXXX.XXxO/A=FFFFFFcomment"					(timestamp, uncompressed position, altitude, comment)
		"/HHMMSSh/YYYYXXXXOAAWcomment"									(timestamp, base91 position, comment)
		"/DDHHMMzYYYY.YYy/XXXXX.XXxO/A=FFFFFF"							(timestampD, uncompressed position, altitude)
		"/DDHHMMz/YYYYXXXXOAAW"											(timestampD, base91 position)
		":call-SSID:PARM."												(telemetry parameters)
		":call-SSID:UNIT."												(telemetry units)
		":call-SSID:EQNS."												(telemetry equations)
		":call-SSID:BITS."												(telemetry bits and message)
		"T#SSS,val1,val2,val3,val4"										(uncompressed telemetry)
		"/HHMMSSh/YYYYXXXXO   /A=FFFFFF"								(timestamp, base91 position, altitude in comment)
		"/HHMMSSh/YYYYXXXXO   /A=FFFFFFT#SSS,val1,val2,val3,val4"		(timestamp, base91 position, altitude in comment, telemetry in comment - unparsed)
	
	FORMATS THAT DIDN'T DECODE
		"!YYYY.YYy/XXXXX.XXxO/A=FFFFFF|SSAAAAAAAAAADD|"					(without timestamp, uncompressed position, altitude, base91 telemetry)
		"!/YYYYXXXXOAAW|SSAAAAAAAAAADD|"								(without timestamp, base91 position, base91 telemetry)
		"!YYYYXXXXOAAW"													(without timestamp, base91 position without Symbol Table Identifier)
		"!/YYYYXXXXOAAW"												(without timestamp, base91 position)
		"!YYYY.YYy/XXXXX.XXxO/A=FFFFFF"									(without timestamp, uncompressed position)
		"!/YYYYXXXXOAAW/|SSAAAAAAAAAADD|"								(without timestamp, base91 position, added '/', base91 telemetry)
		"/HHMMSSh/YYYYXXXXOAAW|SSAAAAAAAAAADD|"							(timestamp, base91 position, base91 telemetry)
		"/HHMMSShYYYY.YYy/XXXXX.XXxO/A=FFFFFF|ssaaaaaaaaaadd|"			(timestamp, uncompressed position, altitude, base91 telemetry)
		"/MMDDhhmmYYYY.YYy/XXXXX.XXxO/A=FFFFFF"							(timestampMD, uncompressed position, altitude)
		"/MMDDhhmm/YYYYXXXXOAAW"										(timestampMD, base91 position)
		"/HHMMSSh/YYYYXXXXOAAWcomment|SSAAAAAAAAAADD|"					(timestamp, base91 position, comment, base91 telemetry)
		"/HHMMSShYYYY.YYy/XXXXX.XXxO/A=FFFFFFcomment|ssaaaaaaaaaadd|"	(timestamp, uncompressed position, altitude, comment, base91 telemetry)
		"/HHMMSSh/YYYYXXXXOAAW/comment|SSAAAAAAAAAADD|"					(timestamp, base91 position, /comment, base91 telemetry)
		"/HHMMSShYYYY.YYy/XXXXX.XXxO/A=FFFFFF/comment|ssaaaaaaaaaadd|"	(timestamp, uncompressed position, altitude, /comment, base91 telemetry)
*/
void APRS_packet_construct(uint8_t *buffer)
{
	num = 0;
	
	// Flags
	for(uint8_t i = 0 ; i < APRSFLAGS; i++)
	{
		buffer[num++] = 0x7E;
	}
	
	// Destination Address
	for(uint8_t i = 0; i < 6; i++)
	{
		buffer[num++] = APRS_destination[i];
	}
	
	// SSID of the destination
	buffer[num++] = 0b00110000 | DSSID;							// 0b0CRRSSID (C - command/response bit '1', RR - reserved '11', SSID - 0-15)
	
	// Source Address
	for(uint8_t i = 0; i < 6; i++)
	{
		buffer[num++] = APRS_callsign[i];
	}
	
	// SSID to specify an APRS symbol (11 - balloon)
	buffer[num++] = 0b01110000 | SSID;							// 0b0CRRSSID (C - command/response bit '1', RR - reserved '11', SSID - 0-15)
	
	// Path
	if(APRS_send_path == 1)										// WIDE1-1
	{
		buffer[num++] = 'W';
		buffer[num++] = 'I';
		buffer[num++] = 'D';
		buffer[num++] = 'E';
		buffer[num++] = '1';									
		buffer[num++] = ' ';
	
		// SSID
		buffer[num++] = 0b00110001;								// 0b0HRRSSID (H - 'has been repeated' bit, RR - reserved '11', SSID - 0-15)
	}
	else if(APRS_send_path == 2)								// WIDE2-1
	{
		buffer[num++] = 'W';
		buffer[num++] = 'I';
		buffer[num++] = 'D';
		buffer[num++] = 'E';
		buffer[num++] = '2';
		buffer[num++] = ' ';
		
		// SSID
		buffer[num++] = 0b00110001;								// 0b0HRRSSID (H - 'has been repeated' bit, RR - reserved '11', SSID - 0-15)
	}
	else if(APRS_send_path == 3)								// WIDE1-1, WIDE2-1
	{
		buffer[num++] = 'W';
		buffer[num++] = 'I';
		buffer[num++] = 'D';
		buffer[num++] = 'E';
		buffer[num++] = '1';
		buffer[num++] = ' ';
		
		// SSID
		buffer[num++] = 0b00110001;								// 0b0HRRSSID (H - 'has been repeated' bit, RR - reserved '11', SSID - 0-15)
		
		buffer[num++] = 'W';
		buffer[num++] = 'I';
		buffer[num++] = 'D';
		buffer[num++] = 'E';
		buffer[num++] = '2';
		buffer[num++] = ' ';
		
		// SSID
		buffer[num++] = 0b00110001;								// 0b0HRRSSID (H - 'has been repeated' bit, RR - reserved '11', SSID - 0-15)
	}
	
	// Left Shifting the Address Bytes
	for(uint16_t i = APRSFLAGS; i < num; i++)
	{
		buffer[i] <<= 1;
		if(i == (num - 1)) buffer[i] |= 0x01;					// the last byte's LSB set to '1' to indicate the end of the address fields
	}
	
	// Control Field
	buffer[num++] = 0x03;
	
	// Protocol ID
	buffer[num++] = 0xF0;
	
	// Information Field
	/*
		APRS Data Type Identifier	1 byte		
		APRS Data					n bytes		
		APRS Data Extension			7 bytes		
		Comment						n bytes		
	*/
	if(APRS_packet_mode == 1)
	{
		APRS_comment(buffer, "/210048h4916.54N/01814.58EO");				// DECODED
	}
	else if(APRS_packet_mode == 2)
	{
		APRS_comment(buffer, "!4903.50N/07201.75W-Test /A=001234");			// NOTHING
	}
	else if(APRS_packet_mode == 3)
	{
		APRS_comment(buffer, "=4903.50N/07201.75W#PHG5132");				// NOTHING
	}
	else if(APRS_packet_mode == 4)
	{
		APRS_comment(buffer, "@092345/4903.50N/07201.75W>Test1234");		// NOTHING
	}
	else if(APRS_packet_mode == 5)
	{
		APRS_comment(buffer, "[IO91SX]");									// DECODED (unknown message type)
	}
	else if(APRS_packet_mode == 6)
	{
		APRS_telemetry_PARM(buffer, "Vsolar,Vbatt,Tcpu,Sats,-", "OK7DMT-11");
	}
	else if(APRS_packet_mode == 7)
	{
		APRS_telemetry_UNIT(buffer, "V,V,C,n,-", "OK7DMT-11");
	}
	else if(APRS_packet_mode == 8)
	{
		APRS_telemetry_EQNS(buffer, "0,0.0008,0,0,0.0016,0,0,0.304,-274,0,1,0,0,1,0", "OK7DMT-11");
	}
	else if(APRS_packet_mode == 9)
	{
		APRS_telemetry_BITS(buffer, "11111111,TT7F High Altitude Balloon", "OK7DMT-11");
	}
	else if(APRS_packet_mode == 10)
	{
		APRS_comment(buffer, "$GPGGA,102705,5157.9762,N,00029.3256,W,1,04,2.0,75.7,M,47.6,M,,*62");
	}
	else if(APRS_packet_mode == 11)
	{
		APRS_comment(buffer, "=/5L!!<*e7OS]S");
	}
	else if(APRS_packet_mode == 12)
	{
		APRS_comment(buffer, "@092345z/5L!!<*e7>{?!");
	}
	else if(APRS_packet_mode == 13)
	{
		APRS_comment(buffer, "!/5L!!<*e7OS]S");
	}
	else if(APRS_packet_mode == 14)
	{
		APRS_comment(buffer, "/092345z/5L!!<*e7>{?!");
	}
	else if(APRS_packet_mode == 15)
	{
		APRS_comment(buffer, ";LEADER   *092345z4903.50N/07201.75W>088/036");
	}
	else if(APRS_packet_mode == 16)
	{
		APRS_comment(buffer, ";LEADER   *092345z/5L!!<*e7>7P[");
	}
	else if(APRS_packet_mode == 17)
	{
		APRS_comment(buffer, ")AID #2!4903.50N/07201.75WA");
	}
	else if(APRS_packet_mode == 18)
	{
		APRS_comment(buffer, ")MOBIL!\5L!!<*e79VsT");
	}
	else if(APRS_packet_mode == 19)
	{
		APRS_comment(buffer, "$ULTW0031003702CE0069----000086A00001----011901CC00000005");
	}
	else if(APRS_packet_mode == 20)
	{
		APRS_comment(buffer, "_10090556c220s004g005t077r000p000P000h50b09900wRSW");
	}
	else if(APRS_packet_mode == 21)
	{
		APRS_comment(buffer, "!4903.50N/07201.75W_220/004g005t077r000p000P000h50b09900wRSW");
	}
	else if(APRS_packet_mode == 22)
	{
		APRS_comment(buffer, "@092345z4903.50N/07201.75W_220/004g005t-07r000p000P000h50b09900wRSW");
	}
	else if(APRS_packet_mode == 23)
	{
		APRS_comment(buffer, "T#005,199,000,255,073,123,01101001");
	}
	else if(APRS_packet_mode == 24)
	{
		APRS_comment(buffer, "{Q1qwerty");
	}
	else if(APRS_packet_mode == 25)
	{
		APRS_comment(buffer, "{{zasdfg");
	}
	else if(APRS_packet_mode == 26)
	{
		APRS_comment(buffer, ",191146,V,4214.2466,N,07303.5181,W,417.238,114.5,091099,14.7,W/GPS FIX");
	}
	else if(APRS_packet_mode == 27)
	{
		APRS_comment(buffer, "!4952.05N/00838.28E#MultimodeRelais DA 438.587MHz www.f42.info");
	}
	else // APRS_packet_mode == 0
	{
		
	}
	
	// Frame Check Sequence - CRC-16-CCITT (0xFFFF)
	uint16_t crc = 0xFFFF;
	for(uint16_t i = 0; i < (num - APRSFLAGS); i++) crc = crc_ccitt_update(crc, buffer[APRSFLAGS+i]);
	crc = ~crc;
	buffer[num++] = crc & 0xFF; // FCS is sent low-byte first
	buffer[num++] = (crc >> 8) & 0xFF; // and with the bits flipped
		
	// the end Flags
	buffer[num++] = 0x7E;
	buffer[num++] = 0x7E;
	buffer[num++] = 0x7E;
	
	APRS_packet_size = num; // packet length
}