/*
 * ARM_UBLOX.c
 *
 * Created: 20.6.2016 23:24:32
 *  Author: Tomy2
 */ 

#include "sam.h"
#include "ARM_UBLOX.h"
#include "ARM_UART.h"
#include "ARM_DELAY.h"
#include "ARM_ADC.h"
#include <stdlib.h>


/*
	Cyclic Redundancy Check function used in CRC16_checksum().
*/
uint16_t crc_xmodem_update(uint16_t crc, uint8_t data)
{
	int i;
	crc = crc ^ ((uint16_t)data << 8);
	for (i=0; i<8; i++)
	{
		if (crc & 0x8000) crc = (crc << 1) ^ 0x1021;
		else crc <<= 1;
	}
	return crc;
}


/*
	RTTY telemetry CRC calculation. String input. Calculation starts on the data after the initial '$' dollar sings.
*/
uint16_t CRC16_checksum(uint8_t *string, uint32_t len, uint32_t start)
{
	uint32_t i;
	uint16_t crc;
	uint8_t c;
	crc = 0xFFFF;
	for(i=start; i < len; i++)
	{
		c = string[i];
		crc = crc_xmodem_update(crc, c);
	}
	return crc;
}


/*
	Function to convert an 8-bit number to ASCII characters. Output length depends on the size of the input number.
	
	8bit number		3 digits max
*/
uint32_t ASCII_8bit_transmit(uint8_t number, uint8_t *buffer, uint32_t sequence)
{
	uint8_t ascii1 = 0;
	uint8_t ascii2 = 0;
	uint8_t ascii3 = 0;
	uint16_t num1 = number;
	ascii1 = num1 / 100;
	ascii2 = (num1 - (ascii1 * 100)) / 10;
	ascii3 = (num1 - (ascii1 * 100)) % 10;
	ascii1 += '0';
	ascii2 += '0';
	ascii3 += '0';
	if(number >= 100) buffer[sequence++] = ascii1;
	if(number >= 10) buffer[sequence++] = ascii2;
	buffer[sequence++] = ascii3;
	
	return sequence;
}


/*
	Function to convert an 8-bit number to ASCII characters. Output length fixed to minimum 2 characters.
	
	8bit number		3 digits max
*/
uint32_t ASCII_8bit_2DEC_transmit(uint8_t number, uint8_t *buffer, uint32_t sequence)
{
	uint8_t ascii1 = 0;
	uint8_t ascii2 = 0;
	uint8_t ascii3 = 0;
	uint16_t num1 = number;
	ascii1 = num1 / 100;
	ascii2 = (num1 - (ascii1 * 100)) / 10;
	ascii3 = (num1 - (ascii1 * 100)) % 10;
	ascii1 += '0';
	ascii2 += '0';
	ascii3 += '0';
	if(number >= 100) buffer[sequence++] = ascii1;
	buffer[sequence++] = ascii2;
	buffer[sequence++] = ascii3;
	
	return sequence;
}


/*
	Function to convert a 16-bit number to ASCII characters. Output length depends on the size of the input number.
	
	16bit number		5 digits max
*/
uint32_t ASCII_16bit_transmit(uint16_t number, uint8_t *buffer, uint32_t sequence)
{
	uint8_t ascii1 = 0;
	uint8_t ascii2 = 0;
	uint8_t ascii3 = 0;
	uint8_t ascii4 = 0;
	uint8_t ascii5 = 0;
	uint16_t num = number;
	ascii1 = num / 10000;
	num = number;
	ascii2 = (num - (ascii1 * 10000)) / 1000;
	num = number;
	ascii3 = (num - (ascii1 * 10000) - (ascii2 * 1000)) / 100;
	num = number;
	ascii4 = (num - (ascii1 * 10000) - (ascii2 * 1000) - (ascii3 * 100)) / 10;
	num = number;
	ascii5 = (num - (ascii1 * 10000) - (ascii2 * 1000) - (ascii3 * 100)) % 10;
	ascii1 += '0';
	ascii2 += '0';
	ascii3 += '0';
	ascii4 += '0';
	ascii5 += '0';
	if(number >= 10000) buffer[sequence++] = ascii1;
	if(number >= 1000) buffer[sequence++] = ascii2;
	if(number >= 100) buffer[sequence++] = ascii3;
	if(number >= 10) buffer[sequence++] = ascii4;
	buffer[sequence++] = ascii5;
	
	return sequence;
}


/*
	Function to convert a 16-bit number to ASCII characters in HEX form. Output length fixed to four characters.
	
	16bit number		4 hexadecimal digits max
*/
uint32_t ASCII_16bit_HEX_transmit(uint16_t number, uint8_t *buffer, uint32_t sequence)
{
	uint8_t ascii1 = 0;
	uint8_t ascii2 = 0;
	uint8_t ascii3 = 0;
	uint8_t ascii4 = 0;
	uint16_t num = number;
	ascii4 = num % 16;
	if(ascii4 > 9) ascii4 = (ascii4 % 10) + 'A';
	else ascii4 += '0';
	num = number / 16;
	ascii3 = num % 16;
	if(ascii3 > 9) ascii3 = (ascii3 % 10) + 'A';
	else ascii3 += '0';
	num = number / 256;
	ascii2 = num % 16;
	if(ascii2 > 9) ascii2 = (ascii2 % 10) + 'A';
	else ascii2 += '0';
	ascii1 = number / 4096;
	if(ascii1 > 9) ascii1 = (ascii1 % 10) + 'A';
	else ascii1 += '0';
	buffer[sequence++] = ascii1;
	buffer[sequence++] = ascii2;
	buffer[sequence++] = ascii3;
	buffer[sequence++] = ascii4;
	
	return sequence;
}


/*
	Function to convert a 32-bit number to ASCII characters. Output length depends on the size of the input number.
	
	32bit number		10 digits max
*/
uint32_t ASCII_32bit_transmit(uint32_t number, uint8_t *buffer, uint32_t sequence)
{
	uint8_t ascii1 = 0;
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
	if(number >= 1000000000) buffer[sequence++] = ascii1;
	if(number >= 100000000) buffer[sequence++] = ascii2;
	if(number >= 10000000) buffer[sequence++] = ascii3;
	if(number >= 1000000) buffer[sequence++] = ascii4;
	if(number >= 100000) buffer[sequence++] = ascii5;
	if(number >= 10000) buffer[sequence++] = ascii6;
	if(number >= 1000) buffer[sequence++] = ascii7;
	if(number >= 100) buffer[sequence++] = ascii8;
	if(number >= 10) buffer[sequence++] = ascii9;
	buffer[sequence++] = ascii10;
	
	return sequence;
}


