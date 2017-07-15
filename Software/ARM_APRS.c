/*
 * ARM_APRS.c
 *
 * Created: 21.6.2016 11:41:32
 *  Author: Tomy2
 */ 

#include "sam.h"
#include "math.h"
#include "ARM_APRS.h"
#include "ARM_EEFC.h"


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
		buffer[num++] = (number / 91) + '!';
		buffer[num++] = (number % 91) + '!';
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
	
	SSDV packet in the Comment Field.
*/
void APRS_SSDV_packet(uint8_t *buffer, uint8_t *packet)
{
	buffer[num++] = '{';										// User-Defined APRS packet format
	//buffer[num++] = '{';										// Experimental (DL7AD)
	//buffer[num++] = 'I';										// Image (DL7AD)
	
	for(uint16_t i = 0; i < 50; i++) buffer[num++] = packet[i];
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
	uint16_t seq = (uint16_t)(sequence % 8281);					// handles the maximum value in case of the SEQUENCE counter
	
	buffer[num++] = '|';
	Base91_u16_2DEC_encode(seq, buffer);						// "SS" - sequence
	Base91_u16_2DEC_encode(value1, buffer);						// "AA" - value 1
	Base91_u16_2DEC_encode(value2, buffer);						// "AA" - value 2
	Base91_u16_2DEC_encode(value3, buffer);						// "AA" - value 3
	Base91_u16_2DEC_encode(value4, buffer);						// "AA" - value 4
	Base91_u16_2DEC_encode(value5, buffer);						// "AA" - value 5
	Base91_u16_2DEC_encode((uint16_t)bitfield, buffer);			// "DD" - 8 bit bitfield
	buffer[num++] = '|';
}


/*
	This and the following three APRS messages are tied to APRS TELEMETRY packets.
	They inform the receiver about the format of the values in telemetry packets.
	
	Contains information on what the values represent for the individual telemetry fields.
	
	Format: ":CALL-SSID:PARM."
	
	STRING: given the complexity of this message the information is passed as a string and needs to be constructed according to the rules
		example:	"Vsol,Vbatt,Tcpu,Sats,Nav"
		
	ADDRESSEE: must have 9 characters (fill the rest with 'space')
		example:	"OK7DMT-11"
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
		example:	"OK7DMT-11"
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
		example:	"0,0.0008,0,0,0.0016,0,0,0.304,-263,0,1,0,0,1,0"
	
	ADDRESSEE: must have 9 characters (fill the rest with 'space')
		example:	"OK7DMT-11"
	
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
		example:	"OK7DMT-11"
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
	Function to insert a historical backlog retrieved from the flash memory into the comment section of an APRS packet.
	It manages listing through the backlogs and holds the last read flash page in 'backlog_tx_pointer' (reset to 0 after MCU reset).
	
	The algorithm alternates between three modes.
		First it makes 3 jumps stepping 78 backlogs.
		Then does a next round of 8 jumps stepping 31 backlogs at a time.
		And at last it switches to 19 jumps of 13 backlogs stepped over.
	The reason is to alternate between quick overviews of the whole backlogged period and more detailed insight.
	Once the 'backlog_tx_pointer' reaches 240 it wraps around and returns to the beginning.
	
	In case of an empty backlog (it hasn't been written since the initial programming) the function adds just a ' ' space character.
	
	State after MCU reset:
		backlog_step		78
		backlog_step_count	3
	
	In case of ATSAM3S4:		EEFC_read_bytes(0x00430100 + (256 * backlog_tx_pointer), 28, backlog_buffer);
	In case of ATSAM3S8:		EEFC_read_bytes(0x00470100 + (256 * backlog_tx_pointer), 28, backlog_buffer);
*/
void APRS_comment_backlog(uint8_t *buffer)
{
	uint8_t backlog_buffer[28];
	
	if(!backlog_step_count)																// cycle through backlog step sizes
	{
		if(backlog_step == 78)		{backlog_step = 31; backlog_step_count = 8;}
		else if(backlog_step == 31)	{backlog_step = 13; backlog_step_count = 19;}
		else if(backlog_step == 13)	{backlog_step = 78; backlog_step_count = 3;}
	}
	backlog_step_count--;
	
	backlog_tx_pointer = (backlog_tx_pointer + backlog_step) % 240;						// calculate the current sequence
	
	EEFC_read_bytes(0x00470100 + (256 * backlog_tx_pointer), 28, backlog_buffer);		// get the desired backlog
	
	buffer[num++] = ' ';
	
	if(backlog_buffer[0] != 0xFF && backlog_buffer[1] != 0xFF)							// don't attach empty backlogs
	{
		for(uint8_t i = 0; i < 25; i++) buffer[num++] = backlog_buffer[i];				// insert the backlog in the APRS packet
	}
}


