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


//#define SI4060_RTTY_INTERRUPT
#define SI4060_GFSK

//#define BIT_DEBUG


#define TCXO 32000000UL
#define FREQUENCY_RTTY 434287000UL
#define FREQUENCY_APRS 144800000UL


/*
	MODEM_FREQ_DEV = (2^19 * outdiv * deviation_Hz) / (Npresc * TCXO_Hz)
	
	434MHz	[outdiv 8]		39		1200Hz			33		1000Hz			26	800Hz			16	450Hz
	144MHz	[outdiv 24]		1179	12000Hz			865		8800Hz			432	4400Hz			216	2200Hz			118	1200Hz
*/
#define TX_DEVIATION_RTTY 16 
#define TX_DEVIATION_APRS 1179
#define POWER_LEVEL 0x7F			// 0x00(0) - -40dBm, 0x61(97) - 10dBm, 0x7F(127) - 13dBm


// RTTY BOTH VERSIONS
/*
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
#define TXBAUD 2500
#define TIMER_CLOCK 3


// RTTY NORMAL VERSION (ms)
#define TXDELAY 10					// delay between bits for the SysTick_delay_ms() version


// RTTY INTERRUPT VERSION
#define TXTRANSPAUSE 0				// number of TC0 interrupts between transmissions
#define TXBITS 8					// 7 or 8 bits for ASCII characters
#define TXPAUSE 0
#define TXSTARTBIT 1
#define TXBYTE 2
#define TXSTOPBIT 3
#define TXRELOAD 4
#define TXWAIT 5
#define TX_BUFFER_SIZE 330


// GFSK
/*
	64MHz PLL		TIMER_CLOCK2 (0x01)		COMPARE_VALUE: 303 (~26400Hz)
	12MHz XTAL		TIMER_CLOCK1 (0x00)		COMPARE_VALUE: 227 (~26400Hz)
*/
#define COMPARE_VALUE_GFSK 303
#define TIMER_CLOCK_GFSK 0x01
#define APRS_BUFFER_SIZE 330


#define CTS_TIMEOUT 15000


extern volatile uint32_t SI4060_buffer[16];		// buffer for SI4060 response
extern volatile uint8_t TC0_gfsk_rtty;			// switch for the TC0_Handler (GFSK = 1, RTTY = 0)


// RTTY INTERRUPT VERSION
static volatile uint8_t SI4060_interrupt_TXbuffer[TX_BUFFER_SIZE];	// interrupt buffer for transmission strings
static volatile uint8_t TXstate = 5;
static volatile uint8_t TXpause = 0;
static volatile uint8_t TXstopbits = 1;								// 1 for 2 Stop Bits, 0 for 1 Stop Bit
static volatile uint8_t TXbyte = 0;									// byte to TX
static volatile uint8_t TXbit = TXBITS;								// number of bits per ASCII character
static volatile uint16_t TXreload;									// flag for loading the next byte
extern uint8_t TXbuffer[TX_BUFFER_SIZE];
extern volatile uint32_t TXdone_get_data;
extern volatile uint8_t TXdata_ready;								// flag for filling new data to SI4060_interrupt_TXbuffer
extern uint32_t TXmessageLEN;


// GFSK
static volatile uint8_t SineWaveFast = 0;							// flag signaling to switch Si4060 to the faster 2200Hz sine wave
static volatile uint8_t SineWaveSlow = 0;							// flag signaling to switch Si4060 to the slower 1200Hz sine wave
extern uint8_t APRSpacket[APRS_BUFFER_SIZE];						// array for the APRS packet
extern uint16_t APRS_packet_size;									// holds the length of the current APRS packet
extern volatile uint8_t APRSbit;									// flag signaling the time for the next bit operated by the TC0_Handler()
static uint32_t interruptStatus = 0;

#ifdef SI4060_GFSK
	static uint8_t GFSKsineSpeed = 0;								// variable holding the current sine wave speed: 0 - 1200Hz, 1 - 2200Hz
	static uint8_t GFSKbaud = 0;									// counter of TC0 interrupts responsible for timings of BAUD RATE and SINE WAVE
#endif // SI4060_GFSK


// Functions
void SI4060_CTS_check_and_read(uint8_t response_length);
void SI4060_init(void);
void SI4060_deinit(void);
void SI4060_setup_pins(uint8_t gpio0, uint8_t gpio1, uint8_t gpio2, uint8_t gpio3, uint8_t nirq, uint8_t sdo);
void SI4060_frequency(uint32_t freq);
void SI4060_frequency_deviation(uint32_t deviation);
void SI4060_frequency_offset(uint8_t offset1, uint8_t offset2);
void SI4060_channel_step_size(uint8_t step1, uint8_t step2);
void SI4060_modulation(uint8_t mod, uint8_t syncasync);
void SI4060_change_state(uint8_t state);
void SI4060_start_TX(uint8_t channel);
void SI4060_power_level(uint8_t val);
void SI4060_info(void);

void TC0_init_RTTY_NORMAL(void);
void TC0_Handler(void);
void TC0_stop(void);

void SI4060_OOK_blips(uint32_t count, uint32_t duration, uint32_t delay);
void SI4060_OOK_blips_PS(uint32_t count, uint32_t duration, uint32_t delay);
void SI4060_RTTY_TX_string_DELAY(uint8_t *string);
void SI4060_RTTY_TX_string_TC0(uint8_t *string);


#ifdef SI4060_RTTY_INTERRUPT
	void TC0_init_RTTY_INTERRUPT(void);
#endif // SI4060_RTTY_INTERRUPT


#ifdef SI4060_GFSK
	void SI4060_filter_coeffs(void);
	void SI4060_data_rate(uint32_t data_rate);
	void SI4060_setup_GFSK(void);
	//void PIOA_Handler(void);
	void TC0_init_GFSK(void);
	void SI4060_setup_GFSK_APRS(void);
#endif // SI4060_GFSK


#endif // ARM_SI4060_H_