/*
	Function to convert a 32-bit number to ASCII characters used specifically for the decimal part of longitude and latitude.
	Output is fixed to 5 characters to ensure proper filling of '0' after the decimal point.
	Input can be up to 7 digits with the output cutting off the last two digits.
	
	UBX			int32_t DEGREES (1e-7)
	NMEA		4915.69566 01817.56412 (5 decimal places)
	PUBX		4915.695661 01817.564128 (6 decimal places)
*/
uint32_t ASCII_32bit_LATLON_DECIMAL_transmit(uint32_t number, uint8_t *buffer, uint32_t sequence, uint8_t figures)
{
	uint8_t ascii1 = 0;
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
	
	if(figures == 5)
	{
		buffer[sequence++] = ascii6;
		buffer[sequence++] = ascii7;
		buffer[sequence++] = ascii8;
		buffer[sequence++] = ascii9;
		buffer[sequence++] = ascii10;
	}
	else if(figures == 6)
	{
		buffer[sequence++] = ascii5;
		buffer[sequence++] = ascii6;
		buffer[sequence++] = ascii7;
		buffer[sequence++] = ascii8;
		buffer[sequence++] = ascii9;
		buffer[sequence++] = ascii10;
	}
	else if(figures == 7)
	{
		buffer[sequence++] = ascii4;
		buffer[sequence++] = ascii5;
		buffer[sequence++] = ascii6;
		buffer[sequence++] = ascii7;
		buffer[sequence++] = ascii8;
		buffer[sequence++] = ascii9;
		buffer[sequence++] = ascii10;
	}
	
	return sequence;
}


/*
	Converts GPS coordinates in Degrees and Decimal Minutes (4928.08702) to Decimal Degrees (49.4681170).
	
		PARAMETER		INPUT
		lat_INT			4 digits max
		lat_DEC			5 digits fixed
		lon_INT			5 digits max
		lon_DEC			5 digits fixed
		latNS			1/0
		lonEW			1/0
	
	The result is saved in global variables APRSLatitude and APRSLongitude.
*/
void Coords_DEGtoDEC(uint32_t lat_INT, uint32_t lat_DEC, uint32_t lon_INT, uint32_t lon_DEC, uint8_t latNS, uint8_t lonEW)
{
	/*
		lat_INT		4928	degrees, minutes
		lat_DEC		08702	minutes decimal value
		lon_INT		01805	degrees, minutes
		lon_DEC		46513	minutes decimal value
		latNS		0/1		S/N
		lonEW		0/1		W/E
	*/
	
	float lat = 0.0;
	float lon = 0.0;
	
	uint32_t deg = lat_INT / 100;								// 49
	uint32_t min = lat_INT % 100;								// 28
	min = (min * 100000) + lat_DEC;								// 2808702
	float minf = min / 100000.0;								// 28.08702
	minf = minf * 100 / 60;										// 46.8117
	min = minf * 100000.0;										// 4681170
	lat = (deg * 10000000) + min;								// 494681170
	
	deg = lon_INT / 100;										// 18
	min = lon_INT % 100;										// 05
	min = (min * 100000) + lon_DEC;								// 546513
	minf = min / 100000.0;										// 5.46513
	minf = minf * 100 / 60;										// 9.10855
	min = minf * 100000.0;										// 910855
	lon = (deg * 10000000) + min;								// 180910855
	
	
	if(!latNS) lat = lat * -1.0;
	if(!lonEW) lon = lon * -1.0;
	
	lon_DEC = (labs(lon) % 10000000) / 100;						// just in case I wanted to save this format to a global variable as well
	lon_INT = abs(lon / 10000000);								// just in case I wanted to save this format to a global variable as well
	lat_DEC = (labs(lat) % 10000000) / 100;						// just in case I wanted to save this format to a global variable as well
	lat_INT = abs(lat / 10000000);								// just in case I wanted to save this format to a global variable as well
	
	GPS_UBX_latitude_Float = (float)lat / 10000000.0;			// save to a global variable
	GPS_UBX_longitude_Float = (float)lon / 10000000.0;			// save to a global variable
}


/*
	Verifies the checksum of received UBX messages.
*/
uint8_t UBLOX_verify_checksum(volatile uint8_t *buffer, uint8_t len)
{
	uint8_t CRC;
	uint8_t CK_A_real = buffer[len-2];
	uint8_t CK_B_real = buffer[len-1];
	uint8_t CK_A_comp = 0;
	uint8_t CK_B_comp = 0;
	
	for(uint8_t i = 2; i < len-2; i++)
	{
		CK_A_comp = CK_A_comp + buffer[i];
		CK_B_comp = CK_A_comp + CK_B_comp;
	}
	
	if(CK_A_real == CK_A_comp && CK_B_real == CK_B_comp) CRC = 1;
	else CRC = 0;

	return CRC;
}


/*
	Waits for the UART1_RX_buffer[] to be filled with an expected number of bytes
	and then empties the buffer to a desired buffer for further processing.
*/
uint8_t UBLOX_fill_buffer_UBX(uint8_t *buffer, uint8_t len)
{
	uint32_t timeout = 500000;									// decreased for 2MHz PLL operation to 500000 (increase 10x for 64MHz PLL)
	uint32_t pos = UART1_buffer_pointer;

	while(UART1_buffer_pointer < (pos + len) && timeout) timeout--;
	
	if(!timeout) return 0;
	
	uint8_t bytes = UART1_buffer_pointer;
	for(uint8_t i = 0; i < bytes; i++)
	{
		buffer[i] = UART1_RX_buffer[i];
	}
	
	return 1;
}


/*
	Waits for the UART1_RX_buffer[] to contain an NMEA message terminated by the '\n' character
	and then empties the buffer to a desired buffer for further processing.
*/
uint8_t UBLOX_fill_buffer_NMEA(uint8_t *buffer)
{
	uint32_t timeout = 5000000;

	while(UART1_RX_buffer[UART1_buffer_pointer - 1] != '\n' && timeout) timeout--;
	
	if(!timeout)
	{
		GPS_NMEA_error_bitfield |= (1 << 0);
		return 0;
	}
	
	uint8_t bytes = UART1_buffer_pointer;
	for(uint8_t i = 0; i < bytes; i++)
	{
		buffer[i] = UART1_RX_buffer[i];
	}
	
	return 1;
}


