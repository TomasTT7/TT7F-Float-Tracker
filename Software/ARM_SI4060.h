/*
SI4060 AND SAM3S8 WIRING
	GPIO1		PB4
	SDN			PA7		(pull down to GND - active, when driven HIGH - shut down)
	TCXOEN		PA8		(drive HIGH to power the TCXO)
	NPCS0		PA11	(automatically HIGH when SPI enabled)
	MISO		PA12
	MOSI		PA13
	SPCK		PA14
*/

#ifndef ARM_SI4060_H
#define ARM_SI4060_H

#include "stdint.h"


//#define BIT_DEBUG										// debug for APRS packets via USB serial


#define TCXO				32000000UL
#define FREQUENCY_RTTY		434287000UL
#define FREQUENCY_APRS		144800000UL
#define FREQ_OFFSET			3200						// Hz to subtract from FREQUENCY_APRS to center the modulation (APRS with Look Up Table)


/*
	MODEM_FREQ_DEV = (2^19 * OUTDIV * deviation_Hz) / (Npresc * TCXO_Hz)
	
	434MHz	[OUTDIV 8]		39		1200Hz			33		1000Hz			26	800Hz			16	450Hz
	144MHz	[OUTDIV 24]		1179	12000Hz			865		8800Hz			432	4400Hz			216	2200Hz			118	1200Hz
*/
#define TX_DEVIATION_RTTY	16 
#define TX_DEVIATION_APRS	1179


/*
	MAX		13dBm		0x7F	127
			10dBm		~0x32	~50
	MIN		-40dBm		0x00	0
		
	The relationship is NOT linear.
*/
#define POWER_LEVEL			0x7F


/*
	RTTY NORMAL and INTERRUPT versions.

					64MHz MCK			12MHz MCK
					TIMER_CLOCK4		TIMER_CLOCK2
					 
	BAUD RATE		compare value		compare value
	50				10000				30000
	100				5000				15000
	200				2500				7500
	300				1667				5000
	600				833					2500
	1200			417					1250
	
								TC_CMRx
	TIMER_CLOCK1	MCK/2		0
	TIMER_CLOCK2	MCK/8		1
	TIMER_CLOCK3	MCK/32		2
	TIMER_CLOCK4	MCK/128		3
	TIMER_CLOCK5	SLCK		4
*/
#define COMPARE_VALUE_RTTY		2500
#define TIMER_CLOCK_RTTY		0x03


// RTTY NORMAL VERSION (ms)
#define TXDELAY_RTTY		5							// delay between bits for the SysTick_delay_ms() version


// RTTY INTERRUPT VERSION
#define TXTRANSPAUSE		0							// number of TC0 interrupts between transmissions
#define TXBITS				8							// 7 or 8 bits for ASCII characters
#define TXPAUSE				0
#define TXSTARTBIT			1
#define TXBYTE				2
#define TXSTOPBIT			3
#define TXRELOAD			4
#define TXWAIT				5
#define TX_BUFFER_SIZE		330


/*
	APRS GFSK and LOOKUP versions.
		GFSK synchronous
		GFSK asynchronous
		LOOKUP
	
	64MHz PLL		TIMER_CLOCK2 (0x01)		COMPARE_VALUE: 6667		1200Hz
	64MHz PLL		TIMER_CLOCK2 (0x01)		COMPARE_VALUE: 3333		2400Hz
	64MHz PLL		TIMER_CLOCK2 (0x01)		COMPARE_VALUE: 1818		4400Hz
	64MHz PLL		TIMER_CLOCK2 (0x01)		COMPARE_VALUE: 368		21739Hz
	64MHz PLL		TIMER_CLOCK2 (0x01)		COMPARE_VALUE: 303		26400Hz
	
	12MHz XTAL		TIMER_CLOCK1 (0x00)		COMPARE_VALUE: 5000		1200Hz
	12MHz XTAL		TIMER_CLOCK1 (0x00)		COMPARE_VALUE: 2500		2400Hz
	12MHz XTAL		TIMER_CLOCK1 (0x00)		COMPARE_VALUE: 1364		4400Hz
	12MHz XTAL		TIMER_CLOCK1 (0x00)		COMPARE_VALUE: 276		21739Hz
	12MHz XTAL		TIMER_CLOCK1 (0x00)		COMPARE_VALUE: 227		26400Hz
*/
#define TIMER_CLOCK_GFSK_SYNC_TC0				0x00
#define COMPARE_VALUE_GFSK_SYNC_TC0				227				// 26400Hz

