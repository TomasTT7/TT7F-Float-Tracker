/*
TT7F6W

PCB:	F1 v1.4
	SAM3S8B
	XTAL 12MHz
	UBLOX MAX-7C
	Si4060 (434MHz 10dBM CLE matching)
	TCXO 32MHz
	LTC3105 (Vout 2.70V, Rmppt 90k) - doesn't work properly
	Si5351A (XTAL version)

Antenna
	2m dipole from 0.12mm magnetic wire (2x 508mm)
	20m dipole from 0.12mm magnetic wire (2x 5.214m)

Power Supply
	4x 52x38 solar cells (in series at 0° to ground, wired directly to supercap+ through a Schottky diode)
	1x Supercapacitor 4.7F (2.7V)
	3.3V board operating voltage

Transmissions
	APRS
		callsign:		OK7DMT-8
		destination:	APRS
		path:			WIDE2-1
		frequency:		Geofence
		mode:			GFSK
		example:		~~~~~~~~~~~~‚ ¤¦@@àž–n<0x88>š¨v®’<0x88>Šd@c<0x03><0xF0>!/5MGoS(L_0GzW |!$!!#p+30n!!!"|<FCS><FCS>~~~
						~~~~~~~~~~~~‚ ¤¦@@àž–n<0x88>š¨v®’<0x88>Šd@c<0x03><0xF0>!/5MGoS(L_0GzW 0K%0/5MI6S(K^HW!!$>+a!*31|!$!!#p+30n!!!"|<FCS><FCS>~~~
						~~~~~~~~~~~~‚ ¤¦@@àž–n<0x88>š¨v®’<0x88>Šd@c<0x03><0xF0>!0000.00N\00000.00W. |!$!!#p+30n!!!"|<FCS><FCS>~~~
						~~~~~~~~~~~~‚ ¤¦@@àž–n<0x88>š¨v®’<0x88>Šd@c<0x03><0xF0>!0000.00N\00000.00W. 0K%0/5MI6S(K^HW!!$>+a!*31|!$!!#p+30n!!!"|<FCS><FCS>~~~
		backlog:		every 20 TX cycles (~10 days stored)
		duration:		0.473-0.68s
		timing:			once per ~1 minute
		limit:			no limit
		power:			0x3C 16.55dBm 44.0mA

	WSPR
		callsign:		OK7DMT
		frequency:		14.097,000-14.097,200 MHz (20m band)
		modulation:		4-FSK
		shift:			1.46Hz (between two individual frequencies)
		bandwidth:		6Hz
		example:		OK7DMT JN99 10
						<OK7DMT> JN99bl 30
		duration:		110.6s (162 symbols * 0.683s)
		timing:			two successive transmissions per 10 minutes
		power:			~25dBm, 8.0mA at 3.3V

Power Saving
	GPS acquisition:	2MHz PLL (MCU)
	WSPR transmission:	2MHz PLL (MCU)
	APRS transmission:	16MHz PLL (MCU)
	Wait mode:			4MHz RC (MCU)
	GPS power saving:	Backup
	TX duration:		~0.7s
						110.6s
	Wait mode duration:	55s

ADC
	temperature offset:		8.0°C (APRS sends raw ADC data, RTTY uses this offset)

Constants
	SPI_SCBR		2		(2MHz MCK - 1MHz SPI, 16MHz MCK - 8MHz SPI)
	UART1_BAUD		13		(2MHz MCK - 9600 baud)
	SYSTICK_LOAD	2000	(2MHz MCK - 1ms, 16MHz MCK - 0.125ms)

Limits
	GPS fix:	90 times poll UBX-NAV-PVT at maximum
	GPS fix:	6 minimum satellites
	GPS fix:	no fix - TX only APRS ambiguous position message
	GPS fix:	ok fix - TX APRS and WSPR
	Vsolar:		none
	Vsupercap:	none
	Watchdog:	16s
 */