/*
	Transmits a desired UBX message across UART1.
*/
void UBLOX_send_message(uint8_t *message, uint8_t len)
{
	for(uint8_t i = 0; i < len; i++)
	{
		UART1_TX(message[i]);
	}
	UART1_buffer_pointer = 0;
}


/*
	Function polling desired GPS data. It first sends the set UBX request.
	Then waits for the data and calls the appropriate parsing function.
*/
uint8_t UBLOX_request_UBX(uint8_t *request, uint8_t len, uint8_t expectlen, void (*parse)(volatile uint8_t*))
{
	for(uint8_t i = 0; i < len; i++)							// send the request
	{
		UART1_TX(*request++);
	}
	
	UART1_buffer_pointer = 0;									// reset UART1 RX buffer pointer
	
	uint8_t ack = UBLOX_fill_buffer_UBX(GPSbuffer, expectlen);	// copy the response from UART1_RX_buffer to GPSbuffer
	
	if(!ack) return 0;
	
	parse(GPSbuffer);											// parse the response to appropriate variables
	
	return 1;
}


/*
	UBX 01 02	POSITION
	
		GPS_UBX_longitude				494681170		+/-
		GPS_UBX_latitude				180910855		+/-
		GPS_UBX_longitude_Float			49.4681170		+/-
		GPS_UBX_latitude_Float			18.0910855		+/-
		GPSaltitude						403				+/-
		
	Checks the header and the checksum.
*/
void UBLOX_parse_0102(volatile uint8_t *buffer)
{
	GPS_UBX_error_bitfield |= (1 << 2);
	
	if(buffer[0] == 0xB5 && buffer[1] == 0x62 && buffer[2] == 0x01 && buffer[3] == 0x02)
	{
		if(UBLOX_verify_checksum(buffer, 36))
		{
			GPS_UBX_longitude = (int32_t)buffer[10] | (int32_t)buffer[11] << 8 | (int32_t)buffer[12] << 16 | (int32_t)buffer[13] << 24;
			GPS_UBX_longitude_Float = (float)GPS_UBX_longitude / 10000000.0;
			
			GPS_UBX_latitude = (int32_t)buffer[14] | (int32_t)buffer[15] << 8 | (int32_t)buffer[16] << 16 | (int32_t)buffer[17] << 24;
			GPS_UBX_latitude_Float = (float)GPS_UBX_latitude / 10000000.0;
			
			GPSaltitude = (int32_t)buffer[22] | (int32_t)buffer[23] << 8 | (int32_t)buffer[24] << 16 | (int32_t)buffer[25] << 24;
			GPSaltitude /= 1000;
			
			GPS_UBX_error_bitfield &= ~(1 << 2);
		}else{
			GPS_UBX_checksum_error++;
		}
	}else{
		GPS_UBX_buffer_error++;
	}
}


/*
	UBX 01 21	TIME
		
		GPShour				9
		GPSminute			14
		GPSsecond			55
		
	Checks the header and the checksum.
*/
void UBLOX_parse_0121(volatile uint8_t *buffer)
{
	GPS_UBX_error_bitfield |= (1 << 3);
	
	if(buffer[0] == 0xB5 && buffer[1] == 0x62 && buffer[2] == 0x01 && buffer[3] == 0x21)
	{
		if(UBLOX_verify_checksum(buffer, 28))
		{
			GPShour = buffer[22];
			GPSminute = buffer[23];
			GPSsecond = buffer[24];
			
			GPS_UBX_error_bitfield &= ~(1 << 3);
		}else{
			GPS_UBX_checksum_error++;
		}
	}else{
		GPS_UBX_buffer_error++;
	}
}


/*
	UBX 01 06	SATS & FIX
		
		GPSsats				7
		GPSfix				0x00		No Fix
							0x01		Dead Reckoning only
							0x02		2D-Fix
							0x03		3D-Fix
							0x04		GPS + Dead Reckoning combined
							0x05		Time only fix
		
	Checks the header and the checksum.
*/
void UBLOX_parse_0106(volatile uint8_t *buffer)
{
	if(buffer[0] == 0xB5 && buffer[1] == 0x62 && buffer[2] == 0x01 && buffer[3] == 0x06)
	{
		if(UBLOX_verify_checksum(buffer, 60))
		{
			GPSfix = buffer[16];
			GPSsats = buffer[53];
		}else{
			GPS_UBX_checksum_error++;
			
			GPSfix = 0;
			GPSsats = 0;
		}
	}else{
		GPS_UBX_buffer_error++;
		
		GPSfix = 0;
		GPSsats = 0;
	}
}


/*
	UBX 06 24	NAVIGATION MODE
	
		GPSnavigation		0	portable
							2	stationary
							3	pedestrian
							4	automotive
							5	sea
							6	airborne with <1g acceleration
							7	airborne with <2g acceleration
							8	airborne with <4g acceleration
							9	wrist worn watch
	
	Checks the header and the checksum.
*/
void UBLOX_parse_0624(volatile uint8_t *buffer)
{
	if(buffer[0] == 0xB5 && buffer[1] == 0x62 && buffer[2] == 0x06 && buffer[3] == 0x24)
	{
		if(UBLOX_verify_checksum(buffer, 44))
		{
			GPSnavigation = buffer[8];
		}else{
			GPS_UBX_checksum_error++;
			
			GPSnavigation = 0;
		}
	}else{
		GPS_UBX_buffer_error++;
		
		GPSnavigation = 0;
	}
}


/*
	UBX 06 11	POWER SAVE MODE
		
		GPSpowermode		0	Continuous Mode
							1	Power Save Mode
							4	Continuous Mode
	
	Checks the header and the checksum.
*/
void UBLOX_parse_0611(volatile uint8_t *buffer)
{
	GPS_UBX_error_bitfield |= (1 << 4);
	
	if(buffer[0] == 0xB5 && buffer[1] == 0x62 && buffer[2] == 0x06 && buffer[3] == 0x11)
	{
		if(UBLOX_verify_checksum(buffer, 10))
		{
			GPSpowermode = buffer[7];
			
			GPS_UBX_error_bitfield &= ~(1 << 4);
		}else{
			GPS_UBX_checksum_error++;
			
			GPSpowermode = 0;
		}
	}else{
		GPS_UBX_buffer_error++;
		
		GPSpowermode = 0;
	}
}