#define TIMER_CLOCK_GFSK_ASYNC_TC0				0x01
#define TIMER_CLOCK_GFSK_ASYNC_TC1				0x01
#define COMPARE_VALUE_GFSK_ASYNC_TC0			6667			// 
#define COMPARE_VALUE_GFSK_ASYNC_TC1_1200		3333			// 
#define COMPARE_VALUE_GFSK_ASYNC_TC1_2200		1818			// 

#define TIMER_CLOCK_LOOKUP_TC0					0x00
#define TIMER_CLOCK_LOOKUP_TC1					0x00
#define COMPARE_VALUE_LOOKUP_TC0				5000			// 1200Hz
#define COMPARE_VALUE_LOOKUP_TC1				276				// 21739Hz


#define APRS_BUFFER_SIZE						350
#define CTS_TIMEOUT								15000			// timeout for a while loop waiting for Si4060 response 


#define LOOKUP_TBL_MULTIPLIER					5				// factor to generate desired modulation width

/*
	Lookup table for APRS sine wave. Values are used as offset to the base frequency programmed in Si4060.
*/
static uint8_t SineLookUp[] = {
	128,131,134,137,140,144,147,150,153,156,159,162,165,168,171,174,177,179,182,185,188,191,193,196,199,201,204,206,209,211,213,216,
	218,220,222,224,226,228,230,232,234,235,237,239,240,241,243,244,245,246,248,249,250,250,251,252,253,253,254,254,254,255,255,255,
	255,255,255,255,254,254,254,253,253,252,251,250,250,249,248,246,245,244,243,241,240,239,237,235,234,232,230,228,226,224,222,220,
	218,216,213,211,209,206,204,201,199,196,193,191,188,185,182,179,177,174,171,168,165,162,159,156,153,150,147,144,140,137,134,131,
	128,125,122,119,116,112,109,106,103,100, 97, 94, 91, 88, 85, 82, 79, 77, 74, 71, 68, 65, 63, 60, 57, 55, 52, 50, 47, 45, 43, 40,
	 38, 36, 34, 32, 30, 28, 26, 24, 22, 21, 19, 17, 16, 15, 13, 12, 11, 10,  8,  7,  6,  6,  5,  4,  3,  3,  2,  2,  2,  1,  1,  1,
	  1,  1,  1,  1,  2,  2,  2,  3,  3,  4,  5,  6,  6,  7,  8, 10, 11, 12, 13, 15, 16, 17, 19, 21, 22, 24, 26, 28, 30, 32, 34, 36,
	 38, 40, 43, 45, 47, 50, 52, 55, 57, 60, 63, 65, 68, 71, 74, 77, 79, 82, 85, 88, 91, 94, 97,100,103,106,109,112,116,119,122,125
	};


// VARIABLES
extern volatile uint32_t SI4060_buffer[16];							// buffer for SI4060 response


/*
	TC0_Handler and TC1_Handler switch.
	
	RTTY_INTERRUPT		0
	GFSK_SYNC			1
	GFSK_ASYNC			2
	LOOKUP				3
*/
extern volatile uint8_t TC_rtty_gfsk_lookup;


// RTTY
static volatile uint8_t SI4060_interrupt_TXbuffer[TX_BUFFER_SIZE];	// interrupt buffer for transmission strings
static volatile uint8_t TXstate = 5;
static volatile uint8_t TXpause = 0;
static volatile uint8_t TXstopbits = 1;								// 1 for 2 Stop Bits, 0 for 1 Stop Bit
static volatile uint8_t TXbyte = 0;									// byte to TX
static volatile uint8_t TXbit = TXBITS;								// number of bits per ASCII character
static volatile uint16_t TXreload;									// flag for loading the next byte