/*
	Creates an array of 25 bytes representing compressed telemetry.
	Encodes year(1), month(1), day(1), hour(1), minute(1), latitude(4), longitude(4), altitude(2), value1(2), value2(2), value3(2), value4(2), value5(2).
	
	Example:	0K#8=5MHyS(KbHH!!$F+E+V!*
	
	Decoding:
		year		=	2016 + (buffer[0] - 48)
		month		=	buffer[1] - 64
		day			=	buffer[2] - 33
		hour		=	buffer[3] - 33
		minute		=	buffer[4] - 33
		latitude	=	90.0 - ((buffer[5] - 33) * 753571 + (buffer[6] - 33) * 8281 + (buffer[7] - 33 ) * 91 + (buffer[8] - 33)) / 380926
		longitude	=	-180.0 + ((buffer[9] - 33) * 753571 + (buffer[10] - 33) * 8281 + (buffer[11] - 33 ) * 91 + (buffer[12] - 33)) / 190463
		altitude	=	1.002 ^ ((buffer[13] - 33) * 91 + (buffer[14] - 33)) * 0.3048
		value1		=	(buffer[15] - 33) * 91 + (buffer[16] - 33)
		value2		=	(buffer[17] - 33) * 91 + (buffer[18] - 33)
		value3		=	(buffer[19] - 33) * 91 + (buffer[20] - 33)
		value4		=	(buffer[21] - 33) * 91 + (buffer[22] - 33)
		value5		=	(buffer[23] - 33) * 91 + (buffer[24] - 33)
*/
void APRS_encode_backlog(uint8_t *buffer)
{
	uint32_t latitude = (uint32_t)((90.0f - APRSlatitude) * 380926.0f);
	uint32_t longitude = (uint32_t)((180.0f + APRSlongitude) * 190463.0f);
	uint16_t altitude = (uint16_t)(log((float)APRSaltitude * 3.28f) / log(1.002f)) % 8281;
	
	buffer[0] = (APRSyear - 2016) + '0';															// Year
	buffer[1] = APRSmonth + '@';																	// Month
	buffer[2] = APRSday + 33;																		// Day
	buffer[3] = APRShour + 33;																		// Hour
	buffer[4] = APRSminute + 33;																	// Minute
	buffer[5] = latitude / 753571 + 33;																// Latitude
	buffer[6] = (latitude % 753571) / 8281 + 33;
	buffer[7] = ((latitude % 753571) % 8281) / 91 + 33;
	buffer[8] = ((latitude % 753571) % 8281) % 91 + 33;
	buffer[9] = longitude / 753571 + 33;															// Longitude
	buffer[10] = (longitude % 753571) / 8281 + 33;
	buffer[11] = ((longitude % 753571) % 8281) / 91 + 33;
	buffer[12] = ((longitude % 753571) % 8281) % 91 + 33;
	buffer[13] = altitude / 91 + 33;																// Altitude
	buffer[14] = altitude % 91 + 33;
	buffer[15] = APRSvalue1 / 91 + 33;																// Value 1
	buffer[16] = APRSvalue1 % 91 + 33;
	buffer[17] = APRSvalue2 / 91 + 33;																// Value 2
	buffer[18] = APRSvalue2 % 91 + 33;
	buffer[19] = APRSvalue3 / 91 + 33;																// Value 3
	buffer[20] = APRSvalue3 % 91 + 33;
	buffer[21] = APRSvalue4 / 91 + 33;																// Value 4
	buffer[22] = APRSvalue4 % 91 + 33;
	buffer[23] = APRSvalue5 / 91 + 33;																// Value 5
	buffer[24] = APRSvalue5 % 91 + 33;
}