/*
	UBX 01 07	EVERYTHING
	
		GPSyear						2016
		GPSmonth					10
		GPSday						18
		GPShour						9
		GPSminute					14
		GPSsecond					55
		GPSfix						3
		GPSpowersavemodestate		0	PSM is not active
									1	Enabled (an intermediate state before Acquisition state)
									2	Acquisition
									3	Tracking
									4	Power Optimized Tracking
									5	Inactive
		GPSsats						7
		GPS_UBX_latitude			494681170		+/-
		GPS_UBX_longitude			180910855		+/-
		GPS_UBX_longitude_Float		49.4681170		+/-
		GPS_UBX_latitude_Float		18.0910855		+/-
		GPSaltitude					403				+/-
		GPSgroundspeed				10000			+/-
		GPSheading					2545641			+/-
	
	Checks the header and the checksum.
	UBLOX 7 message is shorter then UBLOX 8 message. It must be reflected in the checksum verification.
*/
void UBLOX_parse_0107(volatile uint8_t *buffer)
{
	GPS_UBX_error_bitfield |= (1 << 2);
	
	if(buffer[0] == 0xB5 && buffer[1] == 0x62 && buffer[2] == 0x01 && buffer[3] == 0x07)
	{
		if(UBLOX_verify_checksum(buffer, 92) || UBLOX_verify_checksum(buffer, 100))
		{
			// YEAR, MONTH, DAY
			GPSyear = (uint16_t)buffer[10] | (uint16_t)buffer[11] << 8;
			GPSmonth = buffer[12];
			GPSday = buffer[13];
			
			// HOUR, MINUTE, SECONDS
			GPShour = buffer[14];
			GPSminute = buffer[15];
			GPSsecond = buffer[16];
			
			// FIX
			GPSfix = buffer[26];
			GPSfix_0107 = buffer[27] & 0x01;
			GPSvalidity = buffer[17];
			
			// POWER SAVE MODE STATE
			GPSpowersavemodestate = (buffer[27] >> 2) & 0x07;
			
			// SATS
			GPSsats = buffer[29];
			
			// LONGITUDE, LATITUDE, ALTITUDE ABOVE MEAN SEA LEVEL
			GPS_UBX_longitude = (int32_t)buffer[30] | (int32_t)buffer[31] << 8 | (int32_t)buffer[32] << 16 | (int32_t)buffer[33] << 24;
			GPS_UBX_longitude_Float = (float)GPS_UBX_longitude / 10000000.0;
			
			GPS_UBX_latitude = (int32_t)buffer[34] | (int32_t)buffer[35] << 8 | (int32_t)buffer[36] << 16 | (int32_t)buffer[37] << 24;
			GPS_UBX_latitude_Float = (float)GPS_UBX_latitude / 10000000.0;
			
			GPSaltitude = (int32_t)buffer[42] | (int32_t)buffer[43] << 8 | (int32_t)buffer[44] << 16 | (int32_t)buffer[45] << 24;
			GPSaltitude /= 1000;
			
			// GROUND SPEED, HEADING
			GPSgroundspeed = (int32_t)buffer[66] | (int32_t)buffer[67] << 8 | (int32_t)buffer[68] << 16 | (int32_t)buffer[69] << 24;
			GPSheading = (int32_t)buffer[70] | (int32_t)buffer[71] << 8 | (int32_t)buffer[72] << 16 | (int32_t)buffer[73] << 24;;
			
			GPS_UBX_error_bitfield &= ~(1 << 2);
		}else{
			GPS_UBX_checksum_error++;
			
			GPSfix = 0;
			GPSsats = 0;
		}
	}else{
		GPS_UBX_buffer_error++;
		
		GPSfix = 0;
		GPSsats = 0;
	}
}


/*
	UBX 05 01	ACK
	
	Checks the header and the checksum.
*/
void UBLOX_parse_ACK(volatile uint8_t *buffer)
{
	if(buffer[0] == 0xB5 && buffer[1] == 0x62 && buffer[2] == 0x05)
	{
		if(buffer[3] != 0x01)
		{
			GPS_UBX_ack_error++;
		}
	}else{
		GPS_UBX_buffer_error++;
	}
}


/*
	Dummy parse function.
*/
void UBLOX_parse_empty(void)
{
	
}