// DEFINE ----------------------------------------------------------------------------------------------------------------
#define SHORT_CYCLE			50		// value / 0.91 = ~duration of one main loop in seconds (Normal mode)
#define LONG_CYCLE			100		// value / 0.91 = ~duration of one main loop in seconds (Power Saving mode)
#define SOLAR				0		// mV
#define SUPERCAP			0		// mV
#define SUPERCAP_ON			0		// mV
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
#include "ARM_SI5351.h"
#include "ARM_SPI.h"
#include "ARM_TWI.h"
#include "ARM_UART.h"
#include "ARM_UBLOX.h"
#include "ARM_WATCHDOG.h"
#include "ARM_WSPR.h"


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
uint32_t WaitModeSeconds									= SHORT_CYCLE;

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


// SI5351 ----------------------------------------------------------------------------------------------------------------
uint64_t SI5351frequency001Hz = SI5351_FREQUENCY;


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
uint8_t GPSvalidity											= 0;

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


// WSPR ------------------------------------------------------------------------------------------------------------------
uint8_t WSPRcallsign[6] = WSPR_CALLSIGN;
uint8_t WSPRlocator[6] = "JN99cl";


// MAIN ------------------------------------------------------------------------------------------------------------------
int main(void)
{
    // POWER-UP
    EEFC_setup(0, 2, 0, 0);																// Flash Wait State 2 + 1 (max. 64MHz)
    PS_SystemInit(15, 3, 5);															// MCK: 2MHz PLL
    WATCHDOG_enable(4095, 1);															// setup WatchDog with 16s period
    SysTick_delay_init();																// configure the delay timer
    LED_PA0_init();
    LED_PB5_init();
	ADC_init();
    
    // GPS SETUP
    UART1_init();
    SysTick_delay_ms(1000);																// give GPS time to be ready
    UBLOX_send_message(dummyByte, 1);													// wake up GPS module
    SysTick_delay_ms(1000);																// wait for GPS module to be ready
	UBLOX_send_message(resetReceiver, 12);												// reset GPS module
	SysTick_delay_ms(1000);																// wait for GPS module to be ready
    UBLOX_request_UBX(setNMEAoff, 28, 10, UBLOX_parse_ACK);								// turn off periodic NMEA output
    UBLOX_request_UBX(setNAVmode, 44, 10, UBLOX_parse_ACK);								// set Dynamic Model: airborne with <1g acceleration
    UBLOX_request_UBX(setGPSonly, 28, 10, UBLOX_parse_ACK);								// turn off GLONASS
    UBLOX_request_UBX(saveConfiguration, 21, 10, UBLOX_parse_ACK);						// save current configuration
    UART1_deinit();
	
	// WATCHDOG RESTART
	WATCHDOG_restart();
	
	// SI5351's LOAD SWITCH SETUP
	PMC->PMC_PCER0 |= (1 << ID_PIOA);													// enable clock to the peripheral
	PIOA->PIO_OER |= PIO_PA10;															// enable Output on PA10
	PIOA->PIO_PER |= PIO_PA10;															// enable PIO control on the pin (disable peripheral control)
	PIOA->PIO_PUDR |= PIO_PA10;															// disable pull-up
	PIOA->PIO_CODR |= PIO_PA10;															// Clear Output Data Register
    
    uint32_t cycleCount = 0;
	uint8_t WSPRtransmission = 0;														// flag informing about performed WSPR transmission
	uint8_t UART1error = 0;
	uint8_t TWIerror = 0;
	uint8_t SPIerror = 0;
	
    // MAIN LOOP
    while (1) 
    {
        // STATUS LED
        LED_PA0_blink(5);																// signal start of loop
        cycleCount++;
		
		// WATCHDOG RESTART
		WATCHDOG_restart();
        
        // GPS FIX
        uint32_t fixCount = 0;
        uint8_t TXaprs = 0;
		uint8_t UART1check = 0;
        
		UART1_init();
		UBLOX_send_message(dummyByte, 1);												// wake up GPS module
        SysTick_delay_ms(1000);															// wait for GPS module to be ready
		
        GPSnavigation = 0;
        UART1check = UBLOX_request_UBX(request0624, 8, 44, UBLOX_parse_0624);
		
		if(!UART1check) UART1error = 1;													// check UART1 - UBLOX MAX-7C link works
		else UART1error = 0;
        
        if(GPSnavigation != 6)															// verify Dynamic Model: airborne with <1g acceleration
        {
	        UBLOX_request_UBX(setNAVmode, 44, 10, UBLOX_parse_ACK);						// if not, set it
        }
        
        while(1)																		// poll UBX-NAV-PVT until the module has fix (limited)
        {
	        // WATCHDOG RESTART
	        WATCHDOG_restart();
	        
	        GPSfix = 0;
	        GPSfix_0107 = 0;
	        GPSsats = 0;
			GPSvalidity = 0;															// UTC Date and Time of Day validity
	        
	        UBLOX_request_UBX(request0107, 8, 92, UBLOX_parse_0107);					// old firmware UBLOX MAX-7C
	        if(GPSfix == 3 && GPSfix_0107 == 1 && GPSsats >= SATS && (GPSvalidity & 0x01)) break;		// 3D-fix, gnssFixOK, validDate
	        
	        fixCount++;
	        
	        if(fixCount > FIX)															// if taking too long reset and re-initialize GPS module
	        {
		        LED_PA0_blink(5);														// signal GPS module reset
		        SysTick_delay_ms(100);
		        LED_PA0_blink(5);
		        
		        UBLOX_send_message(resetReceiver, 12);									// reset GPS module
		        SysTick_delay_ms(1000);													// wait for GPS module to be ready
		        UBLOX_request_UBX(setNMEAoff, 28, 10, UBLOX_parse_ACK);					// turn off periodic NMEA output
		        UBLOX_request_UBX(setNAVmode, 44, 10, UBLOX_parse_ACK);					// set Dynamic Model: airborne with <1g acceleration
		        UBLOX_request_UBX(setGPSonly, 28, 10, UBLOX_parse_ACK);					// turn off GLONASS
		        UBLOX_request_UBX(saveConfiguration, 21, 10, UBLOX_parse_ACK);			// save current configuration
		        
		        GPSfix = 0;
		        GPSfix_0107 = 0;
		        GPSsats = 0;
		        break;
	        }
        }
		
		TXaprs = 1;																		// transmit APRS - always
		        
        // Si4060/Si4463 TEMPERATURE
        SPI_init();
        SI4060_init();
		
		SI4060_info();																	// check SPI - Si4060 link works 
		if(SI4060_buffer[2] == 0xFF) SPIerror = 1;
		else SPIerror = 0;
		
        Si4060Temp = SI4060_get_temperature();											// SPI and Si4060 need to be initialized first to get the temperature
        SI4060_deinit();
        SPI_deinit();
        
        // ADC READINGS
        ADC_start();
        AD3data = ADC_sample(3, 100);													// SOLAR PANEL voltage (solar panel connected to Vcap in this setup)
        AD9data = ADC_sample(9, 100);													// SUPERCAP voltage
        AD15data = ADC_sample_temperature(100);											// ATSAM3S8B's internal temperature
        ADC_stop();
        
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
        if(GPSnavigation == 6)			APRSbitfield |= (1 << 0);						// Nav bit (Airborne mode)
        if(GPSfix == 3)					APRSbitfield |= (1 << 1);						// Fix bit (GPS fix ok)
        if(WSPRtransmission == 1)		APRSbitfield |= (1 << 2);						// Wsp bit (WSPR transmission performed)
		if(UART1error == 1)				APRSbitfield |= (1 << 3);						// Urt bit (failed UART - GPS communication)
		if(TWIerror == 1)				APRSbitfield |= (1 << 4);						// Twi bit (failed TWI - Si5351 communication)
		if(SPIerror == 1)				APRSbitfield |= (1 << 5);						// Spi bit (failed SPI - Si4060 communication)
		WSPRtransmission = 0;
		TWIerror = 0;
        
        TC_rtty_gfsk_lookup				= 1;											// RTTY_INTERRUPT - 0; GFSK_SYNC - 1; - - 2; LOOKUP - 3
        APRS_send_path					= 2;											// send WIDE2-1 path (2)
        
        if(GPSfix)	APRS_packet_mode	= 1;											// full packet
        else		APRS_packet_mode	= 7;											// no position packet, just backlog and ADC readings
		
        APRS_packet_construct(APRSpacket);												// store the packet in APRSpacket
        
        // BACKLOG
        if((cycleCount % 20) == 0 && GPSfix == 3) APRS_store_backlog();					// save a new backlog to flash memory every x telemetry strings
        
        // GEOFENCE
        GEOFENCE_position(GPS_UBX_latitude_Float, GPS_UBX_longitude_Float);				// choose the right APRS frequency based on current location
        APRS_tx_frequency = GEOFENCE_APRS_frequency;
        if(GEOFENCE_no_tx) TXaprs = 0;													// disable APRS transmission in NO AIRBORNE areas
        
        // STATUS LED
        LED_PB5_blink(5);																// signal start of APRS transmission
        
        // FAST MCK
        PS_switch_MCK_to_FastRC(0, 0);													// MCK: 4MHz internal FastRC
        PS_SystemInit(15, 3, 2);														// MCK: 16MHz PLL
        
        // APRS TX
        if(TXaprs)
        {
	        SI4060_TX_power = POWER_LEVEL;												// TT7F6W (144MHz) 0x3C -> 16.55dBm at 44.0mA
			
			SPI_init();
	        SI4060_init();
	        SI4060_setup_pins(0x02, 0x04, 0x02, 0x02, 0x00, 0x00);
	        SI4060_frequency_offset(0);
	        SI4060_PA_mode(6, 0);														// Si4460: lower-power applications, Class-E or Square Wave match
	        SI4060_tx_APRS_GFSK_sync();													// transmit the packet using GFSK modulation
	        SI4060_deinit();
	        SPI_deinit();
        }
        
        // SLOW MCK
        PS_switch_MCK_to_FastRC(0, 0);													// MCK: 4MHz internal FastRC
        PS_SystemInit(15, 3, 5);														// MCK: 2MHz PLL
        		
        // WATCHDOG RESTART
        WATCHDOG_restart();
		
		// WSPR TIMING
		/*
			Transmission is scheduled every 10 minutes starting at the beginning of the fourth minute (4, 14, 24, 34, 44, 54).
			The first message is the standard WSPR message e.g. "OK7DMT JN99 10". 
			
			The second, the 6-digit LOCATOR (e.g. "<OK7DMT> JN99BL 10"), message follows in the next even minute WSPR window.
			That is 6, 16, 26, 36, 46, 56. It is timed by the SysTick delay function, so it is only as accurate as the crystal
			oscillator feeding MCK/PLL.
			
			Si5351 with XTAL (+-30ppm, -20°C to +70°C) will possibly drift +-420Hz (840Hz bandwidth) at 14MHz.
			Observed drift when taken out of freezer (-16°C) to room temperature (24°C) was 60Hz at 14MHz.
			
			Transmissions alternate between two frequencies in case the temperature drift takes one outside the WSPR band - diversification.
			Further, below certain temperature the frequency is offset by 50Hz and by another 50Hz below a second temperature limit.
		*/
		if(GPSfix == 3 && (GPSminute == 3 || GPSminute == 13 || GPSminute == 23 || GPSminute == 33 || GPSminute == 43 || GPSminute == 53))
		{
			// LOAD SWITCH - ON
			PIOA->PIO_SODR |= PIO_PA10;													// Set Output Data Register
			SysTick_delay_ms(100);
			
			// TEST WRITE TO SI5351
			uint8_t test = 0;
			TWI_init_master();
			
			test = SI5351_register_write(3, 0b11111111);
			
			if(test)			
			{
				TWIerror = 0;
				
				// WSPR FREQUENCY
				if(GPSminute == 3 || GPSminute == 23 || GPSminute == 43) SI5351frequency001Hz = 14097390000;	// adjusted for 215Hz offset at room temp
				else SI5351frequency001Hz = 14097315000;														// adjusted for 215Hz offset at room temp
				
				float tempLevel = (float)AD15data * 0.30402 - 265.15;
				if(tempLevel < -15.0) SI5351frequency001Hz += 50000;					// offset frequency by 50Hz below temperature level
				else if(tempLevel < -35.0) SI5351frequency001Hz += 100000;				// offset frequency by 100Hz below temperature level
				
				// CONSTRUCT WSPR STANDARD MESSAGE
				float WSPRlatitude = GPS_UBX_latitude_Float;
				float WSPRlongitude = GPS_UBX_longitude_Float;
				uint32_t WSPRaltitude = (uint32_t)GPSaltitude;
				
				WSPR_encode_msg(WSPRlatitude, WSPRlongitude, WSPRaltitude, WSPR_CALLSIGN);
				WSPR_create_tones();
			
				// TIME START OF MINUTE
				uint8_t WSPRtimeout = 0;												// waiting shouldn't take longer then ~60 UBX polls
				
				while(1)
				{
					WATCHDOG_restart();
				
					WSPRtimeout++;
				
					GPSfix = 0;
					UBLOX_request_UBX(request0107, 8, 92, UBLOX_parse_0107);			// old firmware UBLOX MAX-7C
					if(GPSsecond == 59 || WSPRtimeout > 70) break;						// wait for the 59th second or timeout
				}
			
				UBLOX_send_message(setBackupMode, 16);									// switch GPS module to backup mode (old firmware UBLOX MAX-7C)
				UART1_deinit();
				
				if(WSPRtimeout <= 70)													// transmit only if the timing worked out
				{
					// STATUS LED
					LED_PB5_blink(5);													// signal start of WSPR transmission
					SysTick_delay_ms(100);
					LED_PB5_blink(5);
					
					// ADDITIONAL DELAY DERIVED FROM TESTING
					SysTick_delay_ms(900);
			
					// TX WSPR STANDARD MESSAGE
					SI5351_init();
					SI5351_frequency(SI5351frequency001Hz);
					WSPR_transmit();
				
					// CONSTRUCT WSPR EXTENDED MESSAGE
					WSPR_encode_msg_extended(WSPRlatitude, WSPRlongitude, WSPRaltitude, WSPR_CALLSIGN);
					WSPR_create_tones();
			
					// TIME START OF MINUTE
					SysTick_delay_ms(8900);
				
					// TX WSPR EXTENDED MESSAGE
					WSPR_transmit();
					SI5351_deinit();
				
					WSPRtransmission = 1;												// WSPR transmission performed
				}
				else
				{
					WSPRtransmission = 0;
				}
				
				TWI_deinit();
				
				// LOAD SWITCH - OFF
				PIOA->PIO_CODR |= PIO_PA10;												// Clear Output Data Register
			}
			else
			{
				UBLOX_send_message(setBackupMode, 16);									// switch GPS module to backup mode (old firmware UBLOX MAX-7C)
				UART1_deinit();
				TWI_deinit();
				
				// LOAD SWITCH - OFF
				PIOA->PIO_CODR |= PIO_PA10;												// Clear Output Data Register
				
				TWIerror = 1;
				WSPRtransmission = 0;
			}
		}
		else
		{
			// GPS BACKUP
			UBLOX_send_message(setBackupMode, 16);										// switch GPS module to backup mode (old firmware UBLOX MAX-7C)
			UART1_deinit();
		}
		
		// LOW POWER CYCLE
		if(!WSPRtransmission)
		{
			WaitModeSeconds = SHORT_CYCLE;
			
			RTT_init(WaitModeSeconds, 0x8000, 0);										// Wait mode period in RC oscillator's seconds
			PS_switch_MCK_to_FastRC(0, 0);												// MCK: 4MHz internal FastRC
			PS_enter_Wait_Mode(1, 0, 0);												// enable wake up on RTT and enter wait mode
			RTT_off();																	// clear pending flag after wake-up
			PS_SystemInit(15, 3, 5);													// MCK: 2MHz PLL
		}
	}
}
