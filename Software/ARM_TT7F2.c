/*
TT7F2

PCB:	F3 v1.4
	SAM3S8B
	XTAL 12MHz
	UBLOX MAX-M8Q
	Si4060 (434MHz 10dBM CLE matching)
	TCXO 32MHz
	...		LTC3105 (Vout 4.2V, Rmppt 91k)
	MT9D111 (poor colors)

Antenna
	...		2m dipole (0.013 guitar string, 2x 492mm)
	
Power Supply
	4x 52x38 solar cells (series at 0° to ground)
	LiPo 250mAh
	3.3V board operating voltage

Transmissions
	APRS
		callsign:		OK7DMT-12
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
		timing:			once per ~1 minute (Vsolar > 1200mV)
						once per ~2 minutes (Vsolar < 1200mV)
		limit:			no limit
		power:			0x2D 14.56dBm 35.5mA
		
	RTTY
		callsign:		TT7F2
		frequency:		434.319MHz
		baud:			300
		shift:			850Hz
		mode:			8n2
		example:		<0x00><0x00><0x00><0x00><0x00>$$$$TT7F2,13,21:13:27,20170629,49.46872,18.15082,395,6,781,3931,21,14,0,S*1F42\n
						$$CALLSIGN,id,time,date,latitude,longitude,altitude,satellites,solar mV,battery mV,SAM3S °C,Si4060 °C,SSDV images,SSDV status*CHECKSUM\n
		duration:		6.25s (OOK) + ~2.9s (80 bytes)
		timing:			once per ~2 minutes (Vsolar > 1200mV)
		limit:			Vsolar > 1200mV
						Vbattery > 3100mV
		power:			0x2D 12.43dBm 17.0mA
		
	SSDV
		callsign:		TT7F2
		frequency:		434.319MHz
		baud:			300
		shift:			850Hz
		mode:			8n2
		duration:		7.5s (initial OOK), 9.4s (packet), 10-15min (image)
		timing:			at the top of the hour and on the half hour (GPSminute checked)
						interleaved with RTTY and APRS after every 5 packets (~1 minute)
		limit:			Vsolar > 1200mV
						Vbattery > 3100mV
		power:			0x2D 12.43dBm 17.0mA
		resolution:		
		color setting:	

Power Saving
	GPS acquisition:	2MHz PLL (MCU)
	RTTY transmission:	2MHz PLL (MCU)
	PWM clock:			...
	SSDV acquisition:	64MHz PLL (MCU)
	SSDV transmission:	...
	APRS transmission:	16MHz PLL (MCU)
	Wait mode:			4MHz RC (MCU)
	GPS power saving:	...		Software Backup
	TX duration:		~3.6s (Vsolar > 1200mV & Vbattery > 3100mV)
						~0.7s (Vsolar < 1200mV)
						10-15min (SSDV)
	Wait mode duration:	~55s (Vsolar > 1200mV)
						~116s (Vsolar < 1200mV)

ADC
	temperature offset:		24.0°C (APRS sends raw ADC data, RTTY uses this offset)

Constants
	SPI_SCBR		2		(2MHz MCK - 1MHz SPI, 16MHz MCK - 8MHz SPI)
	UART1_BAUD		13		(2MHz MCK - 9600 baud)
	SYSTICK_LOAD	2000	(2MHz MCK - 1ms, 16MHz MCK - 0.125ms)

Limits
	GPS fix:	90 times poll UBX-NAV-PVT at maximum
	GPS fix:	6 minimum satellites
	GPS fix:	no fix - TX only APRS ambiguous position message
	GPS fix:	ok fix - TX APRS, RTTY and SSDV
	Vsolar:		<1200mV only APRS in ~2 minute cycle
	Vbattery:	...		>3100mV TX RTTY and APRS in ~1 minute cycles
				...		<3100mV only TX APRS in ~2 minute cycles

Envelope
	Mylar shaped balloon:	1.84m
	Estimated stretch:		~1.83
*/