/*
	Processes and parses an NMEA GGA message located in the input buffer.
	Accepts both GPGGA and GNGGA messages.
		
		GPShour						15
		GPSminute					30
		GPSsecond					43
		GPS_NMEA_latitude_int		4928
		GPS_NMEA_latitude_dec		00456
		GPS_NMEA_longitude_int		01815
		GPS_NMEA_longitude_dec		58561
		GPS_NMEA_NS					1/0
		GPS_NMEA_EW					1/0
		GPSfix						3
		GPSsats						11
		GPSaltitude					403
		
		GPS_NMEA_checksum_toverify
		GPS_NMEA_checksum_calculated
		
	Checks the header, saves the checksum and calculates a control checksum.
*/
void UBLOX_process_GGA(uint8_t *buffer)
{
	if(buffer[1] == 'G' && (buffer[2] == 'N' || buffer[2] == 'P') && buffer[3] == 'G' && buffer[4] == 'G' && buffer[5] == 'A')
	{
		uint8_t i, j, IntegerPart;
		uint8_t GPSaltitudeNeg = 0;
		
		GPShour = 0;
		GPSminute = 0;
		GPSsecond = 0;
		GPS_NMEA_latitude_int = 0;
		GPS_NMEA_latitude_dec = 0;
		GPS_NMEA_longitude_int = 0;
		GPS_NMEA_longitude_dec = 0;
		GPS_NMEA_NS = 1;
		GPS_NMEA_EW = 1;
		GPSfix = 0;
		GPSsats = 0;
		GPSaltitude = 0;
		GPS_NMEA_checksum_calculated = 0;
		GPS_NMEA_checksum_toverify = 0;
		IntegerPart = 1;
		
		i = 1;
		while(buffer[i] != '*')
		{
			GPS_NMEA_checksum_calculated ^= buffer[i];
			i++;
		}
		
		for(i = 6, j = 0; i < GPSBUFFER_SIZE && (j < 15); i++)
		{
			if(buffer[i] == ',')
			{
				j++;
				IntegerPart = 1;
			}else{
				switch(j)
				{
					case 1:																// TIME
						if((buffer[i] >= '0') && (buffer[i] <= '9'))
						{
							if(i == 7 || i == 8)
							{
								GPShour = GPShour * 10;
								GPShour += (buffer[i] - '0');
							}
							if(i == 9 || i == 10)
							{
								GPSminute = GPSminute * 10;
								GPSminute += (buffer[i] - '0');
							}
							if(i == 11 || i == 12)
							{
								GPSsecond = GPSsecond * 10;
								GPSsecond += (buffer[i] - '0');
							}
						}
						break;
					
					case 2:																// LATITUDE
						if((buffer[i] >= '0') && (buffer[i] <= '9') && IntegerPart)
						{
							GPS_NMEA_latitude_int = GPS_NMEA_latitude_int * 10;
							GPS_NMEA_latitude_int += (uint16_t)(buffer[i] - '0');
						}
						if(buffer[i] == '.') IntegerPart = 0;
						if((buffer[i] >= '0') && (buffer[i] <= '9') && !IntegerPart)
						{
							GPS_NMEA_latitude_dec = GPS_NMEA_latitude_dec * 10;
							GPS_NMEA_latitude_dec += (uint32_t)(buffer[i] - '0');
						}
						break;
					
					case 3:																// NORTH/SOUTH
						if(buffer[i] == 'N')
						{
							GPS_NMEA_NS = 1;
						}
						else if(buffer[i] == 'S')
						{
							GPS_NMEA_NS = 0;
						}
						break;
					
					case 4:																// LONGITUDE
						if((buffer[i] >= '0') && (buffer[i] <= '9') && IntegerPart)
						{
							GPS_NMEA_longitude_int = GPS_NMEA_longitude_int * 10;
							GPS_NMEA_longitude_int += (uint16_t)(buffer[i] - '0');
						}
						if(buffer[i] == '.') IntegerPart = 0;
						if((buffer[i] >= '0') && (buffer[i] <= '9') && !IntegerPart)
						{
							GPS_NMEA_longitude_dec = GPS_NMEA_longitude_dec * 10;
							GPS_NMEA_longitude_dec += (uint32_t)(buffer[i] - '0');
						}
						break;
					
					case 5:																// EAST/WEST
						if(buffer[i] == 'E')
						{
							GPS_NMEA_EW = 1;
						}
						else if(buffer[i] == 'W')
						{
							GPS_NMEA_EW = 0;
						}
						break;
					
					case 6:																// FIX
						GPSfix = buffer[i] - '0';
						break;
					
					case 7:																// SATELLITES
						if((buffer[i] >= '0') && (buffer[i] <= '9'))
						{
							GPSsats = GPSsats * 10;
							GPSsats += (uint8_t)(buffer[i] - '0');
						}
						break;
					
					case 9:																// ALTITUDE
						if(buffer[i] == '-') GPSaltitudeNeg = 1;
						if((buffer[i] >= '0') && (buffer[i] <= '9') && IntegerPart)
						{
							GPSaltitude = GPSaltitude * 10;
							GPSaltitude += (int32_t)(buffer[i] - '0');
						}
						if(buffer[i] == '.') IntegerPart = 0;
						break;
					
					case 14:															// CHECKSUM (XOR of $ ... * bytes)
						if(IntegerPart == 3)
						{
							if((buffer[i] >= '0') && (buffer[i] <= '9')) GPS_NMEA_checksum_toverify += (buffer[i] - '0');
							else if((buffer[i] >= 'A') && (buffer[i] <= 'F')) GPS_NMEA_checksum_toverify += (buffer[i] - '7');
							IntegerPart++;
						}
						if(IntegerPart == 2)
						{
							if((buffer[i] >= '0') && (buffer[i] <= '9')) GPS_NMEA_checksum_toverify = ((buffer[i] - '0') << 4);
							else if((buffer[i] >= 'A') && (buffer[i] <= 'F')) GPS_NMEA_checksum_toverify = ((buffer[i] - '7') << 4);
							IntegerPart++;
						}
						if(buffer[i] == '*') IntegerPart = 2;
						break;
					
					default:
						break;
				}
			}
		}
		
		if(GPSaltitudeNeg) GPSaltitude *= -1;											// adjust the altitude value if negative
		
		if(GPS_NMEA_checksum_calculated != GPS_NMEA_checksum_toverify)
											 GPS_NMEA_error_bitfield |= (1 << 2);		// GGA checksum error
		
	}else{
		GPS_NMEA_error_bitfield |= (1 << 1);											// GGA buffer error
	}
}


/*
	Processes and parses an NMEA ZDA message located in the input buffer.
	Accepts both GPZDA and GNZDA messages.
	
		GPShour						15
		GPSminute					30
		GPSsecond					43
		GPSday						18
		GPSmonth					10
		GPSyear						2016
		
		GPS_NMEA_checksum_toverify
		GPS_NMEA_checksum_calculated
		
	Checks the header, saves the checksum and calculates a control checksum.
*/
void UBLOX_process_ZDA(uint8_t *buffer)
{
	if(buffer[1] == 'G' && (buffer[2] == 'N' || buffer[2] == 'P') && buffer[3] == 'Z' && buffer[4] == 'D' && buffer[5] == 'A')
	{
		uint8_t i, j, IntegerPart;
		
		GPShour = 0;
		GPSminute = 0;
		GPSsecond = 0;
		GPSday = 0;
		GPSmonth = 0;
		GPSyear = 0;
		GPS_NMEA_checksum_calculated = 0;
		GPS_NMEA_checksum_toverify = 0;
		IntegerPart = 1;
		
		i = 1;
		while(buffer[i] != '*')
		{
			GPS_NMEA_checksum_calculated ^= buffer[i];
			i++;
		}
		
		for(i = 6, j = 0; i < GPSBUFFER_SIZE && (j < 7); i++)
		{
			if(buffer[i] == ',')
			{
				j++;
				IntegerPart = 1;
			}else{
				switch(j)
				{
					case 1:																// TIME
						if((buffer[i] >= '0') && (buffer[i] <= '9'))
						{
							if(i == 7 || i == 8)
							{
								GPShour = GPShour * 10;
								GPShour += (buffer[i] - '0');
							}
							if(i == 9 || i == 10)
							{
								GPSminute = GPSminute * 10;
								GPSminute += (buffer[i] - '0');
							}
							if(i == 11 || i == 12)
							{
								GPSsecond = GPSsecond * 10;
								GPSsecond += (buffer[i] - '0');
							}
						}
						break;
					
					case 2:																// DAY
						if((buffer[i] >= '0') && (buffer[i] <= '9'))
						{
							GPSday = GPSday * 10;
							GPSday += (uint8_t)(buffer[i] - '0');
						}
						break;
					
					case 3:																// MONTH
						if((buffer[i] >= '0') && (buffer[i] <= '9'))
						{
							GPSmonth = GPSmonth * 10;
							GPSmonth += (uint8_t)(buffer[i] - '0');
						}
						break;
					
					case 4:																// YEAR
						if((buffer[i] >= '0') && (buffer[i] <= '9'))
						{
							GPSyear = GPSyear * 10;
							GPSyear += (uint8_t)(buffer[i] - '0');
						}
						break;
					
					case 7:																// CHECKSUM (XOR of $ ... * bytes)
						if(IntegerPart == 3)
						{
							if((buffer[i] >= '0') && (buffer[i] <= '9')) GPS_NMEA_checksum_toverify += (buffer[i] - '0');
							else if((buffer[i] >= 'A') && (buffer[i] <= 'F')) GPS_NMEA_checksum_toverify += (buffer[i] - '7');
							IntegerPart++;
						}
						if(IntegerPart == 2)
						{
							if((buffer[i] >= '0') && (buffer[i] <= '9')) GPS_NMEA_checksum_toverify = ((buffer[i] - '0') << 4);
							else if((buffer[i] >= 'A') && (buffer[i] <= 'F')) GPS_NMEA_checksum_toverify = ((buffer[i] - '7') << 4);
							IntegerPart++;
						}
						if(buffer[i] == '*') IntegerPart = 2;
						break;
					
					default:
						break;
				}
			}
		}
	}
}


