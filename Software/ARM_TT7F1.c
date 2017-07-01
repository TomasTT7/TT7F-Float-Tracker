/*
TT7F1

PCB:	F5 v1.4
	SAM3S4B
	XTAL 16MHz
	UBLOX MAX-M8Q
	Si4463 (434MHz 20dBM CLE matching)
	TCXO 32MHz
	LTC3105 (Vout 2.7V, Rmppt 91k)

Antenna
	2m dipole (0.013 guitar string, 2x 492mm)
	
Power Supply
	2x 52x38 solar cells (series at 0° to ground)
	1x 15F supercapacitor (2.7V max)
	3.3V board operating voltage

Transmissions
	APRS
		callsign:		OK7DMT-11
		destination:	APRS
		path:			WIDE2-1
		frequency:		Geofence
		mode:			GFSK
		example:		~~~~~~~~~~~~‚ ¤¦@@àž–n<0x88>š¨v®’<0x88>Šd@c<0x03><0xF0>!/5MGoS(L_0GzW |!$!!#p+30n!!!"|<FCS><FCS>~~~
						~~~~~~~~~~~~‚ ¤¦@@àž–n<0x88>š¨v®’<0x88>Šd@c<0x03><0xF0>!/5MGoS(L_0GzW 0K%0/5MI6S(K^HW!!$>+a!*31|!$!!#p+30n!!!"|<FCS><FCS>~~~
						~~~~~~~~~~~~‚ ¤¦@@àž–n<0x88>š¨v®’<0x88>Šd@c<0x03><0xF0>!0000.00N\00000.00W. |!$!!#p+30n!!!"|<FCS><FCS>~~~
						~~~~~~~~~~~~‚ ¤¦@@àž–n<0x88>š¨v®’<0x88>Šd@c<0x03><0xF0>!0000.00N\00000.00W. 0K%0/5MI6S(K^HW!!$>+a!*31|!$!!#p+30n!!!"|<FCS><FCS>~~~
		backlog:		every 30 TX cycles (~10 days stored)
		duration:		0.473-0.68s
		timing:			once per ~1 minute (Vcap > 2500mV)
						once per ~2 minutes (Vcap < 2500mV)
		limit:			no limit
		power:			0x28 16.11dBm 32.8mA
		
	RTTY
		callsign:		TT7F1
		frequency:		434.264MHz
		baud:			100
		shift:			450Hz
		mode:			8n2
		example:		<0x00><0x00><0x00><0x00><0x00>$$$$TT7F1,58,11:06:11,20170620,49.46890,18.15049,353,5,921,2708,37,29*A926\n
						$$CALLSIGN,id,time,date,latitude,longitude,altitude,satellites,solar mV,battery mV,SAM3S °C,Si4060 °C*CHECKSUM\n
		duration:		6.25s (OOK) + ~8.8s (80 bytes)
		timing:			once per ~1 minute (Vcap > 2500mV)
		limit:			Vcap > 2500mV
		power:			0x28 8.47dBm 30.4mA

Power Saving
	GPS acquisition:	2MHz PLL (MCU)
	RTTY transmission:	2MHz PLL (MCU)
	APRS transmission:	16MHz PLL (MCU)
	Wait mode:			4MHz RC (MCU)
	GPS power saving:	Software Backup
	TX duration:		~16.0s (Vcap > 2500mV)
						~0.7s (Vcap < 2500mV)
	Wait mode duration:	~40s (Vcap > 2500mV)
						~114s (Vcap < 2500mV)

ADC
	temperature offset:		10.0°C (APRS sends raw ADC data, RTTY uses this offset)

Constants
	SPI_SCBR		2		(2MHz MCK - 1MHz SPI, 16MHz MCK - 8MHz SPI)
	UART1_BAUD		13		(2MHz MCK - 9600 baud)
	SYSTICK_LOAD	2000	(2MHz MCK - 1ms, 16MHz MCK - 0.125ms)

Limits
	GPS fix:	90 times poll UBX-NAV-PVT at maximum
	GPS fix:	6 minimum satellites
	GPS fix:	no fix - TX only APRS ambiguous position message
	GPS fix:	ok fix - TX APRS and RTTY
	Vsolar:		none
	Vcap:		>2500mV TX RTTY and APRS in ~1 minute cycles
				<2500mV only TX APRS in ~2 minute cycles

Envelope
	Mylar shaped balloon:	1.33m
	Estimated stretch:		~1.9
*/