// INCLUDE ---------------------------------------------------------------------------------------------------------------
#include "sam.h"
#include "ARM_ADC.h"
#include "ARM_APRS.h"
#include "ARM_DELAY.h"
#include "ARM_EEFC.h"
#include "ARM_GEOFENCE.h"
#include "ARM_LED.h"
#include "ARM_MT9D111.h"
#include "ARM_PIODC.h"
#include "ARM_POWER_SAVE.h"
#include "ARM_PWM.h"
#include "ARM_RS8.h"
#include "ARM_RTC.h"
#include "ARM_RTT.h"
#include "ARM_SI4060.h"
#include "ARM_SPI.h"
#include "ARM_SSDV.h"
#include "ARM_TWI.h"
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


// MT9D111 ---------------------------------------------------------------------------------------------------------------
uint8_t JPEGbuffer[MT9D111_BUFFER_SIZE];

uint8_t img_id												= 0;
uint8_t img[64];
uint8_t pkt[SSDV_PKT_SIZE];

uint32_t res_x												= RES_X;
uint32_t res_y												= RES_Y;
uint8_t qscale_1											= QSCALE_1;
uint8_t qscale_2											= QSCALE_2;
uint8_t qscale_3											= QSCALE_3;
uint8_t jpeg_gamma											= JPEG_GAMMA;
uint8_t jpeg_contrast										= JPEG_CONTRAST;
uint8_t jpeg_drivers										= JPEG_DRIVERS;

uint32_t packetsPerTelem									= TELEMETRY_EVERY_X_PACKETS;


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
uint32_t WaitModeSeconds									= 46;

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

uint32_t SSDVimages											= 0;
uint32_t SSDVstatus											= '0';