/*
	Function to construct a telemetry string according to UKHAS specification. It uses decimal degrees format for Latitude and Longitude.
	
	$$CALLSIGN,sentence_id,time,latitude,longitude,altitude,satellites,fix,solar panel voltage,battery voltage,SAM3S temperature,Si4060 temperature,error*CHECKSUM\n
	$$$$TT7F,1,20:31:15,49.49171,18.22271,1131,11,3,2048,4120,15,15, *0C5D\n
	
	Checksum is calculated on bytes between the last dollar sign '$' and the asterisk '*' using CRC_XMODEM_UPDATE function.
	The telemetry string must end with the new line '\n' character.
	In case of lost GPS FIX, the last valid position and altitude data are used.
*/
uint32_t UBLOX_construct_telemetry_UBX(uint8_t *buffer, uint32_t sequence)
{
	for(uint8_t i = 0; i < TELEMETRY_SYNC_BYTES; i++) buffer[sequence++] = '$';
	
	// CALLSIGN
	uint8_t x = 0;
	while(RTTY_callsign[x] != '\0') buffer[sequence++] = RTTY_callsign[x++];
	buffer[sequence++] = ',';
	
	// TIME
	sequence = ASCII_32bit_transmit(telemCount, buffer, sequence);
	buffer[sequence++] = ',';
	sequence = ASCII_8bit_2DEC_transmit(GPShour, buffer, sequence);
	buffer[sequence++] = ':';
	sequence = ASCII_8bit_2DEC_transmit(GPSminute, buffer, sequence);
	buffer[sequence++] = ':';
	sequence = ASCII_8bit_2DEC_transmit(GPSsecond, buffer, sequence);
	buffer[sequence++] = ',';
	
	// DATE
	sequence = ASCII_16bit_transmit(GPSyear, buffer, sequence);
	sequence = ASCII_8bit_2DEC_transmit(GPSmonth, buffer, sequence);
	sequence = ASCII_8bit_2DEC_transmit(GPSday, buffer, sequence);
	buffer[sequence++] = ',';
	
	// POSITION
	if(GPSfix > 0)
	{
		// LATITUDE
		if(GPS_UBX_latitude < 0) buffer[sequence++] = '-';
		sequence = ASCII_8bit_transmit((uint8_t)abs(GPS_UBX_latitude / 10000000), buffer, sequence);
		buffer[sequence++] = '.';
		sequence = ASCII_32bit_LATLON_DECIMAL_transmit((uint32_t)(labs(GPS_UBX_latitude) % 10000000) / 100, buffer, sequence, 5);
		buffer[sequence++] = ',';
		
		// LONGITUDE
		if(GPS_UBX_longitude < 0) buffer[sequence++] = '-';
		sequence = ASCII_8bit_transmit((uint8_t)abs(GPS_UBX_longitude / 10000000), buffer, sequence);
		buffer[sequence++] = '.';
		sequence = ASCII_32bit_LATLON_DECIMAL_transmit((uint32_t)(labs(GPS_UBX_longitude) % 10000000) / 100, buffer, sequence, 5);
		buffer[sequence++] = ',';
		
		// ALTITUDE
		if(GPSaltitude < 0) buffer[sequence++] = '-';
		sequence = ASCII_32bit_transmit((uint32_t)abs(GPSaltitude), buffer, sequence);
		buffer[sequence++] = ',';
		
		// KEEP LATEST VALID VALUES
		GPS_UBX_latitude_L = GPS_UBX_latitude;
		GPS_UBX_longitude_L = GPS_UBX_longitude;
		GPSaltitude_L = GPSaltitude;
	}
	else																				// no fix, retransmit last valid position data
	{
		// LATITUDE
		if(GPS_UBX_latitude_L < 0) buffer[sequence++] = '-';
		sequence = ASCII_8bit_transmit((uint8_t)abs(GPS_UBX_latitude_L / 10000000), buffer, sequence);
		buffer[sequence++] = '.';
		sequence = ASCII_32bit_LATLON_DECIMAL_transmit((uint32_t)(labs(GPS_UBX_latitude_L) % 10000000) / 100, buffer, sequence, 5);
		buffer[sequence++] = ',';
		
		// LONGITUDE
		if(GPS_UBX_longitude_L < 0) buffer[sequence++] = '-';
		sequence = ASCII_8bit_transmit((uint8_t)abs(GPS_UBX_longitude_L / 10000000), buffer, sequence);
		buffer[sequence++] = '.';
		sequence = ASCII_32bit_LATLON_DECIMAL_transmit((uint32_t)(labs(GPS_UBX_longitude_L) % 10000000) / 100, buffer, sequence, 5);
		buffer[sequence++] = ',';
		
		// ALTITUDE
		if(GPSaltitude_L < 0) buffer[sequence++] = '-';
		sequence = ASCII_32bit_transmit((uint32_t)abs(GPSaltitude_L), buffer, sequence);
		buffer[sequence++] = ',';
	}
	
	// SATELLITES
	sequence = ASCII_8bit_transmit(GPSsats, buffer, sequence);
	buffer[sequence++] = ',';
	
	// GPS FIX
	//buffer[sequence++] = GPSfix + '0';
	//buffer[sequence++] = ',';
	
	// POWER SAVE / CONTINUOUS MODE
	//buffer[sequence++] = GPSpowersavemodestate + '0';
	//buffer[sequence++] = ',';
	
	// ADC READINGS
	uint32_t AD3 = ((uint32_t)AD3data * 3300) / 4096;									// converting raw ADC reading to mV
	uint32_t AD9 = ((uint32_t)AD9data * 6600) / 4096;									// converting raw ADC reading to mV
	float temperatureF1 = (float)AD15data * 0.30402 - 273.15 + TEMP_OFFSET;				// converting raw ADC reading to °C
	float temperatureF2 = (float)Si4060Temp * 0.222 - 297;								// converting raw ADC reading to °C
	sequence = ASCII_16bit_transmit((uint16_t)AD3, buffer, sequence);
	buffer[sequence++] = ',';
	sequence = ASCII_16bit_transmit((uint16_t)AD9, buffer, sequence);
	buffer[sequence++] = ',';
	if(temperatureF1 < 0) buffer[sequence++] = '-';
	sequence = ASCII_16bit_transmit((uint16_t)abs(temperatureF1), buffer, sequence);
	buffer[sequence++] = ',';
	if(temperatureF2 < 0) buffer[sequence++] = '-';
	sequence = ASCII_16bit_transmit((uint16_t)abs(temperatureF2), buffer, sequence);
	buffer[sequence++] = ',';
	
	// SSDV IMAGE COUNT
	sequence = ASCII_32bit_transmit(SSDVimages, buffer, sequence);
	buffer[sequence++] = ',';
	buffer[sequence++] = SSDVstatus;
	
	// ERROR BITFIELD
	//if(GPSnavigation != 6) GPS_UBX_error_bitfield |= (1 << 6);							// check whether the module is in AIRBORNE MODE
	//if(GPS_UBX_error_bitfield == 0b01111111) GPS_UBX_error_bitfield = 0b01011111;
	//if(GPS_UBX_error_bitfield == 0b00101100) GPS_UBX_error_bitfield = 0b01001100;
	//if(GPS_UBX_error_bitfield == 0b00101010) GPS_UBX_error_bitfield = 0b01001010;
	//if(GPS_UBX_error_bitfield == 0b00100100) GPS_UBX_error_bitfield = 0b01000100;
	//buffer[sequence++] = GPS_UBX_error_bitfield;
	
	// CHECKSUM
	uint16_t crc = CRC16_checksum(buffer, sequence, TELEMETRY_SYNC_BYTES);
	buffer[sequence++] = '*';
	sequence = ASCII_16bit_HEX_transmit(crc, buffer, sequence);
	
	// NEW LINE
	buffer[sequence++] = 0x0A;
	
	//GPSnavigation = 0;																	// reset the variable ahead of another telemetry round
	telemetry_len = sequence;															// save the telemetry length to a global variable
	GPS_UBX_error_bitfield = 0b00100000;												// reset the bitfield ahead of another telemetry round
	
	return sequence;
}