// INCLUDE ---------------------------------------------------------------------------------------------------------------
#include "sam.h"
#include "ARM_ADC.h"
#include "ARM_APRS.h"
#include "ARM_DELAY.h"
#include "ARM_EEFC.h"
#include "ARM_GEOFENCE.h"
#include "ARM_LED.h"
#include "ARM_POWER_SAVE.h"
#include "ARM_RTC.h"
#include "ARM_RTT.h"
#include "ARM_SI4060.h"
#include "ARM_SPI.h"
#include "ARM_UART.h"
#include "ARM_UBLOX.h"
#include "ARM_WATCHDOG.h"


// APRS ------------------------------------------------------------------------------------------------------------------
uint8_t APRS_send_path										= 2;

uint8_t APRSpacket[APRS_BUFFER_SIZE];

uint8_t APRShour											= 0;
uint8_t APRSminute											= 0;
uint8_t APRSsecond											= 0;
uint8_t APRSday												= 0;
uint8_t APRSmonth											= 0;
uint16_t APRSyear											= 0;

float APRSlatitude											= 0.0;
float APRSlongitude											= 0.0;
int32_t APRSaltitude										= 0;

uint16_t APRSlat_int										= 0;
uint16_t APRSlon_int										= 0;
uint32_t APRSlat_dec										= 0;
uint32_t APRSlon_dec										= 0;
uint8_t APRSlatNS											= 0;
uint8_t APRSlonEW											= 0;

uint32_t APRSsequence										= 0;
uint16_t APRSvalue1											= 0;
uint16_t APRSvalue2											= 0;
uint16_t APRSvalue3											= 0;
uint16_t APRSvalue4											= 0;
uint16_t APRSvalue5											= 0;
uint8_t APRSbitfield										= 0;

uint8_t APRS_packet_mode									= 0;
uint8_t APRS_show_alt_B91									= 0;
uint16_t APRS_packet_size									= 0;


// EEFC ------------------------------------------------------------------------------------------------------------------
uint32_t EEFC_descriptor[32];


// GEOFENCE --------------------------------------------------------------------------------------------------------------
uint32_t GEOFENCE_APRS_frequency							= 144800000;
uint32_t GEOFENCE_no_tx										= 0;


// RTC -------------------------------------------------------------------------------------------------------------------
uint8_t RTCdate												= 0;
uint8_t RTCday												= 0;
uint8_t RTCmonth											= 0;
uint16_t RTCyear											= 0;
uint8_t RTCcent												= 0;
uint8_t RTCampm												= 0;
uint8_t RTChour												= 0;
uint8_t RTCmin												= 0;
uint8_t RTCsec												= 0;


// RTT -------------------------------------------------------------------------------------------------------------------
uint32_t WaitModeSeconds									= 32;

// SI4060 ----------------------------------------------------------------------------------------------------------------
volatile uint32_t SI4060_buffer[16];

volatile uint8_t TC_rtty_gfsk_lookup						= 1;

volatile uint32_t TXdone_get_data							= 0;
volatile uint8_t TXdata_ready								= 0;
uint32_t TXmessageLEN										= 0;
uint8_t TXbuffer[TX_BUFFER_SIZE];

uint8_t APRSpacket[APRS_BUFFER_SIZE];

uint32_t APRS_tx_frequency									= 144800000;
uint8_t SI4060_TX_power										= POWER_LEVEL;


// UART ------------------------------------------------------------------------------------------------------------------
volatile uint8_t UART0_RX_buffer[UART0_BUFFER_SIZE];
volatile uint8_t UART1_RX_buffer[UART1_BUFFER_SIZE];
volatile uint32_t UART0_buffer_pointer						= 0;
volatile uint32_t UART1_buffer_pointer						= 0;
volatile uint32_t UART0_temp								= 0;
volatile uint32_t UART1_temp								= 0;


// UBLOX -----------------------------------------------------------------------------------------------------------------
uint8_t GPS_UBX_error_bitfield								= 0;

uint16_t GPS_NMEA_latitude_int								= 0;
uint32_t GPS_NMEA_latitude_dec								= 0;
uint16_t GPS_NMEA_longitude_int								= 0;
uint32_t GPS_NMEA_longitude_dec								= 0;
uint8_t GPS_NMEA_NS											= 1;
uint8_t GPS_NMEA_EW											= 1;