/*
	Every time it's called the function encodes current telemetry data to a 25 byte array and stores it inside the MCU's flash memory.
	Each backlog gets stored on one page of flash memory (256 bytes).
	The algorithm uses 240 pages then circulates back and overwrites the oldest logs.
	The number of the current page to write to is saved in flash on page 1792 (0x00470000).
	The backlog starts at page 1793 (0x00470100) and spans to page 2033 (0x0047F100).
	
		page	1792		0x00470000					backlog pointer		written every 1 hour (flash endurance min 416 days)
		pages	1793-2033	0x00470100-0x0047F100		240 backlogs		each written every 240 hours (flash endurance min 100000 days)
	
	This specific page selection is intended for SAM3S8B and its one plane 512kB flash memory.
	In case of using a different MCU (SAM3S4B for example) the page numbering has to be adjusted!
	
	ATSAM3S4 - one plane of 256kB, 1024 pages of 256 bytes
		page	768			0x00430000					backlog pointer		written every 1 hour (flash endurance min 416 days)
		pages	769-1009	0x00430100-0x0043F100		240 backlogs		each written every 240 hours (flash endurance min 100000 days)
*/
void APRS_store_backlog(void)
{
	uint8_t backlog_buffer[28];
	uint8_t pointer_buffer[4];
	
	APRS_encode_backlog(backlog_buffer);									// encode the current data
	
	EEFC_read_bytes(0x00470000, 4, pointer_buffer);							// get the number of the page to write to
	
	backlog_store_pointer = (pointer_buffer[0] << 24) |
	(pointer_buffer[1] << 16 |
	(pointer_buffer[2] << 8) |
	(pointer_buffer[3] << 0));
	
	if(backlog_store_pointer > 239) backlog_store_pointer = 0;				// the pointer reads 255 after initial programming
	
	EEFC_write_page(backlog_buffer, 28, 1793 + backlog_store_pointer);		// store the backlog in the flash memory
	
	backlog_store_pointer = (backlog_store_pointer + 1) % 240;				// point to the next position
	
	pointer_buffer[0] = backlog_store_pointer << 24;
	pointer_buffer[1] = backlog_store_pointer << 16;
	pointer_buffer[2] = backlog_store_pointer << 8;
	pointer_buffer[3] = backlog_store_pointer << 0;
	EEFC_write_page(pointer_buffer, 4, 1792);								// update the number of the page to write to next time
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
*/
void APRS_packet_construct(uint8_t *buffer)
{
	num = 0;
	
	
	// Flags
	for(uint32_t i = 0 ; i < APRSFLAGS; i++)
	{
		buffer[num++] = 0x7E;
	}
	
	
	// Destination Address
	for(uint8_t i = 0; i < 6; i++)
	{
		buffer[num++] = APRS_destination[i];
	}
	
	// SSID of the destination
	buffer[num++] = 0b01110000 | DSSID;							// 0b0CRRSSID (C - command/response bit '1', RR - reserved '11', SSID - 0-15)
	
	
	// Source Address
	for(uint8_t i = 0; i < 6; i++)
	{
		buffer[num++] = APRS_callsign[i];
	}
	
	// SSID to specify an APRS symbol (11 - balloon)
	buffer[num++] = 0b00110000 | (APRS_ssid & 0x0F);							// 0b0CRRSSID (C - command/response bit '1', RR - reserved '11', SSID - 0-15)
	
	
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
	else if(APRS_send_path == 4)								// WIDE2-2
	{
		buffer[num++] = 'W';
		buffer[num++] = 'I';
		buffer[num++] = 'D';
		buffer[num++] = 'E';
		buffer[num++] = '2';
		buffer[num++] = ' ';
		
		// SSID
		buffer[num++] = 0b00110010;								// 0b0HRRSSID (H - 'has been repeated' bit, RR - reserved '11', SSID - 0-15)
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
		// !/5MGoS(L_0GzW |!$!!#p+30n!!!"|												empty backlog
		// !/5MGoS(L_0GzW 0K%0/5MI6S(K^HW!!$>+a!*31|!$!!#p+30n!!!"|						with backlog
		
		buffer[num++] = '!';
		APRS_position_base91(buffer, APRSlatitude, APRSlongitude, (float)APRSaltitude, 1);
		APRS_comment_backlog(buffer);
		APRS_telemetry_base91(buffer, APRSsequence, APRSvalue1, APRSvalue2, APRSvalue3, APRSvalue4, APRSvalue5, APRSbitfield);
	}
	else if(APRS_packet_mode == 2)
	{
		APRS_telemetry_PARM(buffer, "Vsol,Vbatt,Tcpu,Ttx,Sats,Nav,Fix,Img,PSM", "OK7DMT-12");
	}
	else if(APRS_packet_mode == 3)
	{
		APRS_telemetry_UNIT(buffer, "V,V,C,C", "OK7DMT-12");
	}
	else if(APRS_packet_mode == 4)
	{
		APRS_telemetry_EQNS(buffer, "0,0.0008,0,0,0.0016,0,0,0.304,-263,0,0.222,-297,0,1,0", "OK7DMT-12");
	}
	else if(APRS_packet_mode == 5)
	{
		APRS_telemetry_BITS(buffer, "11111111,TT7F2 High Altitude Balloon SSDV 434.319MHz", "OK7DMT-12");
	}
	else if(APRS_packet_mode == 6)
	{
		buffer[num++] = '/';
		APRS_time_short(buffer, APRShour, APRSminute, APRSsecond);
		APRS_position_base91(buffer, APRSlatitude, APRSlongitude, (float)APRSaltitude, 1);
		APRS_telemetry_base91(buffer, APRSsequence, APRSvalue1, APRSvalue2, APRSvalue3, APRSvalue4, APRSvalue5, APRSbitfield);
	}
	else if(APRS_packet_mode == 7)
	{
		// !0000.00N\00000.00W. |!$!!#p+30n!!!"|										no position data, empty backlog
		// !0000.00N\00000.00W. 0K%0/5MI6S(K^HW!!$>+a!*31|!$!!#p+30n!!!"|				no position data, with backlog
		
		buffer[num++] = '!';
		APRS_comment(buffer, "0000.00N\\00000.00W.");
		APRS_comment_backlog(buffer);
		APRS_telemetry_base91(buffer, APRSsequence, APRSvalue1, APRSvalue2, APRSvalue3, APRSvalue4, APRSvalue5, APRSbitfield);
	}
	else // APRS_packet_mode == 0
	{
		buffer[num++] = '/';
		APRS_time_short(buffer, APRShour, APRSminute, APRSsecond);
		APRS_position_uncompressed(buffer, APRSlat_int, APRSlon_int, APRSlat_dec, APRSlon_dec, APRSlatNS, APRSlonEW, (uint32_t)APRSaltitude);
	}
	
	
	// Frame Check Sequence - CRC-16-CCITT (0xFFFF)
	uint16_t crc = 0xFFFF;
	for(uint16_t i = 0; i < (num - APRSFLAGS); i++) crc = crc_ccitt_update(crc, buffer[APRSFLAGS+i]);
	crc = ~crc;
	buffer[num++] = crc & 0xFF;									// FCS is sent low-byte first
	buffer[num++] = (crc >> 8) & 0xFF;							// and with the bits flipped
	
	
	// the end Flags
	buffer[num++] = 0x7E;
	buffer[num++] = 0x7E;
	buffer[num++] = 0x7E;
	
	APRS_packet_size = num;										// packet length
}


/*
	Allows changing callsign and ssid between transmissions.
*/
void APRS_fill_callsign(char *callsign, uint8_t ssid)
{
	for(uint8_t i = 0; i < 6; i++)
	{
		APRS_callsign[i] = callsign[i];
	}
	
	APRS_ssid = ssid & 0x0F;
}