/*
	Function to construct a telemetry string according to UKHAS specification. It uses NMEA format for Latitude and Longitude.
	
	$$CALLSIGN,sentence_id,time,latitude,longitude,altitude,satellites,fix,solar panel voltage,battery voltage,SAM3S temperature,Si4060 temperature,error*CHECKSUM\n
	$$$$TT7F1,1,20:31:15,4949.171,01822.271,1131,11,3,2048,4120,15,15, *0C5D\n
	
	Checksum is calculated on bytes between the last dollar sign '$' and the asterisk '*' using CRC_XMODEM_UPDATE function.
	The telemetry string must end with the new line '\n' character.
	In case of lost GPS FIX, the last valid position and altitude data are used.
*/
uint32_t UBLOX_construct_telemetry_NMEA(uint8_t *buffer, uint32_t sequence)
{
	for(uint8_t i = 0; i < TELEMETRY_SYNC_BYTES; i++) buffer[sequence++] = '$';
	
	// CALLSIGN
	uint8_t x = 0;
	while(RTTY_callsign[x] != '\0') buffer[sequence++] = RTTY_callsign[x++];
	buffer[sequence++] = ',';
	
	// TIME
	sequence = ASCII_32bit_transmit(telemCount, buffer, sequence);
	buffer[sequence++] = ',';
	sequence = ASCII_8bit_2DEC_transmit(GPShour, buffer, sequence);
	buffer[sequence++] = ':';
	sequence = ASCII_8bit_2DEC_transmit(GPSminute, buffer, sequence);
	buffer[sequence++] = ':';
	sequence = ASCII_8bit_2DEC_transmit(GPSsecond, buffer, sequence);
	buffer[sequence++] = ',';
	
	// DATE
	sequence = ASCII_16bit_transmit(GPSyear, buffer, sequence);
	sequence = ASCII_8bit_2DEC_transmit(GPSmonth, buffer, sequence);
	sequence = ASCII_8bit_2DEC_transmit(GPSday, buffer, sequence);
	buffer[sequence++] = ',';
	
	// POSITION
	if(GPSfix > 0 && !(GPS_NMEA_error_bitfield & (0x01 << 2)))
	{
		// LATITUDE
		if(GPS_NMEA_NS == 0) buffer[sequence++] = '-';
		sequence = ASCII_16bit_transmit(GPS_NMEA_latitude_int, buffer, sequence);
		buffer[sequence++] = '.';
		sequence = ASCII_32bit_LATLON_DECIMAL_transmit(GPS_NMEA_latitude_dec, buffer, sequence, 5);
		buffer[sequence++] = ',';
		
		// LONGITUDE
		if(GPS_NMEA_EW == 0) buffer[sequence++] = '-';
		sequence = ASCII_16bit_transmit(GPS_NMEA_longitude_int, buffer, sequence);
		buffer[sequence++] = '.';
		sequence = ASCII_32bit_LATLON_DECIMAL_transmit(GPS_NMEA_longitude_dec, buffer, sequence, 5);
		buffer[sequence++] = ',';
		
		// ALTITUDE
		if(GPSaltitude < 0) buffer[sequence++] = '-';
		sequence = ASCII_32bit_transmit((uint32_t)abs(GPSaltitude), buffer, sequence);
		buffer[sequence++] = ',';
		
		// KEEP LATEST VALID VALUES
		GPS_NMEA_NS_L = GPS_NMEA_NS;
		GPS_NMEA_EW_L = GPS_NMEA_EW;
		GPSaltitude_L = GPSaltitude;
		GPS_NMEA_latitude_int_L = GPS_NMEA_latitude_int;
		GPS_NMEA_latitude_dec_L = GPS_NMEA_latitude_dec;
		GPS_NMEA_longitude_int_L = GPS_NMEA_longitude_int;
		GPS_NMEA_longitude_dec_L = GPS_NMEA_longitude_dec;
	}
	else																				// no fix or GGA corrupt, retransmit last valid position data
	{
		// LATITUDE
		if(GPS_NMEA_NS_L == 0) buffer[sequence++] = '-';
		sequence = ASCII_16bit_transmit(GPS_NMEA_latitude_int_L, buffer, sequence);
		buffer[sequence++] = '.';
		sequence = ASCII_32bit_LATLON_DECIMAL_transmit(GPS_NMEA_latitude_dec_L, buffer, sequence, 5);
		buffer[sequence++] = ',';
		
		// LONGITUDE
		if(GPS_NMEA_EW_L == 0) buffer[sequence++] = '-';
		sequence = ASCII_16bit_transmit(GPS_NMEA_longitude_int_L, buffer, sequence);
		buffer[sequence++] = '.';
		sequence = ASCII_32bit_LATLON_DECIMAL_transmit(GPS_NMEA_longitude_dec_L, buffer, sequence, 5);
		buffer[sequence++] = ',';
		
		// ALTITUDE
		if(GPSaltitude_L < 0) buffer[sequence++] = '-';
		sequence = ASCII_32bit_transmit((uint32_t)abs(GPSaltitude_L), buffer, sequence);
		buffer[sequence++] = ',';
	}
	
	// SATELLITES
	sequence = ASCII_8bit_transmit(GPSsats, buffer, sequence);
	buffer[sequence++] = ',';
	
	// GPS FIX
	//buffer[sequence++] = GPSfix + '0';
	//buffer[sequence++] = ',';
	
	// POWER SAVE / CONTINUOUS MODE
	//buffer[sequence++] = GPSpowersavemodestate + '0';
	//buffer[sequence++] = ',';
	
	// ADC READINGS
	uint32_t AD3 = ((uint32_t)AD3data * 3300) / 4096;									// converting raw ADC reading to mV
	uint32_t AD9 = ((uint32_t)AD9data * 6600) / 4096;									// converting raw ADC reading to mV
	float temperatureF1 = (float)AD15data * 0.30402 - 273.15 + TEMP_OFFSET;				// converting raw ADC reading to °C
	float temperatureF2 = (float)Si4060Temp * 0.222 - 297.0;							// converting raw ADC reading to °C
	sequence = ASCII_16bit_transmit((uint16_t)AD3, buffer, sequence);
	buffer[sequence++] = ',';
	sequence = ASCII_16bit_transmit((uint16_t)AD9, buffer, sequence);
	buffer[sequence++] = ',';
	if(temperatureF1 < 0) buffer[sequence++] = '-';
	sequence = ASCII_16bit_transmit((uint16_t)abs(temperatureF1), buffer, sequence);
	buffer[sequence++] = ',';
	if(temperatureF2 < 0) buffer[sequence++] = '-';
	sequence = ASCII_16bit_transmit((uint16_t)abs(temperatureF2), buffer, sequence);
	//buffer[sequence++] = ',';
	
	// ERROR BITFIELD
	//if(GPSfix == 0) GPS_NMEA_error_bitfield |= (1 << 4);
	//if(GPSnavigation != 6) GPS_NMEA_error_bitfield |= (1 << 6);
	//if(GPS_NMEA_error_bitfield == 0b01111111) GPS_NMEA_error_bitfield = 0b01011111;
	//if(GPS_NMEA_error_bitfield == 0b00101100) GPS_NMEA_error_bitfield = 0b01001100;
	//if(GPS_NMEA_error_bitfield == 0b00101010) GPS_NMEA_error_bitfield = 0b01001010;
	//if(GPS_NMEA_error_bitfield == 0b00100100) GPS_NMEA_error_bitfield = 0b01000100;
	//buffer[sequence++] = GPS_NMEA_error_bitfield;
	
	// CHECKSUM
	uint16_t crc = CRC16_checksum(buffer, sequence, TELEMETRY_SYNC_BYTES);
	buffer[sequence++] = '*';
	sequence = ASCII_16bit_HEX_transmit(crc, buffer, sequence);
	
	// NEW LINE
	buffer[sequence++] = 0x0A;
	
	//GPSnavigation = 0;																	// reset the variable ahead of another telemetry round
	telemetry_len = sequence;															// save the telemetry length to a global variable
	GPS_NMEA_error_bitfield = 0b00100000;												// reset the bitfield ahead of another telemetry round
	
	return sequence;
}