int32_t GPS_UBX_latitude									= 0;
int32_t GPS_UBX_longitude									= 0;
float GPS_UBX_latitude_Float								= 0.0;
float GPS_UBX_longitude_Float								= 0.0;

int32_t GPSaltitude											= 0;

uint8_t GPShour												= 0;
uint8_t GPSminute											= 0;
uint8_t GPSsecond											= 0;
uint8_t GPSday												= 0;
uint8_t GPSmonth											= 0;
uint16_t GPSyear											= 0;

uint8_t GPSsats												= 0;
uint8_t GPSfix												= 0;
uint8_t GPSfix_0107											= 0;

uint8_t GPSnavigation										= 0;
uint8_t GPSpowermode										= 0;
uint8_t GPSpowersavemodestate								= 0;

int32_t GPSgroundspeed										= 0;
int32_t GPSheading											= 0;

uint16_t AD3data											= 0;
uint16_t AD9data											= 0;
uint16_t AD15data											= 0;
uint16_t Si4060Temp											= 0;
uint32_t telemCount											= 0;
uint32_t telemetry_len										= 0;

int32_t GPS_UBX_latitude_L									= 0;
int32_t GPS_UBX_longitude_L									= 0;
int32_t GPSaltitude_L										= 0;
uint8_t GPS_NMEA_NS_L										= 0;
uint8_t GPS_NMEA_EW_L										= 0;
uint16_t GPS_NMEA_latitude_int_L							= 0;
uint32_t GPS_NMEA_latitude_dec_L							= 0;
uint16_t GPS_NMEA_longitude_int_L							= 0;
uint32_t GPS_NMEA_longitude_dec_L							= 0;


