
#ifndef ARM_APRS_H
#define ARM_APRS_H

#include "stdint.h"


#define SSID 11											// APRS source address SSID
#define DSSID 0											// APRS destination address SSID
#define APRSFLAGS 20									// number of 0x7E FLAGS in the beginning of the APRS message
#define APRS_BUFFER_SIZE 350


static char APRS_callsign[6] = "OK7DMT";				// 6 characters (fill the rest with 'space')
static char APRS_destination[6] = "APRS  ";				// 6 characters (fill the rest with 'space')

/*
	0		no path
	1		WIDE1-1
	2		WIDE2-1
	3		WIDE1-1, WIDE2-1
*/
extern uint8_t APRS_send_path;							


static uint16_t num = 0;

/*
	APRS PACKET SIZE
		Flags (?), Destination (7), Source (7), Digipeater (0-56), Control (1), Protocol ID (1), Information (1-256), FCS (2)
*/
extern uint8_t APRSpacket[APRS_BUFFER_SIZE];			// max APRS packet size

extern uint8_t APRSHour;
extern uint8_t APRSMinute;
extern uint8_t APRSSecond;
extern uint8_t APRSDay;
extern uint8_t APRSMonth;
extern uint16_t APRSYear;
extern float APRSLatitude;
extern float APRSLongitude;
extern uint16_t APRSAltitude;
extern uint32_t APRSSequence;
extern uint16_t APRSValue1;
extern uint16_t APRSValue2;
extern uint16_t APRSValue3;
extern uint16_t APRSValue4;
extern uint16_t APRSValue5;
extern uint16_t APRSBitfield;
extern uint16_t APRSlat_int;
extern uint16_t APRSlon_int;
extern uint32_t APRSlat_dec;
extern uint32_t APRSlon_dec;
extern uint8_t APRSlatNS;
extern uint8_t APRSlonEW;

extern uint8_t APRS_packet_mode;						// holds the choice of what type of packet should APRS_packet_construct() create
extern uint8_t APRS_show_alt_B91;						// 0 - don't show	1 - show altitude in B91 encoded position
extern uint16_t APRS_packet_size;						// holds the length of the current APRS packet
extern uint8_t *pointerSSDVpacket;


// Functions
uint16_t crc_ccitt_update(uint16_t crc, uint8_t data);
void Base91_u16_2DEC_encode(uint16_t number, uint8_t *buffer);
void Base91_u32_encode(uint32_t number, uint8_t *buffer);
void ASCII_8bitfield_transmit_APRS(uint8_t number, uint8_t *buffer);
void ASCII_16bit_transmit_APRS(uint16_t number, uint8_t *buffer, uint8_t ints);
void ASCII_16bit_transmit_APRS_auto(uint16_t number, uint8_t *buffer);
void ASCII_32bit_LATLON_transmit_APRS(uint32_t number, uint8_t *buffer, uint8_t altitude);
void APRS_base91_SSDV_encode(uint8_t *BASE91buffer, uint8_t *SSDVpacket);
void APRS_SSDV_packet(uint8_t *buffer, uint8_t *packet);
void APRS_time_short(uint8_t *buffer, uint8_t hour, uint8_t minute, uint8_t second);
void APRS_time_mid(uint8_t *buffer, uint8_t hour, uint8_t minute, uint8_t day);
void APRS_time_long(uint8_t *buffer, uint8_t hour, uint8_t minute, uint8_t month, uint8_t day);
void APRS_position_uncompressed(uint8_t *buffer, uint16_t lat_int, uint16_t lon_int, uint32_t lat_dec,
								uint32_t lon_dec, uint8_t NS, uint8_t EW, uint32_t alt);
void APRS_position_base91(uint8_t *buffer, float lat, float lon, float alt, uint8_t showAlt);
void APRS_telemetry_uncompressed(uint8_t *buffer, uint16_t sequence, int16_t value1, int16_t value2,
								int16_t value3, int16_t value4, int16_t value5, uint8_t bitfield);
void APRS_telemetry_base91(uint8_t *buffer, uint32_t sequence, uint16_t value1, uint16_t value2,
								uint16_t value3, uint16_t value4, uint16_t value5, uint8_t bitfield);
void APRS_telemetry_PARM(uint8_t *buffer, char *string, char *addressee);
void APRS_telemetry_UNIT(uint8_t *buffer, char *string, char *addressee);
void APRS_telemetry_EQNS(uint8_t *buffer, char *string, char *addressee);
void APRS_telemetry_BITS(uint8_t *buffer, char *string, char *addressee);
void APRS_comment(uint8_t *buffer, char *string);
void APRS_comment_altitude(uint8_t *buffer, uint32_t alt);
void APRS_packet_construct(uint8_t *buffer);


#endif // ARM_APRS_H_