/*
	Function to prepare the module and enter the chosen POWER SAVING mode.
	First it turns off periodic messages, then it turns of GLONASS (required for POWER SAVE mode), sets up the desired mode
	and a wake up period and switches to the POWER SAVE mode.
*/
void UBLOX_powersave_mode_init(uint8_t * mode)
{
	GPS_UBX_ack_error = 0;
	UBLOX_request_UBX(setNMEAoff, 28, 10, UBLOX_parse_ACK);								// turn off the periodic output
	UBLOX_request_UBX(setGPSonly, 28, 10, UBLOX_parse_ACK);								// turn off GLONASS (needs to be done for POWERSAVE mode)
	UBLOX_request_UBX(mode, 52, 10, UBLOX_parse_ACK);									// set up the desired UBX-CFG-PM2 (0x06 0x3B) settings
	UBLOX_request_UBX(setPowerSaveMode, 10, 10, UBLOX_parse_ACK);						// switch to POWERSAVE mode
}


/*
	Fills a buffer with ASCII characters returned after polling UBX-MON-VER. Individual bits of information are 0x00 delimited.
*/
uint32_t UBLOX_get_version(uint8_t *buffer)
{
	UBLOX_send_message(request0A04, 8);													// request UBX-MON-VER
	
	UART1_buffer_pointer = 0;															// reset UART1 RX buffer pointer
	UBLOX_fill_buffer_UBX(GPSbuffer, 104);												// copy the response from UART1_RX_buffer to GPSbuffer
	
	if(GPSbuffer[0] == 0xB5 && GPSbuffer[1] == 0x62 && GPSbuffer[2] == 0x0A && GPSbuffer[3] == 0x04)
	{
		uint8_t sequence = 0;
		uint8_t zeroFlag = 0;
		uint32_t msglen = (GPSbuffer[5] << 8) | GPSbuffer[4];
		msglen -= 4;
		
		for(uint32_t i = 0; i < msglen; i++)
		{
			if(GPSbuffer[6 + i] != 0)
			{
				buffer[sequence++] = (GPSbuffer[6 + i]);
				zeroFlag = 0;
			}else{
				if(!zeroFlag)
				{
					buffer[sequence++] = 0;
					zeroFlag = 1;
				}
			}
		}
		
		return sequence;
	}else{
		return 0;
	}
}