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
#include <stdlib.h> // mathematical functions


/*

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

*/
uint32_t ASCII_8bit_transmit(uint8_t number, uint8_t *buffer, uint32_t sequence)
{
	uint8_t ascii1 = 0; // 8bit numbers - 3 decimal places max
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

*/
uint32_t ASCII_8bit_2DEC_transmit(uint8_t number, uint8_t *buffer, uint32_t sequence)
{
	uint8_t ascii1 = 0; // 8bit numbers - 3 decimal places max
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

*/
uint32_t ASCII_16bit_transmit(uint16_t number, uint8_t *buffer, uint32_t sequence)
{
	uint8_t ascii1 = 0; // 16bit numbers - 5 decimal places max
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

*/
uint32_t ASCII_16bit_HEX_transmit(uint16_t number, uint8_t *buffer, uint32_t sequence)
{
	uint8_t ascii1 = 0; // 16bit numbers - 4 hexadecimal places max
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

*/
uint32_t ASCII_32bit_transmit(uint32_t number, uint8_t *buffer, uint32_t sequence)
{
	uint8_t ascii1 = 0; // 32bit numbers - 10 decimal places max
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

*/
uint32_t ASCII_32bit_LATLON_transmit(uint32_t number, uint8_t *buffer, uint32_t sequence)
{
	uint8_t ascii1 = 0; // 32bit numbers - 10 decimal places max
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
	//buffer[sequence++] = ascii4; // for 7 decimal places accuracy
	//buffer[sequence++] = ascii5; // for 7 decimal places accuracy
	buffer[sequence++] = ascii6;
	buffer[sequence++] = ascii7;
	buffer[sequence++] = ascii8;
	buffer[sequence++] = ascii9;
	buffer[sequence++] = ascii10;
	
	return sequence;
}


/*

*/
void Coords_DEGtoDEC(uint32_t lat_INT, uint32_t lat_DEC, uint32_t lon_INT, uint32_t lon_DEC, uint8_t latNS, uint8_t lonEW, float lat, float lon)
{
	// input lat_INT 4928 - degrees, minutes
	// input lat_DEC 08702 - minutes decimal value
	// input lon_INT 01805 - degrees, minutes
	// input lon_DEC 46513 - minutes decimal value
	// input latNS - 0/1 S/N
	// input lonEW - 0/1 W/E
	
	uint32_t deg = lat_INT / 100; // 49
	uint32_t min = lat_INT % 100; // 28
	min = (min * 100000) + lat_DEC; // 2808702
	float minf = min / 100000.0; // 28.08702
	minf = minf * 100 / 60; // 46.8117
	min = minf * 100000.0; // 4681170
	lat = (deg * 10000000) + min; // 494681170
	
	deg = lon_INT / 100; // 18
	min = lon_INT % 100; // 05
	min = (min * 100000) + lon_DEC; // 546513
	minf = min / 100000.0; // 5.46513
	minf = minf * 100 / 60; // 9.10855
	min = minf * 100000.0; // 910855
	lon = (deg * 10000000) + min; // 180910855
	
	
	if(!latNS) lat = lat * -1;
	if(!lonEW) lon = lon * -1;
	
	lon_DEC = (labs(lon) % 10000000) / 100;
	lon_INT = abs(lon / 10000000);
	lat_DEC = (labs(lat) % 10000000) / 100;
	lat_INT = abs(lat / 10000000);
	
	APRSLatitude = (float)lat / 10000000.0;
	APRSLongitude = (float)lon / 10000000.0;
}


/*

*/
void UBLOX_powersave_mode_init(uint8_t * mode)
{
	// after setNMEAoff setting NMEA message's rate doesn't have an effect, GPGGAs must be polled manually
	UBLOX_send_message(setNMEAoff, 28); // turn off the periodic output
	SysTick_delay_ms(50);
	UBLOX_send_message(enableGPSonly, 28); // turn off GLONASS (needs to be done for powersave mode)
	SysTick_delay_ms(50);
	UBLOX_send_message(mode, 52); // setup the desired UBX-CFG-PM2 (0x06 0x3B) settings
	SysTick_delay_ms(50);
	UBLOX_send_message(setPowerSaveMode, 10); // switch to powersave mode
	SysTick_delay_ms(50);
}


#ifdef UBX


/*

*/
void UBLOX_fill_buffer_UBX(uint8_t *buffer, uint8_t len) // the delay for reception reacts to module's response
{
	uint32_t timeout = 16000000;
	uint32_t pos = UART1_buffer_pointer;

	while(UART1_buffer_pointer < (pos + len) && timeout) timeout--;
	for(uint8_t i = 0; i < GPSBUFFER_SIZE; i++)
	{
		buffer[i] = 0;
	}
	
	uint8_t bytes = UART1_buffer_pointer;
	for(uint8_t i = 0; i < bytes; i++)
	{
		buffer[i] = UART1_RX_buffer[i];
	}
}


/*

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

*/
void UBLOX_parse_0102(volatile uint8_t *buffer) // UBX 01 02 - HEX - POSITION
{
	GPSerror |= (1 << 2);
	if(buffer[0] == 0xB5 && buffer[1] == 0x62 && buffer[2] == 0x01 && buffer[3] == 0x02)
	{
		if(UBLOX_verify_checksum(buffer, 36))
		{
			GPSlon = (int32_t)buffer[10] | (int32_t)buffer[11] << 8 | (int32_t)buffer[12] << 16 | (int32_t)buffer[13] << 24;
			GPSlon_dec = (labs(GPSlon) % 10000000) / 100;
			GPSlon_int = abs(GPSlon / 10000000);
			GPSlat = (int32_t)buffer[14] | (int32_t)buffer[15] << 8 | (int32_t)buffer[16] << 16 | (int32_t)buffer[17] << 24;
			GPSlat_dec = (labs(GPSlat) % 10000000) / 100;
			GPSlat_int = abs(GPSlat / 10000000);
			GPSalt = (int32_t)buffer[22] | (int32_t)buffer[23] << 8 | (int32_t)buffer[24] << 16 | (int32_t)buffer[25] << 24;
			GPSalt /= 1000;
			GPSerror &= ~(1 << 2);
			}else{
			GPSchecksError++;
		}
	}else{
		GPSbufferError++;
	}
}


/*

*/
void UBLOX_parse_0121(volatile uint8_t *buffer) // UBX 01 21 - HEX - TIME
{
	GPSerror |= (1 << 3);
	if(buffer[0] == 0xB5 && buffer[1] == 0x62 && buffer[2] == 0x01 && buffer[3] == 0x21)
	{
		if(UBLOX_verify_checksum(buffer, 28))
		{
			GPShour = buffer[22];
			GPSminute = buffer[23];
			GPSsecond = buffer[24];
			GPSerror &= ~(1 << 3);
			}else{
			GPSchecksError++;
		}
		}else{
		GPSbufferError++;
	}
}


/*

*/
void UBLOX_parse_0106(volatile uint8_t *buffer) // UBX 01 06 - HEX - SATS & FIX
{
	GPSerror |= (1 << 1);
	if(buffer[0] == 0xB5 && buffer[1] == 0x62 && buffer[2] == 0x01 && buffer[3] == 0x06)
	{
		if(UBLOX_verify_checksum(buffer, 60))
		{
			GPSfix = buffer[16];
			GPSsats = buffer[53];
			GPSerror &= ~(1 << 1);
			}else{
			GPSchecksError++;
			GPSfix = 0;
			GPSsats = 0;
		}
		}else{
		GPSbufferError++;
		GPSfix = 0;
		GPSsats = 0;
	}
}


/*

*/
void UBLOX_parse_0624(volatile uint8_t *buffer) // UBX 06 24 - HEX - NAVIGATION MODE
{
	GPSerror |= (1 << 0);
	if(buffer[0] == 0xB5 && buffer[1] == 0x62 && buffer[2] == 0x06 && buffer[3] == 0x24)
	{
		if(UBLOX_verify_checksum(buffer, 44))
		{
			GPSnavigation = buffer[8];
			GPSerror &= ~(1 << 0);
		}else{
			GPSchecksError++;
			GPSnavigation = 0;
		}
	}else{
		GPSbufferError++;
		GPSnavigation = 0;
	}
}


/*

*/
void UBLOX_parse_0611(volatile uint8_t *buffer) // UBX 06 11 - HEX - POWER SAVE MODE
{
	GPSerror |= (1 << 4);
	if(buffer[0] == 0xB5 && buffer[1] == 0x62 && buffer[2] == 0x06 && buffer[3] == 0x11)
	{
		if(UBLOX_verify_checksum(buffer, 10))
		{
			GPSpowermode = buffer[7];
			GPSerror &= ~(1 << 4);
		}else{
			GPSchecksError++;
			GPSpowermode = 0;
		}
		}else{
		GPSbufferError++;
		GPSpowermode = 0;
	}
}


/*

*/
void UBLOX_parse_0107(volatile uint8_t *buffer) // UBX 01 07 - HEX - EVERYTHING
{
	GPSerror |= (1 << 2);
	if(buffer[0] == 0xB5 && buffer[1] == 0x62 && buffer[2] == 0x01 && buffer[3] == 0x07)
	{
		if(UBLOX_verify_checksum(buffer, 92) || UBLOX_verify_checksum(buffer, 100)) // UBLOX 7 message is shorter then UBLOX 8 message
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
			
			// POWER SAVE MODE STATE
			GPSpowersavemodestate = (buffer[27] >> 2) & 0x07;
			
			// SATS
			GPSsats = buffer[29];
			
			// LONGITUDE, LATITUDE, ALTITUDE ABOVE MEAN SEA LEVEL
			GPSlon = (int32_t)buffer[30] | (int32_t)buffer[31] << 8 | (int32_t)buffer[32] << 16 | (int32_t)buffer[33] << 24;
			GPSlon_dec = (labs(GPSlon) % 10000000) / 100;
			GPSlon_int = abs(GPSlon / 10000000);
			
			GPSlat = (int32_t)buffer[34] | (int32_t)buffer[35] << 8 | (int32_t)buffer[36] << 16 | (int32_t)buffer[37] << 24;
			GPSlat_dec = (labs(GPSlat) % 10000000) / 100;
			GPSlat_int = abs(GPSlat / 10000000);
			
			GPSalt = (int32_t)buffer[42] | (int32_t)buffer[43] << 8 | (int32_t)buffer[44] << 16 | (int32_t)buffer[45] << 24;
			GPSalt /= 1000;
			
			// GROUND SPEED, HEADING
			GPSgroundspeed = (int32_t)buffer[66] | (int32_t)buffer[67] << 8 | (int32_t)buffer[68] << 16 | (int32_t)buffer[69] << 24;
			GPSheading = (int32_t)buffer[70] | (int32_t)buffer[71] << 8 | (int32_t)buffer[72] << 16 | (int32_t)buffer[73] << 24;;
			
			GPSerror &= ~(1 << 2);
		}else{
			GPSchecksError++;
		}
	}
}


/*

*/
void UBLOX_parse_ACK(volatile uint8_t *buffer)
{
	if(buffer[0] == 0xB5 && buffer[1] == 0x62 && buffer[2] == 0x05)
	{
		if(buffer[3] != 0x01)
		{
			GPSackError++;
		}
		}else{
		GPSbufferError++;
	}
}


/*

*/
void UBLOX_parse_empty()
{
	// dummy function
}


/*

*/
void UBLOX_request_UBX(uint8_t *request, uint8_t len, uint8_t expectlen, void (*parse)(volatile uint8_t*)) // request with a dynamic delay
{
	for(uint8_t i = 0; i < len; i++) // send the request
	{
		UART1_TX(*request++);
	}
	UART1_buffer_pointer = 0; // reset UART1 RX buffer pointer
	UBLOX_fill_buffer_UBX(GPSbuffer, expectlen); // copy the response from UART1_RX_buffer to GPSbuffer
	parse(GPSbuffer); // parse the response to variables
}


/*

*/
uint32_t TX_BUFFER_fill_UBX(uint8_t *buffer, uint32_t sequence)
{
	buffer[0] = '$';
	buffer[1] = '$';
	buffer[2] = '$';
	buffer[3] = '$';
	buffer[4] = 'T';
	buffer[5] = 'T';
	buffer[6] = '7';
	buffer[7] = 'F';
	buffer[8] = ',';
	sequence = 9;
	
	sequence = ASCII_32bit_transmit(telemCount, buffer, sequence);
	buffer[sequence++] = ',';
	sequence = ASCII_8bit_2DEC_transmit(GPShour, buffer, sequence);
	buffer[sequence++] = ':';
	sequence = ASCII_8bit_2DEC_transmit(GPSminute, buffer, sequence);
	buffer[sequence++] = ':';
	sequence = ASCII_8bit_2DEC_transmit(GPSsecond, buffer, sequence);
	buffer[sequence++] = ',';
	
	sequence = ASCII_16bit_transmit(GPSyear, buffer, sequence);
	sequence = ASCII_8bit_2DEC_transmit(GPSmonth, buffer, sequence);
	sequence = ASCII_8bit_2DEC_transmit(GPSday, buffer, sequence);
	buffer[sequence++] = ',';
	
	if(GPSfix > 0)	// if the fix is not valid, retransmit last valid position data
	{
		if(GPSlat < 0) buffer[sequence++] = '-';
		sequence = ASCII_16bit_transmit((uint16_t)GPSlat_int, buffer, sequence);
		buffer[sequence++] = '.';
		sequence = ASCII_32bit_LATLON_transmit((uint32_t)GPSlat_dec, buffer, sequence);	// must fill '0's after decimal point
		buffer[sequence++] = ',';
		
		if(GPSlon < 0) buffer[sequence++] = '-';
		sequence = ASCII_16bit_transmit((uint16_t)GPSlon_int, buffer, sequence);
		buffer[sequence++] = '.';
		sequence = ASCII_32bit_LATLON_transmit((uint32_t)GPSlon_dec, buffer, sequence);	// must fill '0's after decimal point
		buffer[sequence++] = ',';
		
		if(GPSalt < 0) buffer[sequence++] = '-';
		uint32_t alt = (uint32_t)abs(GPSalt);
		sequence = ASCII_32bit_transmit(alt, buffer, sequence);
		buffer[sequence++] = ',';
		
		GPSlat_L = GPSlat;
		GPSlat_int_L = GPSlat_int;
		GPSlat_dec_L = GPSlat_dec;
		GPSlon_L = GPSlon;
		GPSlon_int_L = GPSlon_int;
		GPSlon_dec_L = GPSlon_dec;
		GPSalt_L = GPSalt;
	}else{
		if(GPSlat_L < 0) buffer[sequence++] = '-';
		sequence = ASCII_16bit_transmit((uint16_t)GPSlat_int_L, buffer, sequence);
		buffer[sequence++] = '.';
		sequence = ASCII_32bit_LATLON_transmit((uint32_t)GPSlat_dec_L, buffer, sequence);	// must fill '0's after decimal point
		buffer[sequence++] = ',';
		
		if(GPSlon_L < 0) buffer[sequence++] = '-';
		sequence = ASCII_16bit_transmit((uint16_t)GPSlon_int_L, buffer, sequence);
		buffer[sequence++] = '.';
		sequence = ASCII_32bit_LATLON_transmit((uint32_t)GPSlon_dec_L, buffer, sequence);	// must fill '0's after decimal point
		buffer[sequence++] = ',';
		
		if(GPSalt_L < 0) buffer[sequence++] = '-';
		uint32_t alt_L = (uint32_t)abs(GPSalt_L);		// needs to be turned from INT32_T to UINT32_T for proper processing of negative altitudes
		sequence = ASCII_32bit_transmit(alt_L, buffer, sequence);
		buffer[sequence++] = ',';
	}
	
	sequence = ASCII_8bit_transmit(GPSsats, buffer, sequence);
	buffer[sequence++] = ',';
	buffer[sequence++] = GPSfix + '0';
	buffer[sequence++] = ',';
	//buffer[sequence++] = GPSpowersavemodestate + '0';
	//buffer[sequence++] = ',';
	
	uint32_t AD3 = ((uint32_t)AD3data * 3300) / 4096;							// convert ADC reading to mV
	uint32_t AD9 = ((uint32_t)AD9data * 6600) / 4096;							// convert ADC reading to mV
	float temperatureF = (float)AD15data * 0.30402 - 274.896 + TEMP_OFFSET;		// convert ADC reading to °C
	sequence = ASCII_16bit_transmit((uint16_t)AD3, buffer, sequence);
	buffer[sequence++] = ',';
	sequence = ASCII_16bit_transmit((uint16_t)AD9, buffer, sequence);
	buffer[sequence++] = ',';
	if(temperatureF < 0) buffer[sequence++] = '-';
	sequence = ASCII_16bit_transmit((uint8_t)abs(temperatureF), buffer, sequence);
	buffer[sequence++] = ',';
	
	if(GPSnavigation != 6) GPSerror |= (1 << 6);
	if(GPSerror == 0b01111111) GPSerror = 0b01011111;	// character 'DEL' doesn't show in DL-FLDIGI, needs to be changed -> '_'
	if(GPSerror == 0b00101100) GPSerror = 0b01001100;	// character corresponds to ',' which is used in the parser -> 'L'
	if(GPSerror == 0b00101010) GPSerror = 0b01001010;	// character corresponds to '*' which is used in the parser -> 'J'
	if(GPSerror == 0b00100100) GPSerror = 0b01000100;	// character corresponds to '$' which is used in the parser -> 'D'
	buffer[sequence++] = GPSerror;
	
	GPSchecksum = CRC16_checksum(buffer, sequence, 4);
	buffer[sequence++] = '*';
	sequence = ASCII_16bit_HEX_transmit(GPSchecksum, buffer, sequence);
	
	//buffer[sequence++] = 0x0D;						// CR '\r' - not advised by UKHAS
	buffer[sequence++] = 0x0A;							// LF '\n'
	
	GPSerror = 0b00100000;
	GPSnavigation = 0;
	telemetry_len = sequence;
	
	return sequence;
}


#endif // UBX


#ifdef NMEA


/*

*/
void UBLOX_fill_buffer_NMEA(uint8_t *buffer)
{
	uint32_t timeout = 16000000;

	while(UART1_RX_buffer[UART1_buffer_pointer - 1] != '\n' && timeout) timeout--;
	for(uint8_t i = 0; i < GPSBUFFER_SIZE; i++)
	{
		buffer[i] = 0;
	}
	
	if(!timeout) GPSerror |= (1 << 0);
	
	uint8_t bytes = UART1_buffer_pointer;
	for(uint8_t i = 0; i < bytes; i++)
	{
		buffer[i] = UART1_RX_buffer[i];
	}
}


/*

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

*/
void UBLOX_process_GGA(uint8_t *buffer)
{
	if(buffer[1] == 'G' && (buffer[2] == 'N' || buffer[2] == 'P') && buffer[3] == 'G' && buffer[4] == 'G' && buffer[5] == 'A')
	{
		uint8_t i, j, IntegerPart;
		
		GPShour = 0;
		GPSminute = 0;
		GPSsecond = 0;
		GPSlat_int = 0;
		GPSlat_dec = 0;
		GPSlon_int = 0;
		GPSlon_dec = 0;
		GPSlatNS = 1;
		GPSlonEW = 1;
		GPSfix = 0;
		GPSsats = 0;
		GPSaltNeg = 0;
		GPSalt = 0;
		GPSchecksum = 0;
		GPSchecksum_verify = 0;
		IntegerPart = 1;
		
		i = 1;
		while(buffer[i] != '*')
		{
			GPSchecksum ^= buffer[i];
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
					case 1: // time
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
					
					case 2: // latitude
					if((buffer[i] >= '0') && (buffer[i] <= '9') && IntegerPart)
					{
						GPSlat_int = GPSlat_int * 10;
						GPSlat_int += (int16_t)(buffer[i] - '0');
					}
					if(buffer[i] == '.') IntegerPart = 0;
					if((buffer[i] >= '0') && (buffer[i] <= '9') && !IntegerPart)
					{
						GPSlat_dec = GPSlat_dec * 10;
						GPSlat_dec += (int32_t)(buffer[i] - '0');
					}
					break;
					
					case 3: // N/S
					if(buffer[i] == 'N')
					{
						GPSlatNS = 1;
					}
					else if(buffer[i] == 'S')
					{
						GPSlatNS = 0;
					}
					break;
					
					case 4: // longitude
					if((buffer[i] >= '0') && (buffer[i] <= '9') && IntegerPart)
					{
						GPSlon_int = GPSlon_int * 10;
						GPSlon_int += (int16_t)(buffer[i] - '0');
					}
					if(buffer[i] == '.') IntegerPart = 0;
					if((buffer[i] >= '0') && (buffer[i] <= '9') && !IntegerPart)
					{
						GPSlon_dec = GPSlon_dec * 10;
						GPSlon_dec += (int32_t)(buffer[i] - '0');
					}
					break;
					
					case 5: // E/W
					if(buffer[i] == 'E')
					{
						GPSlonEW = 1;
					}
					else if(buffer[i] == 'W')
					{
						GPSlonEW = 0;
					}
					break;
					
					case 6: // fix
					GPSfix = buffer[i] - '0';
					break;
					
					case 7: // satellites
					if((buffer[i] >= '0') && (buffer[i] <= '9'))
					{
						GPSsats = GPSsats * 10;
						GPSsats += (uint8_t)(buffer[i] - '0');
					}
					break;
					
					case 9: // altitude
					if(buffer[i] == '-') GPSaltNeg = 1;
					if((buffer[i] >= '0') && (buffer[i] <= '9') && IntegerPart)
					{
						GPSalt = GPSalt * 10;
						GPSalt += (int32_t)(buffer[i] - '0');
					}
					if(buffer[i] == '.') IntegerPart = 0;
					break;
					
					case 14: // checksum (XOR of $-* bytes)
					if(IntegerPart == 3)
					{
						if((buffer[i] >= '0') && (buffer[i] <= '9')) GPSchecksum_verify += (buffer[i] - '0');
						else if((buffer[i] >= 'A') && (buffer[i] <= 'F')) GPSchecksum_verify += (buffer[i] - '7');
						IntegerPart++;
					}
					if(IntegerPart == 2)
					{
						if((buffer[i] >= '0') && (buffer[i] <= '9')) GPSchecksum_verify = ((buffer[i] - '0') << 4);
						else if((buffer[i] >= 'A') && (buffer[i] <= 'F')) GPSchecksum_verify = ((buffer[i] - '7') << 4);
						IntegerPart++;
					}
					if(buffer[i] == '*') IntegerPart = 2;
					break;
					
					default:
					break;
				}
			}
		}
	}else{
		GPSerror |= (1 << 1);
	}
}


/*

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
		GPSchecksum = 0;
		GPSchecksum_verify = 0;
		IntegerPart = 1;
		
		i = 1;
		while(buffer[i] != '*')
		{
			GPSchecksum ^= buffer[i];
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
					case 1: // time
					
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
					
					case 2: // Day
					
						if((buffer[i] >= '0') && (buffer[i] <= '9'))
						{
							GPSday = GPSday * 10;
							GPSday += (uint8_t)(buffer[i] - '0');
						}
						break;
						
					case 3: // Month
					
						if((buffer[i] >= '0') && (buffer[i] <= '9'))
						{
							GPSmonth = GPSmonth * 10;
							GPSmonth += (uint8_t)(buffer[i] - '0');
						}
						break;
						
					case 4: // Year
					
						if((buffer[i] >= '0') && (buffer[i] <= '9'))
						{
							GPSyear = GPSyear * 10;
							GPSyear += (uint8_t)(buffer[i] - '0');
						}
						break;
						
					case 7: // checksum (XOR of $-* bytes)
					
						if(IntegerPart == 3)
						{
							if((buffer[i] >= '0') && (buffer[i] <= '9')) GPSchecksum_verify += (buffer[i] - '0');
							else if((buffer[i] >= 'A') && (buffer[i] <= 'F')) GPSchecksum_verify += (buffer[i] - '7');
							IntegerPart++;
						}
						if(IntegerPart == 2)
						{
							if((buffer[i] >= '0') && (buffer[i] <= '9')) GPSchecksum_verify = ((buffer[i] - '0') << 4);
							else if((buffer[i] >= 'A') && (buffer[i] <= 'F')) GPSchecksum_verify = ((buffer[i] - '7') << 4);
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

*/
uint32_t TX_BUFFER_fill_NMEA(uint8_t *buffer, uint32_t sequence)
{
	buffer[0] = '$';
	buffer[1] = '$';
	buffer[2] = 'T';
	buffer[3] = 'T';
	buffer[4] = '7';
	buffer[5] = 'F';
	buffer[6] = ',';
	sequence = 7;
	sequence = ASCII_32bit_transmit(telemCount, buffer, sequence);
	buffer[sequence++] = ',';
	sequence = ASCII_8bit_2DEC_transmit(GPShour, buffer, sequence);
	buffer[sequence++] = ':';
	sequence = ASCII_8bit_2DEC_transmit(GPSminute, buffer, sequence);
	buffer[sequence++] = ':';
	sequence = ASCII_8bit_2DEC_transmit(GPSsecond, buffer, sequence);
	buffer[sequence++] = ',';
	if(GPSfix > 0 && GPSchecksum == GPSchecksum_verify)	// if the fix is not valid or the GGA message was corrupt, retransmit last valid position data
	{
		if(GPSlatNS == 0) buffer[sequence++] = '-';
		sequence = ASCII_16bit_transmit((uint16_t)GPSlat_int, buffer, sequence);
		buffer[sequence++] = '.';
		sequence = ASCII_32bit_LATLON_transmit((uint32_t)GPSlat_dec, buffer, sequence);		// must fill '0's after decimal point
		buffer[sequence++] = ',';
		if(GPSlonEW == 0) buffer[sequence++] = '-';
		sequence = ASCII_16bit_transmit((uint16_t)GPSlon_int, buffer, sequence);
		buffer[sequence++] = '.';
		sequence = ASCII_32bit_LATLON_transmit((uint32_t)GPSlon_dec, buffer, sequence);		// must fill '0's after decimal point
		buffer[sequence++] = ',';
		if(GPSaltNeg) buffer[sequence++] = '-';
		sequence = ASCII_32bit_transmit(GPSalt, buffer, sequence);
		GPSlat_int_L = GPSlat_int;
		GPSlat_dec_L = GPSlat_dec;
		GPSlon_int_L = GPSlon_int;
		GPSlon_dec_L = GPSlon_dec;
		GPSlatNS_L = GPSlatNS;
		GPSlonEW_L = GPSlonEW;
		GPSaltNeg_L = GPSaltNeg;
		GPSalt_L = GPSalt;
	}else{
		if(GPSlatNS_L == 0) buffer[sequence++] = '-';
		sequence = ASCII_16bit_transmit((uint16_t)GPSlat_int_L, buffer, sequence);
		buffer[sequence++] = '.';
		sequence = ASCII_32bit_LATLON_transmit((uint32_t)GPSlat_dec_L, buffer, sequence);	// must fill '0's after decimal point
		buffer[sequence++] = ',';
		if(GPSlonEW_L == 0) buffer[sequence++] = '-';
		sequence = ASCII_16bit_transmit((uint16_t)GPSlon_int_L, buffer, sequence);
		buffer[sequence++] = '.';
		sequence = ASCII_32bit_LATLON_transmit((uint32_t)GPSlon_dec_L, buffer, sequence);	// must fill '0's after decimal point
		buffer[sequence++] = ',';
		if(GPSaltNeg_L) buffer[sequence++] = '-';
		sequence = ASCII_32bit_transmit(GPSalt_L, buffer, sequence);
	}
	buffer[sequence++] = ',';
	sequence = ASCII_8bit_transmit(GPSsats, buffer, sequence);
	buffer[sequence++] = ',';
	sequence = ASCII_8bit_transmit(GPSfix, buffer, sequence);
	buffer[sequence++] = ',';
	
	//uint32_t AD3 = ((uint32_t)AD3data * 3300) / 4096;							// convert ADC reading to mV
	uint32_t AD9 = ((uint32_t)AD9data * 6600) / 4096;							// convert ADC reading to mV
	float temperatureF = (float)AD15data * 0.30402 - 274.896 + TEMP_OFFSET;		// convert ADC reading to °C
	
	//sequence = ASCII_16bit_transmit((uint16_t)AD3, buffer, sequence);
	//buffer[sequence++] = ',';
	sequence = ASCII_16bit_transmit((uint16_t)AD9, buffer, sequence);
	buffer[sequence++] = ',';
	if(temperatureF < 0) buffer[sequence++] = '-';
	sequence = ASCII_8bit_transmit((uint8_t)abs(temperatureF), buffer, sequence);
	buffer[sequence++] = ',';
	
	if(GPSfix == 0) GPSerror |= (1 << 4);
	if(GPSchecksum != GPSchecksum_verify) GPSerror |= (1 << 2);
	if(GPSnavigation != 6) GPSerror |= (1 << 6);
	if(GPSerror == 0b01111111) GPSerror = 0b01011111;		// character doesn't show in DL-FLDIGI, needs to be changed
	if(GPSerror == 0b00101100) GPSerror = 0b01001100;		// character corresponds to ',' which is used in the parser
	if(GPSerror == 0b00101010) GPSerror = 0b01001010;		// character corresponds to '*' which is used in the parser
	if(GPSerror == 0b00100100) GPSerror = 0b01000100;		// character corresponds to '$' which is used in the parser
	
	buffer[sequence++] = GPSerror;
	GPSchecksum = CRC16_checksum(buffer, sequence, 2);
	buffer[sequence++] = '*';
	sequence = ASCII_16bit_HEX_transmit(GPSchecksum, buffer, sequence);
	
	//buffer[sequence++] = 0x0D;							// CR '\r' - not advised to use
	buffer[sequence++] = 0x0A;								// LF '\n'
	buffer[sequence] = 0x00;								// NUL '\0'
	
	GPSerror = 0b00100000;
	GPSnavigation = 0;
	telemetry_len = sequence - 1;
	
	return sequence;
}

#endif // NMEA