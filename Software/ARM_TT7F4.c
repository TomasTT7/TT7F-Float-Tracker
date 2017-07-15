/*
TT7F4

PCB:	F9 v1.5
	SAM3S8B
	XTAL 12MHz
	Biwin GM10
	Si4463 (169MHz 20dBM SQW matching)
	TCXO 32MHz
	LTC3105 (Vout 4.08V, Rmppt 180k)

Antenna
	2m dipole (0.013 guitar string, 2x 492mm)

Power Supply
	8x 52x39 solar cells (2 parallel branches of 4 in series at 90° to ground, branches back to back)
	LiPo 400mAh + 2x 4.7F Supercapacitors in series 
	3.3V board operating voltage

Transmissions
	APRS
		callsign:		OK7DMT-9
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
		timing:			once per ~1 minute (Vsolar > 1600mV && Vbattery > 3000mV)
						once per ~2 minutes (Vsolar < 1600mV || Vbattery < 3000mV)
						once per ~30 seconds (altitude decrease at >= 0.5m/s over last two cycles)
		limit:			no limit
		power:			0x64 16.81dBm 89.3mA
		
Power Saving
	GPS acquisition:	2MHz PLL (MCU)
	APRS transmission:	16MHz PLL (MCU)
	Wait mode:			4MHz RC (MCU)
	GPS power saving:	Backup
	TX duration:		~0.7s
	Wait mode duration:	~55s (Vsolar > 1600mV && Vbattery > 3000mV)
						~116s (Vsolar < 1600mV || Vbattery < 3000mV)
						~26s (altitude decrease at >= 0.5m/s over last two cycles)

ADC
	temperature offset:		13.0°C (APRS sends raw ADC data)

Constants
	SPI_SCBR		2		(2MHz MCK - 1MHz SPI, 16MHz MCK - 8MHz SPI)
	UART1_BAUD		13		(2MHz MCK - 9600 baud)
	SYSTICK_LOAD	2000	(2MHz MCK - 1ms, 16MHz MCK - 0.125ms)

Limits
	GPS fix:	90 times poll UBX-NAV-PVT at maximum
	GPS fix:	6 minimum satellites
	GPS fix:	no fix - TX APRS ambiguous position message
	GPS fix:	ok fix - TX APRS standard message
	Vsolar:		> 1600mV TX APRS
				< 1600mV TX APRS in ~2 minute cycles
	Vbattery:	> 3000mV TX APRS
				< 3000mV TX APRS in ~2 minute cycles
	Watchdog:	16s

Envelope
	Mylar shaped balloon:	?
	Estimated stretch:		?
*/


// DEFINE ----------------------------------------------------------------------------------------------------------------
#define SHORT_CYCLE			45		// value / 0.82 = ~duration of one main loop in seconds (Normal mode)
#define LONG_CYCLE			95		// value / 0.82 = ~duration of one main loop in seconds (Power Saving mode)
#define EXTRA_SHORT_CYCLE	21		// value / 0.82 = ~duration of one main loop in seconds (Payload descending)
#define DESCENT				0.5		// m/s
#define SOLAR				1600	// mV
#define BATTERY				3000	// mV
#define BATTERY_ON			2800	// mV
#define FIX					90		// attempts to poll UBX-NAV-PVT
#define SATS				6		// number of satellites required for positional solution


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