// MAIN ------------------------------------------------------------------------------------------------------------------
int main(void)
{
	// POWER-UP
	EEFC_setup(0, 2, 0, 0);												// Flash Wait State 2 + 1 (max. 64MHz)
	PS_SystemInit(11, 3, 5);											// MCK: 2MHz PLL
	WATCHDOG_disable();													// disable WatchDog timer
	SysTick_delay_init();												// configure the delay timer
	LED_PA0_init();
	LED_PB5_init();
	
	// GPS INITIAL BACKUP
	UART1_init();
	UBLOX_send_message(dummyByte, 1);									// in case only MCU restarted while GPS stayed powered
	SysTick_delay_ms(1000);												// wait for GPS module to be ready
	UBLOX_send_message(setSwBackupMode, 16);							// low consumption at this point
	UART1_deinit();
	
	// BATTERY VOLTAGE LIMIT
	uint32_t AD9 = 0;
	ADC_init();
	
	while(1)
	{
		ADC_start();
		AD9data = ADC_sample(9, 100);									// sample battery voltage
		ADC_stop();
		
		AD9 = ((uint32_t)AD9data * 6600) / 4096;
		if(AD9 > 0) break;												// Battery minimum voltage limit (mV)
		
		RTT_init(1, 0x8000, 0);											// wake up every 1s
		PS_switch_MCK_to_FastRC(0, 0);
		PS_enter_Wait_Mode(1, 0, 0);									// enable wake up on RTT and enter wait mode
		RTT_off();
		PS_SystemInit(11, 3, 5);										// MCK: 2MHz PLL
	}
	
	// GPS SETUP
	UART1_init();
	SysTick_delay_ms(1000);												// in case this follows immediately after the backup command
	UBLOX_send_message(dummyByte, 1);									// wake up GPS module
	SysTick_delay_ms(1000);												// wait for GPS module to be ready
	UBLOX_request_UBX(setNMEAoff, 28, 10, UBLOX_parse_ACK);				// turn off periodic NMEA output
	UBLOX_request_UBX(setNAVmode, 44, 10, UBLOX_parse_ACK);				// set Dynamic Model: airborne with <1g acceleration
	UBLOX_request_UBX(setGPSonly, 28, 10, UBLOX_parse_ACK);				// turn off GLONASS
	UBLOX_request_UBX(saveConfiguration, 21, 10, UBLOX_parse_ACK);		// save current configuration
	UART1_deinit();
	
	// MAIN LOOP
    while(1) 
    {
		// STATUS LED
		LED_PB5_blink(5);															// signal start of loop
		
		// GPS FIX
		uint32_t fixCount = 0;
		uint8_t TXaprs = 0;
		uint8_t TXrtty = 0;
		
		UART1_init();
		UBLOX_send_message(dummyByte, 1);											// wake up GPS module
		SysTick_delay_ms(1000);														// wait for GPS module to be ready
		
		GPSnavigation = 0;
		UBLOX_request_UBX(request0624, 8, 44, UBLOX_parse_0624);
		
		if(GPSnavigation != 6)														// verify Dynamic Model: airborne with <1g acceleration
		{
			UBLOX_request_UBX(setNAVmode, 44, 10, UBLOX_parse_ACK);					// if not, set it
		}
		
		while(1)																	// poll UBX-NAV-PVT until the module has fix (limited)
		{
			GPSfix = 0;
			GPSfix_0107 = 0;
			GPSsats = 0;
			
			UBLOX_request_UBX(request0107, 8, 100, UBLOX_parse_0107);
			if(GPSfix == 3 && GPSfix_0107 == 1 && GPSsats >= 6) break;
			
			fixCount++;
			
			if(fixCount > 90)														// if taking too long reset and re-initialize GPS module
			{
				LED_PB5_blink(5);													// signal GPS module reset
				SysTick_delay_ms(100);
				LED_PB5_blink(5);
				
				UBLOX_send_message(resetReceiver, 12);								// reset GPS module
				SysTick_delay_ms(1000);												// wait for GPS module to be ready
				UBLOX_request_UBX(setNMEAoff, 28, 10, UBLOX_parse_ACK);				// turn off periodic NMEA output
				UBLOX_request_UBX(setNAVmode, 44, 10, UBLOX_parse_ACK);				// set Dynamic Model: airborne with <1g acceleration
				UBLOX_request_UBX(setGPSonly, 28, 10, UBLOX_parse_ACK);				// turn off GLONASS
				UBLOX_request_UBX(saveConfiguration, 21, 10, UBLOX_parse_ACK);		// save current configuration
				
				GPSfix = 0;
				GPSfix_0107 = 0;
				GPSsats = 0;
				break;
			}
		}
		
		UBLOX_send_message(setSwBackupMode, 16);									// switch GPS module to software backup mode
		UART1_deinit();
		
		if(GPSfix == 3 && GPSfix_0107 == 1) {TXaprs = 1; TXrtty = 1;}				// enable both APRS and RTTY transmissions
		else {TXaprs = 1; TXrtty = 0;}												// disable RTTY transmission
		
		// Si4060/Si4463 TEMPERATURE
		SPI_init();
		SI4060_init();
		Si4060Temp = SI4060_get_temperature();										// SPI and Si4060 need to be initialized first to get the temperature
		SI4060_deinit();
		SPI_deinit();
		
		// ADC READINGS
		ADC_start();
		AD3data = ADC_sample(3, 100);												// SOLAR PANEL voltage
		AD9data = ADC_sample(9, 100);												// SUPERCAP voltage
		AD15data = ADC_sample_temperature(100);										// ATSAM3S4B's internal temperature
		ADC_stop();
		
		// ALTITUDE LIMIT
		
		
		// SUPERCAP LIMIT
		uint32_t AD9 = ((uint32_t)AD9data * 6600) / 4096;
		
		if(AD9 > 2500)																// supercap minimum voltage limit (mV)
		{
			WaitModeSeconds = 32;													// short cycle, transmit both RTTY and APRS
		}else{
			WaitModeSeconds = 91;													// longer cycle
			TXrtty = 0;																// transmit only APRS
		}
		
		// CONSTRUCT RTTY TELEMETRY
		telemCount++;
		uint32_t telemLen = UBLOX_construct_telemetry_UBX(TXbuffer, 0);				// store the telemetry string in TXbuffer
		
		// CONSTRUCT APRS PACKET
		APRShour						= GPShour;
		APRSminute						= GPSminute;
		APRSsecond						= GPSsecond;
		APRSyear						= GPSyear;
		APRSmonth						= GPSmonth;
		APRSday							= GPSday;
		APRSlatitude					= GPS_UBX_latitude_Float;
		APRSlongitude					= GPS_UBX_longitude_Float;
		APRSaltitude					= GPSaltitude;
		APRSsequence					= telemCount;
		APRSvalue1						= AD3data;
		APRSvalue2						= AD9data;
		APRSvalue3						= AD15data;
		APRSvalue4						= Si4060Temp;
		APRSvalue5						= GPSsats;
		APRSbitfield					= 0;
		if(GPSnavigation == 6)			APRSbitfield |= (1 << 0);
		if(GPSfix == 3)					APRSbitfield |= (1 << 1);
		
		TC_rtty_gfsk_lookup				= 1;										// RTTY_INTERRUPT - 0; GFSK_SYNC - 1; - - 2; LOOKUP - 3
		APRS_send_path					= 2;										// send WIDE2-1 path (2)
		
		if(GPSfix)	APRS_packet_mode	= 1;										// full packet
		else		APRS_packet_mode	= 7;										// no position packet, just backlog and ADC readings
		
		APRS_packet_construct(APRSpacket);											// store the packet in APRSpacket
		
		// BACKLOG
		if(telemCount % 30 == 0) APRS_store_backlog();								// save a new backlog to flash memory every x telemetry strings
		
		// GEOFENCE
		GEOFENCE_position(GPS_UBX_latitude_Float, GPS_UBX_longitude_Float);			// choose the right APRS frequency based on current location
		APRS_tx_frequency = GEOFENCE_APRS_frequency;
		if(GEOFENCE_no_tx) TXaprs = 0;												// disable APRS transmission in NO AIRBORNE areas
		
		// STATUS LED
		LED_PA0_blink(5);															// signal start of transmissions
		
		// FAST MCK
		PS_switch_MCK_to_FastRC(0, 0);												// MCK: 4MHz internal FastRC
		PS_SystemInit(11, 3, 2);													// MCK: 16MHz PLL
		
		// APRS TX
		if(TXaprs)
		{
			SPI_init();
			SI4060_init();
			SI4060_setup_pins(0x02, 0x04, 0x02, 0x02, 0x00, 0x00);
			SI4060_frequency_offset(0);
			SI4060_PA_mode(2, 0);													// Si4463/64: higher maximum power, Class-E or Square Wave match
			SI4060_tx_APRS_GFSK_sync();												// transmit the packet using GFSK modulation
			SI4060_deinit();
			SPI_deinit();
		}
		
		// SLOW MCK
		PS_switch_MCK_to_FastRC(0, 0);												// MCK: 4MHz internal FastRC
		PS_SystemInit(11, 3, 5);													// MCK: 2MHz PLL
		
		// RTTY TX
		if(TXrtty)
		{
			SPI_init();
			SI4060_init();
			SI4060_setup_pins(0x02, 0x04, 0x02, 0x02, 0x00, 0x00);
			SI4060_frequency_offset(0);
			SI4060_PA_mode(2, 0);													// Si4463/64: higher maximum power, Class-E or Square Wave match
			SI4060_frequency(FREQUENCY_RTTY);
			SI4060_frequency_deviation(TX_DEVIATION_RTTY);
			SI4060_power_level(POWER_LEVEL);
			SI4060_tx_OOK_blips(5, 250, 1000);										// first transmit several blips to announce RTTY transmission
			SI4060_modulation(2, 1);												// FSK, asynchronous
			SI4060_change_state(0x07);												// TX state
			TC0_init_RTTY_NORMAL();													// start TimerCounter0 to time baud rate
			
			uint8_t Sync[] = {0, 0, 0, 0, 0};
			SI4060_tx_RTTY_string_TC0(Sync, 5);										// transmit five 0x00 bytes to help receiver synchronize
			SI4060_tx_RTTY_string_TC0(TXbuffer, telemLen);							// then transmit the telemetry string
			
			TC0_stop();
			SI4060_deinit();
			SPI_deinit();
		}
		
		// LOW POWER CYCLE
		RTT_init(WaitModeSeconds, 0x8000, 0);										// Wait mode period in RC oscillator's seconds
		PS_switch_MCK_to_FastRC(0, 0);												// MCK: 4MHz internal FastRC
		PS_enter_Wait_Mode(1, 0, 0);												// enable wake up on RTT and enter wait mode
		RTT_off();																	// clear pending flag after wake-up
		PS_SystemInit(11, 3, 5);													// MCK: 2MHz PLL
    }
}