// MAIN ------------------------------------------------------------------------------------------------------------------
int main(void)
{
    // POWER-UP
    EEFC_setup(0, 2, 0, 0);												// Flash Wait State 2 + 1 (max. 64MHz)
    PS_SystemInit(15, 3, 5);											// MCK: 2MHz PLL
    WATCHDOG_disable();													// disable WatchDog timer
    SysTick_delay_init();												// configure the delay timer
    LED_PA0_init();
    LED_PB5_init();
	MT9D111_init();
    
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
		if(AD9 > 2800) break;											// Battery minimum voltage limit (mV)
		
		RTT_init(1, 0x8000, 0);											// wake up every 1s
		PS_switch_MCK_to_FastRC(0, 0);
		PS_enter_Wait_Mode(1, 0, 0);									// enable wake up on RTT and enter wait mode
		RTT_off();
		PS_SystemInit(15, 3, 5);										// MCK: 2MHz PLL
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
	
	uint32_t cycleCount = 0;
	
	// MAIN LOOP
    while(1) 
    {
        // STATUS LED
        LED_PA0_blink(5);															// signal start of loop
		cycleCount++;
		
		// GPS FIX
		uint32_t fixCount = 0;
		uint8_t TXaprs = 0;
		uint8_t TXrtty = 0;
		uint8_t TXssdv = 0;
		
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
				LED_PA0_blink(5);													// signal GPS module reset
				SysTick_delay_ms(100);
				LED_PA0_blink(5);
				
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
	
		if(GPSfix == 3 && GPSfix_0107 == 1) {TXaprs = 1; TXrtty = 1; TXssdv = 1;}	// enable APRS, RTTY and SSDV transmissions
		else {TXaprs = 1; TXrtty = 0; TXssdv = 0;}									// disable RTTY and SSDV transmissions
		
		// Si4060/Si4463 TEMPERATURE
		SPI_init();
		SI4060_init();
		Si4060Temp = SI4060_get_temperature();										// SPI and Si4060 need to be initialized first to get the temperature
		SI4060_deinit();
		SPI_deinit();
		
		// ADC READINGS
		ADC_start();
		AD3data = ADC_sample(3, 100);												// SOLAR PANEL voltage
		AD9data = ADC_sample(9, 100);												// BATTERY voltage
		AD15data = ADC_sample_temperature(100);										// ATSAM3S8B's internal temperature
		ADC_stop();
		
		// ALTITUDE LIMIT
		
		
		// SOLAR & BATTERY LIMITS
		uint32_t AD3 = ((uint32_t)AD3data * 3300) / 4096;
		uint32_t AD9 = ((uint32_t)AD9data * 6600) / 4096;
		
		if(AD3 >= 500 && AD9 >= 3000)												// solar panel and battery minimum voltage limit (mV)
		{
			WaitModeSeconds = 46;													// short cycle, transmit APRS, RTTY and SSDV
		}else{
			WaitModeSeconds = 96;													// longer cycle
			TXrtty = 0;																// transmit only APRS
			TXssdv = 0;
		}
		
		// RTTY LIMIT
		if(TXrtty)
		{
			if((cycleCount % 2) == 1) TXrtty = 1;									// transmit RTTY only every other APRS cycle
			else TXrtty = 0;
		}
		
		// SSDV LIMIT
		if(TXssdv)
		{
			if(GPSminute == 0 || GPSminute == 1 || GPSminute == 30 || GPSminute == 31)
			{
				TXssdv = 1;															// if it is the top of the hour or on the half hour, transmit SSDV
			}else{
				TXssdv = 0;															// if not, disable it
			}
		}
		
		// CONSTRUCT RTTY TELEMETRY
		uint32_t telemLen = 0;
		
		if(TXrtty)
		{
			telemCount++;
			telemLen = UBLOX_construct_telemetry_UBX(TXbuffer, 0);				// store the telemetry string in TXbuffer
		}
		
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
		APRSsequence					= cycleCount;
		APRSvalue1						= AD3data;
		APRSvalue2						= AD9data;
		APRSvalue3						= AD15data;
		APRSvalue4						= Si4060Temp;
		APRSvalue5						= GPSsats;
		APRSbitfield					= 0;
		if(GPSnavigation == 6)			APRSbitfield |= (1 << 0);					// Nav bit (Airborne mode)
		if(GPSfix == 3)					APRSbitfield |= (1 << 1);					// Fix bit (GPS fix ok)
		if(TXssdv == 1)					APRSbitfield |= (1 << 2);					// Img bit (currently transmitting SSDV image)
		if(WaitModeSeconds > 60)		APRSbitfield |= (1 << 3);					// PSM bit (power save mode active)
		
		TC_rtty_gfsk_lookup				= 1;										// RTTY_INTERRUPT - 0; GFSK_SYNC - 1; - - 2; LOOKUP - 3
		APRS_send_path					= 2;										// send WIDE2-1 path (2)
		
		if(GPSfix)	APRS_packet_mode	= 1;										// full packet
		else		APRS_packet_mode	= 7;										// no position packet, just backlog and ADC readings
		
		APRS_packet_construct(APRSpacket);											// store the packet in APRSpacket
		
		// BACKLOG
		if(cycleCount % 30 == 0) APRS_store_backlog();								// save a new backlog to flash memory every x telemetry strings
		
		// GEOFENCE
		GEOFENCE_position(GPS_UBX_latitude_Float, GPS_UBX_longitude_Float);			// choose the right APRS frequency based on current location
		APRS_tx_frequency = GEOFENCE_APRS_frequency;
		if(GEOFENCE_no_tx) TXaprs = 0;												// disable APRS transmission in NO AIRBORNE areas
		
		// STATUS LED
		LED_PB5_blink(5);															// signal start of transmissions
		
		// FAST MCK
		PS_switch_MCK_to_FastRC(0, 0);												// MCK: 4MHz internal FastRC
		PS_SystemInit(15, 3, 2);													// MCK: 16MHz PLL
		
		// APRS TX
		if(TXaprs)
		{
			SPI_init();
			SI4060_init();
			SI4060_setup_pins(0x02, 0x04, 0x02, 0x02, 0x00, 0x00);
			SI4060_frequency_offset(0);
			SI4060_PA_mode(6, 0);													// Si4460: lower-power applications, Class-E or Square Wave match
			SI4060_tx_APRS_GFSK_sync();												// transmit the packet using GFSK modulation
			SI4060_deinit();
			SPI_deinit();
		}
		
		// SLOW MCK
		PS_switch_MCK_to_FastRC(0, 0);												// MCK: 4MHz internal FastRC
		PS_SystemInit(15, 3, 5);													// MCK: 2MHz PLL
		
		// RTTY TX
		if(TXrtty)
		{
			SPI_init();
			SI4060_init();
			SI4060_setup_pins(0x02, 0x04, 0x02, 0x02, 0x00, 0x00);
			SI4060_frequency_offset(0);
			SI4060_PA_mode(6, 0);													// Si4460: lower-power applications, Class-E or Square Wave match
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
		
		// MT9D111 GET IMAGE
		uint8_t imageOK = 0;
		uint32_t JPEGlength = 0;
		uint16_t JPEGstatus = 0;
		
		if(TXssdv)
		{
			SSDVstatus = '0';
			
			// MAX MCK																// all following delays must be multiplied by 32 (2MHz -> 64MHz) 
			PS_switch_MCK_to_FastRC(0, 0);											// MCK: 4MHz internal FastRC
			PS_SystemInit(31, 3, 1);												// MCK: 64MHz PLL
			
			// CAMERA INIT & CHECK
			TWI_init_master();														// camera communicates via TWI interface, initialized to 100kHz
			PWM_init(6, 3);															// provide camera with 10.7MHz clock signal
			SysTick_delay_ms(32);													// restart clock 24 clock cycles before de-asserting standby
			
			if(MT9D111_exit_standby())												// if camera reacts, continue
			{
				MT9D111_reset();													// reset the camera
				
				if(MT9D111_get_version() == 0x15190020)								// check the camera responds
				{
					// TAKE JPEG IMAGE
					uint32_t camTimeout = 0;
					
					for(uint8_t i = 0; i < 4; i++)									// allow a few attempts in case of failure
					{
						LED_PA0_blink(160);											// signal camera will try get an image
						SysTick_delay_ms(3200);
						LED_PA0_blink(160);
						SysTick_delay_ms(3200);
						LED_PA0_blink(160);
						
						SSDVstatus = i + '1';										// count attempts
						
						uint32_t len = CreateJpegHeader(JPEGbuffer, res_x, res_y, JPEG_COLOR_FORMAT, JPEG_RESTART_INTERVAL, qscale_1);
						
						// JPEG MODE INIT
						camTimeout = MT9D111_wait_for_state(3);						// wait for the camera's PREVIEW state
						if(!camTimeout) {SSDVstatus = 'P'; continue;}				// next attempt if timed out
						
						camTimeout = MT9D111_mode_1();								// set up camera to take one JPEG
						if(!camTimeout) {SSDVstatus = 'C'; continue;}				// next attempt if timed out
						
						// IMAGE SAMPLING
						camTimeout = 16000000;
						while((PIOA->PIO_PDSR & (1 << 15)) && camTimeout) camTimeout--;		// wait for the end of the current frame (VSYNC HIGH->LOW)
						if(!camTimeout) {SSDVstatus = 'D'; continue;}						// next attempt if timed out
						
						PDC_transfer(JPEGbuffer + len, MT9D111_BUFFER_SIZE - len);	// initialize the PDC (there is not enough time after VSYNC goes HIGH)
						
						camTimeout = 16000000;
						while(!(PIOA->PIO_PDSR & (1 << 15)) && camTimeout) camTimeout--;	// wait for the start of a new frame (VSYNC LOW->HIGH)
						if(!camTimeout) {SSDVstatus = 'D'; continue;}						// next attempt if timed out
						
						camTimeout = 16000000;
						while(PIOA->PIO_PDSR & (1 << 15) && camTimeout) camTimeout--;		// wait for the end of the sampled frame (VSYNC HIGH->LOW)
						if(!camTimeout) {SSDVstatus = 'D'; continue;}						// next attempt if timed out
						
						// ANALYZE RECEIVED DATA
						MT9D111_register_write(WRITE_PAGE, 1);
						uint16_t da5 = MT9D111_variable_read(9, 15, 1);				// last JPEG length [23:16]
						uint16_t da6 = MT9D111_variable_read(9, 16, 0);				// last JPEG length [15:0]
						
						MT9D111_register_write(WRITE_PAGE, 2);
						JPEGstatus = MT9D111_register_read(0x02);					// JPEG status (interested in Transfer done status flag)
						
						JPEGlength = ((uint32_t)da5 << 16) | da6;					// size of the current JPG image (camera produced bytes)
						JPEGlength += len;											// size including the header
						
						if(JPEGlength <= (MT9D111_BUFFER_SIZE - 2) && (JPEGstatus & 0x01) && JPEGlength > (len + 500))
						{
							JPEGbuffer[JPEGlength++] = 0xFF;						// finish the image with an EOI marker
							JPEGbuffer[JPEGlength++] = 0xD9;
							imageOK = 1;											// MCU has JPEG image of length JPEGlength
							break;
						}
						else
						{
							for(uint32_t i = 0; i < MT9D111_BUFFER_SIZE; i++) JPEGbuffer[i] = 0;	// else clear the buffer
							JPEGlength = 0;
							JPEGstatus = 0;
							imageOK = 0;
							SSDVstatus = 'L';										// sampled image exceeded buffer size
						}
					}
					
					// CAMERA STANDBY
					MT9D111_wait_for_state(3);										// wait for the camera's PREVIEW state
					camTimeout = MT9D111_standby();									// prepare camera for low power state, enter standby mode
					if(!camTimeout) SSDVstatus = 'E';								// failed to enter standby on exit
					SysTick_delay_ms(32);											// after asserting standby, wait 10 clock cycles before stopping CLK
					PWM_deinit();													// turn clock signal off
					TWI_deinit();													// de-initialize TWI
				}
				else																// camera didn't respond to command or wrong version
				{
					SSDVstatus = 'V';												// failed communication/wrong version
					PWM_deinit();													// turn clock signal off
					TWI_deinit();													// de-initialize TWI
					imageOK = 0;
				}
			}
			else																	// camera didn't transition to PREVIEW mode (disconnected?)
			{
				SSDVstatus = 'S';													// failed to communicate/exit standby
				PWM_deinit();														// turn clock signal off
				TWI_deinit();														// de-initialize TWI
				imageOK = 0;
			}
			
			// SLOW MCK
			PS_switch_MCK_to_FastRC(0, 0);											// MCK: 4MHz internal FastRC
			PS_SystemInit(15, 3, 5);												// MCK: 2MHz PLL
		}
			
		// SSDV TX
		if(TXssdv & imageOK)
		{
			SSDVimages++;
			
			// RADIO INIT & SYNC
			SPI_init();
			SI4060_init();
			SI4060_setup_pins(0x02, 0x04, 0x02, 0x02, 0x00, 0x00);
			SI4060_frequency_offset(0);
			SI4060_PA_mode(6, 0);													// Si4460: lower-power applications, Class-E or Square Wave match
			SI4060_frequency(FREQUENCY_RTTY);
			SI4060_frequency_deviation(TX_DEVIATION_RTTY);
			SI4060_power_level(POWER_LEVEL);
			SI4060_tx_OOK_blips(5, 250, 250);										// first transmit several blips to announce SSDV transmission
			SI4060_modulation(2, 1);												// FSK, asynchronous
			SI4060_change_state(0x07);												// TX state
			TC0_init_RTTY_NORMAL();													// start TimerCounter0 to time baud rate
			
			uint8_t Sync[] = {0, 0, 0, 0, 0};
			SI4060_tx_RTTY_string_TC0(Sync, 5);										// transmit five 0x00 bytes to help receiver synchronize
			
			// SSDV PROCESS
			uint8_t *_JPEGbufferP = JPEGbuffer;
			ssdv_t ssdv;
			
			ssdv_enc_init(&ssdv, SSDV_TYPE_NORMAL, SSDV_CALLSIGN, img_id++, 4);
			ssdv_enc_set_buffer(&ssdv, pkt);
			
			uint8_t c = 0;
			uint32_t packetCount = 0;
			
			while(1)
			{	
				// INTERLEAVED APRS & RTTY
				if(packetCount % packetsPerTelem == 0 && packetCount != 0)			// every x packets transmit APRS packet and RTTY telemetry
				{
					TC0_stop();														// stop transmission until GPS fix is obtained
					SI4060_deinit();
					SPI_deinit();
					
					// GPS FIX
					uint32_t fixCount = 0;
					uint8_t interleavedTXrtty = 0;
					uint8_t interleavedTXaprs = 1;
					
					UART1_init();
					UBLOX_send_message(dummyByte, 1);								// wake up GPS module
					SysTick_delay_ms(1000);											// wait for GPS module to be ready
					
					GPSnavigation = 0;
					UBLOX_request_UBX(request0624, 8, 44, UBLOX_parse_0624);
					
					if(GPSnavigation != 6)											// verify Dynamic Model: airborne with <1g acceleration
					{
						UBLOX_request_UBX(setNAVmode, 44, 10, UBLOX_parse_ACK);		// if not, set it
					}
					
					while(1)														// poll UBX-NAV-PVT until the module has fix (limited)
					{
						GPSfix = 0;
						GPSfix_0107 = 0;
						GPSsats = 0;
						
						UBLOX_request_UBX(request0107, 8, 100, UBLOX_parse_0107);
						if(GPSfix == 3 && GPSfix_0107 == 1 && GPSsats >= 6) break;
						
						fixCount++;
						
						if(fixCount > 15)											// if taking too long stop trying (decreased limit to normal operation)
						{
							GPSfix = 0;
							GPSfix_0107 = 0;
							GPSsats = 0;
							break;
						}
					}
					
					UBLOX_send_message(setSwBackupMode, 16);						// switch GPS module to software backup mode
					UART1_deinit();
					
					// Si4060/Si4463 TEMPERATURE
					SPI_init();
					SI4060_init();
					Si4060Temp = SI4060_get_temperature();							// SPI and Si4060 need to be initialized first to get the temperature
					SI4060_deinit();
					SPI_deinit();
					
					// ADC READINGS
					ADC_start();
					AD3data = ADC_sample(3, 100);									// SOLAR PANEL voltage
					AD9data = ADC_sample(9, 100);									// BATTERY voltage
					AD15data = ADC_sample_temperature(100);							// ATSAM3S8B's internal temperature
					ADC_stop();
					
					// TX LIMITS
					if(GPSfix == 3 && GPSfix_0107 == 1) interleavedTXrtty = 1;		// enable RTTY
					
					// CONSTRUCT RTTY TELEMETRY
					if(interleavedTXrtty)
					{
						telemCount++;
						telemLen = UBLOX_construct_telemetry_UBX(TXbuffer, 0);
					}
					
					// CONSTRUCT APRS PACKET
					cycleCount++;
					
					APRShour						= GPShour;
					APRSminute						= GPSminute;
					APRSsecond						= GPSsecond;
					APRSyear						= GPSyear;
					APRSmonth						= GPSmonth;
					APRSday							= GPSday;
					APRSlatitude					= GPS_UBX_latitude_Float;
					APRSlongitude					= GPS_UBX_longitude_Float;
					APRSaltitude					= GPSaltitude;
					APRSsequence					= cycleCount;
					APRSvalue1						= AD3data;
					APRSvalue2						= AD9data;
					APRSvalue3						= AD15data;
					APRSvalue4						= Si4060Temp;
					APRSvalue5						= GPSsats;
					APRSbitfield					= 0;
					if(GPSnavigation == 6)			APRSbitfield |= (1 << 0);		// Nav bit (Airborne mode)
					if(GPSfix == 3)					APRSbitfield |= (1 << 1);		// Fix bit (GPS fix ok)
					if(TXssdv == 1)					APRSbitfield |= (1 << 2);		// Img bit (currently transmitting SSDV image)
					
					TC_rtty_gfsk_lookup				= 1;							// RTTY_INTERRUPT - 0; GFSK_SYNC - 1; - - 2; LOOKUP - 3
					APRS_send_path					= 2;							// send WIDE2-1 path (2)
					
					if(GPSfix)	APRS_packet_mode	= 1;							// full packet
					else		APRS_packet_mode	= 7;							// no position packet, just backlog and ADC readings
					
					APRS_packet_construct(APRSpacket);								// store the packet in APRSpacket
					
					// BACKLOG
					if(cycleCount % 30 == 0) APRS_store_backlog();					// save a new backlog to flash memory every x telemetry strings
					
					// GEOFENCE
					GEOFENCE_position(GPS_UBX_latitude_Float, GPS_UBX_longitude_Float);	// choose the right APRS frequency based on current location
					APRS_tx_frequency = GEOFENCE_APRS_frequency;
					if(GEOFENCE_no_tx) interleavedTXaprs = 0;						// disable APRS transmission in NO AIRBORNE areas
					
					// STATUS LED
					LED_PB5_blink(5);												// signal interleaved transmission
					SysTick_delay_ms(50);
					LED_PB5_blink(5);
					
					// APRS TX
					if(interleavedTXaprs)
					{
						// FAST MCK
						PS_switch_MCK_to_FastRC(0, 0);												// MCK: 4MHz internal FastRC
						PS_SystemInit(15, 3, 2);													// MCK: 16MHz PLL
						
						SPI_init();
						SI4060_init();
						SI4060_setup_pins(0x02, 0x04, 0x02, 0x02, 0x00, 0x00);
						SI4060_frequency_offset(0);
						SI4060_PA_mode(6, 0);													// Si4460: lower-power applications, Class-E or Square Wave match
						SI4060_tx_APRS_GFSK_sync();												// transmit the packet using GFSK modulation
						SI4060_deinit();
						SPI_deinit();
						
						// SLOW MCK
						PS_switch_MCK_to_FastRC(0, 0);												// MCK: 4MHz internal FastRC
						PS_SystemInit(15, 3, 5);													// MCK: 2MHz PLL
					}
					
					// RTTY TX
					SPI_init();
					SI4060_init();
					SI4060_setup_pins(0x02, 0x04, 0x02, 0x02, 0x00, 0x00);
					SI4060_frequency_offset(0);
					SI4060_PA_mode(6, 0);											// Si4460: lower-power applications, Class-E or Square Wave match
					SI4060_frequency(FREQUENCY_RTTY);
					SI4060_frequency_deviation(TX_DEVIATION_RTTY);
					SI4060_power_level(POWER_LEVEL);
					SI4060_tx_OOK_blips(5, 250, 250);								// first transmit several blips to announce transmission
					SI4060_modulation(2, 1);										// FSK, asynchronous
					SI4060_change_state(0x07);										// TX state
					TC0_init_RTTY_NORMAL();											// start TimerCounter0 to time baud rate
					
					uint8_t Sync[] = {0, 0, 0, 0, 0};
					SI4060_tx_RTTY_string_TC0(Sync, 5);								// transmit five 0x00 bytes to help receiver synchronize
					
					if(interleavedTXrtty)											// if not allowed, continue to next SSDV packet
					{
						SI4060_tx_RTTY_string_TC0(TXbuffer, telemLen);
					}	
				}
				
				// SSDV PACKET
				packetCount++;
				
				while((c = ssdv_enc_get_packet(&ssdv)) == SSDV_FEED_ME)
				{
					size_t r = 0;
					
					for(uint8_t i = 0; i < 64; i++)
					{
						if(_JPEGbufferP > JPEGbuffer + JPEGlength) continue;
						img[i] = *_JPEGbufferP++;
						r++;
					}
					
					if(r == 0) break;
					ssdv_enc_feed(&ssdv, img, r);
				}
				
				if(c == SSDV_EOI)
				{
					break;
				}
				
				else if(c != SSDV_OK)
				{
					break;
				}
				
				SI4060_tx_RTTY_string_TC0(pkt, 256);
			}
			
			TC0_stop();
			SI4060_deinit();
			SPI_deinit();
		}
		
		// LOW POWER CYCLE
		RTT_init(WaitModeSeconds, 0x8000, 0);										// Wait mode period in RC oscillator's seconds
		PS_switch_MCK_to_FastRC(0, 0);												// MCK: 4MHz internal FastRC
		PS_enter_Wait_Mode(1, 0, 0);												// enable wake up on RTT and enter wait mode
		RTT_off();																	// clear pending flag after wake-up
		PS_SystemInit(15, 3, 5);													// MCK: 2MHz PLL
    }
}