uint8_t APRS_ssid											= SSID;
char APRS_callsign[6]										= APRS_CALLSIGN;


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
uint32_t WaitModeSeconds									= 45;

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
	WATCHDOG_enable(4095, 1);											// setup WatchDog with 16s period
    SysTick_delay_init();												// configure the delay timer
    LED_PA0_init();
    LED_PB5_init();
    
    // GPS INITIAL BACKUP
    UART1_init();
    UBLOX_send_message(dummyByte, 1);									// in case only MCU restarted while GPS stayed powered
    SysTick_delay_ms(1000);												// wait for GPS module to be ready
	UBLOX_send_message(setBackupMode, 16);								// low consumption at this point, Biwin GM10 - older soft, uses backup (not sw backup)
    UART1_deinit();
	
	// BATTERY VOLTAGE LIMIT
	uint32_t AD_9 = 0;
	ADC_init();
	
	while(1)
	{
		// WATCHDOG RESTART
		WATCHDOG_restart();
		
		ADC_start();
		AD9data = ADC_sample(9, 100);									// sample battery voltage
		ADC_stop();
		
		AD_9 = ((uint32_t)AD9data * 6600) / 4096;
		if(AD_9 >= BATTERY_ON) break;									// Battery minimum voltage limit (mV)
		
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
	
	uint32_t cycleCount = 0;											// keeps count of main loop
	int32_t prevAlt1 = 0;												// altitude one cycle back
	int32_t prevAlt2 = 0;												// altitude two cycles back
	uint32_t prevMode1 = 1;												// power mode one cycle back (cycle length)
	uint32_t prevMode2 = 1;												// power mode two cycles back (cycle length)
	
	// MAIN LOOP
    while(1) 
    {
		// STATUS LED
        LED_PB5_blink(5);															// signal start of loop
		cycleCount++;
		
		// WATCHDOG RESTART
		WATCHDOG_restart();
		
		// GPS FIX
		uint32_t fixCount = 0;
		uint8_t TXaprs = 0;
		
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
			// WATCHDOG RESTART
			WATCHDOG_restart();
			
			GPSfix = 0;
			GPSfix_0107 = 0;
			GPSsats = 0;
			
			UBLOX_request_UBX(request0107, 8, 92, UBLOX_parse_0107);				// Biwin GM10 - older soft version, only 92 bytes for UBX-NAV-PVT
			if(GPSfix == 3 && GPSfix_0107 == 1 && GPSsats >= SATS) break;
			
			fixCount++;
			
			if(fixCount > FIX)														// if taking too long reset and re-initialize GPS module
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
		
		UBLOX_send_message(setBackupMode, 16);										// switch GPS module to software backup mode, Biwin GM10 uses backup
		UART1_deinit();
		
		if(GPSfix == 3 && GPSfix_0107 == 1) {TXaprs = 1;}							// enable APRS
		else {TXaprs = 1;}															// enable APRS
		
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
		
		// SOLAR & BATTERY LIMITS
		uint32_t AD3 = ((uint32_t)AD3data * 3300) / 4096;
		uint32_t AD9 = ((uint32_t)AD9data * 6600) / 4096;
		
		if(AD3 >= SOLAR && AD9 >= BATTERY)											// solar panel and battery minimum voltage limit (mV)
		{
			WaitModeSeconds = SHORT_CYCLE;											// short cycle
		}else{
			WaitModeSeconds = LONG_CYCLE;											// longer cycle
		}
		
		// ALTITUDE LIMIT
		if(GPSfix == 3)
		{
			float chng1 = (float)(prevAlt1 - GPSaltitude);
			float chng2 = (float)(prevAlt2 - prevAlt1);
			float time1 = (float)prevMode1 / 0.82;
			float time2 = (float)prevMode2 / 0.82;
			
			if(chng1 / time1 >= DESCENT && chng2 / time2 >= DESCENT)				// check if descent speed in two intervals exceeds limit
			{
				WaitModeSeconds = EXTRA_SHORT_CYCLE;								// extra short cycle when falling
			}
			
			prevAlt2 = prevAlt1;													// update the historical values
			prevAlt1 = GPSaltitude;
			prevMode2 = prevMode1;
			prevMode1 = WaitModeSeconds;
		}
		
		// WATCHDOG RESTART
		WATCHDOG_restart();
		
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
		if(GPSnavigation == 6)						APRSbitfield |= (1 << 0);		// Nav bit (Airborne mode)
		if(GPSfix == 3)								APRSbitfield |= (1 << 1);		// Fix bit (GPS fix ok)
		if(WaitModeSeconds == EXTRA_SHORT_CYCLE)	APRSbitfield |= (1 << 2);		// Des bit (tracker is descending)
		if(WaitModeSeconds == LONG_CYCLE)			APRSbitfield |= (1 << 3);		// PSM bit (power save mode active)
		
		TC_rtty_gfsk_lookup				= 1;										// RTTY_INTERRUPT - 0; GFSK_SYNC - 1; - - 2; LOOKUP - 3
		APRS_send_path					= 2;										// send WIDE2-1 path (2)
		
		if(GPSfix)	APRS_packet_mode	= 1;										// full packet
		else		APRS_packet_mode	= 7;										// no position packet, just backlog and ADC readings
		
		APRS_packet_construct(APRSpacket);											// store the packet in APRSpacket
		
		// BACKLOG
		if((cycleCount % 30) == 0 && GPSfix == 3) APRS_store_backlog();				// save a new backlog to flash memory every x telemetry strings
		
		// GEOFENCE
		GEOFENCE_position(GPS_UBX_latitude_Float, GPS_UBX_longitude_Float);			// choose the right APRS frequency based on current location
		APRS_tx_frequency = GEOFENCE_APRS_frequency;
		if(GEOFENCE_no_tx) TXaprs = 0;												// disable APRS transmission in NO AIRBORNE areas
		
		// STATUS LED
		LED_PA0_blink(5);															// signal start of transmissions
		
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
			SI4060_PA_mode(2, 0);													// Si4463/64: higher maximum power, Class-E or Square Wave match
			SI4060_tx_APRS_GFSK_sync();												// transmit the packet using GFSK modulation
			SI4060_deinit();
			SPI_deinit();
		}
		
		// SLOW MCK
		PS_switch_MCK_to_FastRC(0, 0);												// MCK: 4MHz internal FastRC
		PS_SystemInit(15, 3, 5);													// MCK: 2MHz PLL
		
		// WATCHDOG RESTART
		WATCHDOG_restart();
		
		// LOW POWER CYCLE
		RTT_init(WaitModeSeconds, 0x8000, 0);										// Wait mode period in RC oscillator's seconds
		PS_switch_MCK_to_FastRC(0, 0);												// MCK: 4MHz internal FastRC
		PS_enter_Wait_Mode(1, 0, 0);												// enable wake up on RTT and enter wait mode
		RTT_off();																	// clear pending flag after wake-up
		PS_SystemInit(15, 3, 5);													// MCK: 2MHz PLL
    }
}