extern volatile uint32_t TXdone_get_data;
extern volatile uint8_t TXdata_ready;								// flag for filling new data to SI4060_interrupt_TXbuffer
extern uint32_t TXmessageLEN;
extern uint8_t TXbuffer[TX_BUFFER_SIZE];


// APRS
static uint32_t interruptStatusTC0 = 0;
static uint32_t interruptStatusTC1 = 0;
static volatile uint8_t APRS_bit = 0;								// flag signaling the time for the next bit operated by the TC0_Handler()

static volatile uint8_t APRS_GFSK_Sine = 0;							// variable holding the current sine wave speed: 0 - 1200Hz, 1 - 2200Hz
static volatile uint8_t APRS_GFSK_TC0 = 0;							// counter of TC0 interrupts responsible for timings of BAUD RATE and SINE WAVE
static uint8_t SineWaveFast = 0;									// flag signaling to switch Si4060 to the faster 2200Hz sine wave
static uint8_t SineWaveSlow = 0;									// flag signaling to switch Si4060 to the slower 1200Hz sine wave

static uint8_t GFSKwave = 0;										// current state off the SINE WAVE (0 - 1200Hz, 1 - 2200Hz)

static volatile uint8_t APRS_lookup_wave = 0;

extern uint16_t APRS_packet_size;									// holds the length of the current APRS packet
extern uint8_t APRSpacket[APRS_BUFFER_SIZE];						// array for the APRS packet

extern uint32_t APRS_tx_frequency;


// Functions
void SI4060_CTS_check_and_read(uint8_t response_length);
void SI4060_init(void);
void SI4060_deinit(void);
void SI4060_setup_pins(uint8_t gpio0, uint8_t gpio1, uint8_t gpio2, uint8_t gpio3, uint8_t nirq, uint8_t sdo);
void SI4060_frequency(uint32_t freq);
void SI4060_frequency_fast(uint32_t freq);
void SI4060_frequency_deviation(uint32_t deviation);
void SI4060_frequency_offset(uint32_t offset);
void SI4060_channel_step_size(uint32_t step);
void SI4060_modulation(uint8_t mod, uint8_t syncasync);
void SI4060_power_level(uint8_t val);
void SI4060_filter_coeffs(void);
void SI4060_data_rate(uint32_t data_rate);
void SI4060_change_state(uint8_t state);
void SI4060_start_TX(uint8_t channel);
void SI4060_info(void);
uint16_t SI4060_get_temperature(void);

void TC0_init_RTTY_NORMAL(void);
void TC0_init_RTTY_INTERRUPT(void);
void TC0_init_APRS_GFSK_sync(void);
void TC0_init_APRS_GFSK_async(void);
void TC1_init_APRS_GFSK_async(void);
void TC0_init_APRS_lookup(void);
void TC1_init_APRS_lookup(void);
void TC0_Handler(void);
void TC1_Handler(void);
void TC0_stop(void);
void TC1_stop(void);

void SI4060_tx_OOK_blips(uint32_t count, uint32_t duration, uint32_t delay);
void SI4060_tx_OOK_blips_PS(uint32_t count, uint32_t duration, uint32_t delay);
void SI4060_tx_RTTY_string_DELAY(uint8_t *string);
void SI4060_tx_RTTY_string_TC0(uint8_t *string);
void SI4060_tx_APRS_GFSK_sync(void);
void SI4060_tx_APRS_GFSK_sync_BITS(uint8_t * buffer, uint32_t startFlagsEnd, uint32_t endFlagsStart);
void SI4060_tx_APRS_GFSK_async(void);
void SI4060_tx_APRS_look_up(void);
void SI4060_tx_APRS_look_up_BITS(uint8_t * buffer, uint32_t startFlagsEnd, uint32_t endFlagsStart);


//#define SI4060_ORDINARY_GFSK

#ifdef SI4060_ORDINARY_GFSK
	void SI4060_setup_ordinary_GFSK(void);
	void PIOA_Handler(void);
#endif // SI4060_ORDINARY_GFSK


#endif // ARM_SI4060_H_