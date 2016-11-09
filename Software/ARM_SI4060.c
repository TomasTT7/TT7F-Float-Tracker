/*
 * ARM_SI4060.c
 *
 * Created: 20.6.2016 15:37:46
 *  Author: Tomy2
 */ 

#include "sam.h"
#include "ARM_SI4060.h"
#include "ARM_SPI.h"
#include "ARM_DELAY.h"


/*
	CLEAR TO SEND (CTS)
		 Checking CTS is used to make sure the internal MCU has executed the command and prepared the data to be output over the SDO pin.
*/
void SI4060_CTS_check_and_read(uint8_t response_length)
{
	uint16_t data;
	uint8_t dt = 0;
	uint32_t CTS_timeout = CTS_TIMEOUT;
	
	while(dt != 0xFF && CTS_timeout)
	{
		CTS_timeout--;
		SPI->SPI_CR = SPI_CR_SPIEN;									// enable SPI if disabled
		SPI_write(0x44, 0);											// READ_CMD_BUFF
		data = SPI_write(0x00, 0);
		dt = (uint8_t)data;
		if(dt == 0xFF) break;
		SPI->SPI_CR = SPI_CR_SPIDIS;								// workaround to de-assert chip select
	}
	
	SI4060_buffer[0] = dt;
	
	if(!CTS_timeout)
	{
		for(uint8_t i = 0; i < 16; i++) SI4060_buffer[i] = 0xFE;
	}
	else
	{
		if(response_length > 0)
		{
			if(response_length > 1)
			{
				for(uint8_t i = 1; i < (response_length - 1); i++)
				{
					SI4060_buffer[i] = SPI_write(0x00, 0);
				}
			}
			SI4060_buffer[response_length] = SPI_write(0x00, 1);
		}else{
			SPI->SPI_CR = SPI_CR_SPIDIS;							// workaround to de-assert chip select
		}
	}
}


/*
INITIALIZATION
	drive SDN HIGH for minimum of 10us (640 MCK cycles)
	then drive SDN LOW again
	Power on Reset (POR) requires 10ms to settle the circuit
	POWER_UP command is then required to initialize the radio
*/
void SI4060_init(void)
{
	// enable TCXO - PA8
	PMC->PMC_PCER0 |= (1 << ID_PIOA);			// enable clock to the peripheral
	PIOA->PIO_OER |= PIO_PA8;					// enable Output on PA8
	PIOA->PIO_PER |= PIO_PA8;					// enable PIO control on the pin (disable peripheral control)
	PIOA->PIO_PUDR |= PIO_PA8;					// disable pull-up
	PIOA->PIO_SODR |= PIO_PA8;					// Set Output Data Register
	
	// setup GPIO1 - PB4
	MATRIX->CCFG_SYSIO |= (1 << 4);				// System I/O lines must be configured in this register as well (PB4, PB5, PB6, PB7, PB10, PB11, PB12)
	PMC->PMC_PCER0 |= (1 << ID_PIOB);			// enable clock to the peripheral
	PIOB->PIO_OER |= PIO_PB4;					// enable Output on PB4
	PIOB->PIO_PER |= PIO_PB4;					// enable PIO control on the pin (disable peripheral control)
	PIOB->PIO_PUDR |= PIO_PB4;					// disable pull-up
	
	// setup SDN - PA7
	PIOA->PIO_OER |= PIO_PA7;					// enable Output on PA7
	PIOA->PIO_PER |= PIO_PA7;					// enable PIO control on the pin (disable peripheral control)
	PIOA->PIO_PUDR |= PIO_PA7;					// disable pull-up
	PIOA->PIO_SODR |= PIO_PA7;					// Set Output Data Register
	SysTick_delay_ms(1);
	PIOA->PIO_CODR |= PIO_PA7;					// Clear Output Data Register
	SysTick_delay_ms(10);
	
	// divide the XTAL/TCXO frequency into 4 bytes
	uint32_t tcxo1 = TCXO / 16777216;
	uint32_t tcxo2 = (TCXO - tcxo1 * 16777216) / 65536;
	uint32_t tcxo3 = (TCXO - tcxo1 * 16777216 - tcxo2 * 65536) / 256;
	uint32_t tcxo4 = (TCXO - tcxo1 * 16777216 - tcxo2 * 65536 - tcxo3 * 256);
	
	SPI_write(0x02, 0);							// POWER_UP - 15ms
	SPI_write(0x01, 0);
	SPI_write(0x01, 0);							// 0x00 - XTAL, 0x01 - TCXO
	SPI_write(tcxo1, 0);
	SPI_write(tcxo2, 0);
	SPI_write(tcxo3, 0);
	SPI_write(tcxo4, 1);
	SI4060_CTS_check_and_read(0);				// monitor CTS
	
	SPI_write(0x20, 0);							// GET_INT_STATUS
	SPI_write(0x00, 0);
	SPI_write(0x00, 0);
	SPI_write(0x00, 1);
	SI4060_CTS_check_and_read(9);				// monitor CTS
}


/*
	When shutting Si4060 down by using SDN pin, it consumes 7mA more than leaving SDN low (for some reason).
	Pulling pins up when shutting Si4060 down decreases consumption a little (omitting whichever pin doesn't influence consumption critically).
*/
void SI4060_deinit(void)
{
	SI4060_change_state(1);						// Sleep/Standby
	
	// disable TCXO - PA8
	PIOA->PIO_CODR |= PIO_PA8;					// Clear Output Data Register
	
	// enable pull-ups on pins used by SI4060
	PIOA->PIO_PUER |= PIO_PA8;					// TCXO
	PIOB->PIO_PUER |= PIO_PB4;					// GPIO1
	PIOA->PIO_PUER |= PIO_PA7;					// SDN
}


/*

*/
void SI4060_setup_pins(uint8_t gpio0, uint8_t gpio1, uint8_t gpio2, uint8_t gpio3, uint8_t nirq, uint8_t sdo)
{
	SPI_write(0x13, 0);							// GPIO_PIN_CFG
	SPI_write(gpio0, 0);						// GPIO0 - 0x02
	SPI_write(gpio1, 0);						// GPIO1 - 0x04 - pin is configured as a CMOS input
	SPI_write(gpio2, 0);						// GPIO2 - 0x02
	SPI_write(gpio3, 0);						// GPIO3 - 0x02
	SPI_write(nirq, 0);							// NIRQ - 0x00
	SPI_write(sdo, 0);							// SDO - 0x00 - possible to use as TX_DATA_CLK output for GFSK
	SPI_write(0x00, 1);							// GPIOs configured as outputs will have the highest drive strength
	SI4060_CTS_check_and_read(8);				// monitor CTS
}


/*

*/
void SI4060_frequency(uint32_t freq)
{
	// divider for PLL Synthesizer running at 3.6GHz
	uint8_t outdiv = 4;
	uint8_t band = 0;
	if (freq < 705000000UL) { outdiv = 6;  band = 1;};
	if (freq < 525000000UL) { outdiv = 8;  band = 2;};
	if (freq < 353000000UL) { outdiv = 12; band = 3;};
	if (freq < 239000000UL) { outdiv = 16; band = 4;};
	if (freq < 177000000UL) { outdiv = 24; band = 5;};
	
	uint32_t f_pfd = 2 * TCXO / outdiv;
	uint32_t n = ((uint32_t)(freq / f_pfd)) - 1;
	float ratio = (float)freq / (float)f_pfd;
	float rest = ratio - (float)n;
	uint32_t m = (uint32_t)(rest * 524288UL);
	uint32_t m2 = m / 0x10000;
	uint32_t m1 = (m - m2 * 0x10000) / 0x100;
	uint32_t m0 = (m - m2 * 0x10000 - m1 * 0x100);
	
	SPI_write(0x11, 0);							// SET_PROPERTY (cmd)
	SPI_write(0x20, 0);							// MODEM (group)
	SPI_write(0x01, 0);							// 1 (num_props)
	SPI_write(0x51, 0);							// MODEM_CLKGEN_BAND (start_prop)
	SPI_write(0b1000 + band, 1);				// (data)
	SI4060_CTS_check_and_read(0);
	
	SPI_write(0x11, 0);							// SET_PROPERTY (cmd)
	SPI_write(0x40, 0);							// FREQ_CONTROL (group)
	SPI_write(0x04, 0);							// 4 (num_props)
	SPI_write(0x00, 0);							// FREQ_CONTROL_INTE (start_prop)
	SPI_write(n, 0);							// (data) - FREQ_CONTROL_INTE
	SPI_write(m2, 0);							// (data) - FREQ_CONTROL_FRAC
	SPI_write(m1, 0);							// (data) - FREQ_CONTROL_FRAC
	SPI_write(m0, 1);							// (data) - FREQ_CONTROL_FRAC
	SI4060_CTS_check_and_read(0);
}


/*
	Faster then the previous function. Omits setting MODEM_CLKGEN_BAND.
	Intended for faster transitions between frequencies within one band.
*/
void SI4060_frequency_fast(uint32_t freq)
{
	// divider for PLL Synthesizer running at 3.6GHz
	uint8_t outdiv = 4;
	if (freq < 705000000UL) outdiv = 6;
	if (freq < 525000000UL) outdiv = 8;
	if (freq < 353000000UL) outdiv = 12;
	if (freq < 239000000UL) outdiv = 16;
	if (freq < 177000000UL) outdiv = 24;
	
	uint32_t f_pfd = 2 * TCXO / outdiv;
	uint32_t n = ((uint32_t)(freq / f_pfd)) - 1;
	float ratio = (float)freq / (float)f_pfd;
	float rest = ratio - (float)n;
	uint32_t m = (uint32_t)(rest * 524288UL);
	uint32_t m2 = m / 0x10000;
	uint32_t m1 = (m - m2 * 0x10000) / 0x100;
	uint32_t m0 = (m - m2 * 0x10000 - m1 * 0x100);
	
	SPI_write(0x11, 0);							// SET_PROPERTY (cmd)
	SPI_write(0x40, 0);							// FREQ_CONTROL (group)
	SPI_write(0x04, 0);							// 4 (num_props)
	SPI_write(0x00, 0);							// FREQ_CONTROL_INTE (start_prop)
	SPI_write(n, 0);							// (data) - FREQ_CONTROL_INTE
	SPI_write(m2, 0);							// (data) - FREQ_CONTROL_FRAC
	SPI_write(m1, 0);							// (data) - FREQ_CONTROL_FRAC
	SPI_write(m0, 1);							// (data) - FREQ_CONTROL_FRAC
	SI4060_CTS_check_and_read(0);
}


/*
	Specifies the deviation of the two frequencies of FSK and GFSK modulations.
*/
void SI4060_frequency_deviation(uint32_t deviation)
{	
	SPI_write(0x11, 0);							// SET_PROPERTY (cmd)
	SPI_write(0x20, 0);							// MODEM (group)
	SPI_write(0x03, 0);							// 3 (num_props)
	SPI_write(0x0A, 0);							// MODEM_FREQ_DEV (start_prop)
	SPI_write((deviation >> 16) & 0xFF, 0);		// (data) - MODEM_FREQ_DEV - usually 0x00
	SPI_write((deviation >> 8) & 0xFF, 0);		// (data) - MODEM_FREQ_DEV - usually 0x00
	SPI_write(deviation & 0xFF, 1);				// (data) - MODEM_FREQ_DEV - good for up to 2500Hz (at 144MHz) or 7700Hz (at 434MHz)
	SI4060_CTS_check_and_read(0);
}


/*
	Value is used to provide an offset to the programmed TX frequency. This allows fine tuning of the TX frequency to account
	for the variability of the TX reference frequency
*/
void SI4060_frequency_offset(uint32_t offset)
{
	SPI_write(0x11, 0);							// SET_PROPERTY (cmd)
	SPI_write(0x20, 0);							// MODEM (group)
	SPI_write(0x02, 0);							// 2 (num_props)
	SPI_write(0x0D, 0);							// MODEM_FREQ_OFFSET (start_prop)
	SPI_write((offset >> 8) & 0xFF, 0);			// (data) - MODEM_FREQ_OFFSET
	SPI_write(offset & 0xFF, 1);				// (data) - MODEM_FREQ_OFFSET
	SI4060_CTS_check_and_read(0);
}


/*
	Step size between two channels selected by SI4060_start_TX().
*/
void SI4060_channel_step_size(uint32_t step)
{
	SPI_write(0x11, 0);							// SET_PROPERTY (cmd)
	SPI_write(0x40, 0);							// FREQ_CONTROL (group)
	SPI_write(0x02, 0);							// 2 (num_props)
	SPI_write(0x04, 0);							// FREQ_CONTROL_CHANNEL_STEP_SIZE (start_prop)
	SPI_write((step >> 8) & 0xFF, 0);			// (data) - FREQ_CONTROL_CHANNEL_STEP_SIZE
	SPI_write(step & 0xFF, 1);					// (data) - FREQ_CONTROL_CHANNEL_STEP_SIZE
	SI4060_CTS_check_and_read(0);
}


/*
	DIRECT TX MODE the modulation is sourced in real-time from a GPIO1 pin.
	
	MOD:		CW 		0
				OOK 	1
				2FSK 	2
				2GFSK 	3
				4FSK 	4
				4GFSK 	5
	
	SYNCASYNC:	synchronous mode	0
				asynchronous mode	1
*/
void SI4060_modulation(uint8_t mod, uint8_t syncasync)
{
	SPI_write(0x11, 0);												// SET_PROPERTY (cmd)
	SPI_write(0x20, 0);												// MODEM (group)
	SPI_write(0x01, 0);												// 1 (num_props)
	SPI_write(0x00, 0);												// MODEM_MOD_TYPE (start_prop)
	SPI_write(((syncasync << 7) | (1 << 5) | (1 << 3) | mod), 1);	// (data) GPIO1 as the source of data (INPUT), TX Direct Mode
	SI4060_CTS_check_and_read(0);
}


/*
	Range:	0x00 (0)	0x61 (97)	0x7F (127)
			-40dBm		10dBm		13dBm
	
	Step Size:	~0.1dB
	
			Max Output Power	TX Current
	Si4060	+13dBm				+10dBm: 18mA (at 868MHz)
								+13dBm: 25mA (measured at 434MHz)
	Si4063	+20dBm				+20dBm: 70mA (at 169MHz)
								+20dBm: 75mA (at 460MHz)
								+20dBm: 85mA (at 915MHz)
*/
void SI4060_power_level(uint8_t val)
{
	SPI_write(0x11, 0);							// SET_PROPERTY (cmd)
	SPI_write(0x22, 0);							// PA (group)
	SPI_write(0x01, 0);							// 1 (num_props)
	SPI_write(0x01, 0);							// PA_PWR_LVL (start_prop)
	SPI_write(val, 1);							// (data)
	SI4060_CTS_check_and_read(0);
}


/*
	The chip can apply a spectral shaping filter function (e.g., Gaussian filtering) to the TX data stream.
	The filter is implemented as a 17-tap digital FIR filter. The values of the tap coefficients are symmetrical, only 9 are required.
	The spectral shaping filter function is used only in TX mode, and is not available when using TX Direct Asynchronous mode.
	
	Below are a few sets of coefficients I came across in different APRS trackers. Filters entitled as MY FILTER were made using
	a Python utility by UBSEDS and http://t-filter.engineerjs.com/ calculator.
	
	uint8_t filter[9] = {0x01,0x03,0x08,0x11,0x21,0x36,0x4D,0x60,0x67};			// default
	uint8_t filter[9] = {0x81,0x9F,0xC4,0xEE,0x18,0x3E,0x5C,0x70,0x76};			// UTRAK - 6dB@1200 Hz, 4400 Hz
	uint8_t filter[9] = {0x1d,0xe5,0xb8,0xaa,0xc0,0xf5,0x36,0x6b,0x7f};			// UTRAK - 6dB@1200 Hz, 2400 Hz
	uint8_t filter[9] = {0x07,0xde,0xbf,0xb9,0xd4,0x05,0x40,0x6d,0x7f};			// UTRAK - 3db@1200 Hz, 2400 Hz
	uint8_t filter[9] = {0xfa,0xe5,0xd8,0xde,0xf8,0x21,0x4f,0x71,0x7f};			// UTRAK - LP only, 2400 Hz
	uint8_t filter[9] = {0xd9,0xf1,0x0c,0x29,0x44,0x5d,0x70,0x7c,0x7f};			// UTRAK - LP only, 4800 Hz
	uint8_t filter[9] = {0xd5,0xe9,0x03,0x20,0x3d,0x58,0x6d,0x7a,0x7f};			// UTRAK - LP only, 4400 Hz
	uint8_t filter[9] = {0x19,0x21,0x07,0xC8,0x8E,0x9A,0xFB,0x75,0xAD};			// UBSEDS (FIR python)
	uint8_t filter[9] = {7, 10, 2, 238, 218, 222, 255, 40, 59};					// MY FILTER (FIR python) - no pre-emphasis
	uint8_t filter[9] = {6, 10, 6, 244, 224, 224, 251, 32, 50};					// MY FILTER (FIR python) - 6.14dB ripple
*/
void SI4060_filter_coeffs(void)
{
	uint8_t filter[9] = {6, 10, 6, 244, 224, 224, 251, 32, 50};					// MY FILTER (FIR python) - 6.14dB ripple
	
	SPI_write(0x11, 0);															// SET_PROPERTY (cmd)
	SPI_write(0x20, 0);															// MODEM (group)
	SPI_write(0x09, 0);															// 9 (num_props)
	SPI_write(0x0F, 0);															// MODEM_TX_FILTER_COEFF (start_prop)
	SPI_write(filter[8], 0);													// (data) - MODEM_TX_FILTER_COEFF_8
	SPI_write(filter[7], 0);													// (data) - MODEM_TX_FILTER_COEFF_7
	SPI_write(filter[6], 0);													// (data) - MODEM_TX_FILTER_COEFF_6
	SPI_write(filter[5], 0);													// (data) - MODEM_TX_FILTER_COEFF_5
	SPI_write(filter[4], 0);													// (data) - MODEM_TX_FILTER_COEFF_4
	SPI_write(filter[3], 0);													// (data) - MODEM_TX_FILTER_COEFF_3
	SPI_write(filter[2], 0);													// (data) - MODEM_TX_FILTER_COEFF_2
	SPI_write(filter[1], 0);													// (data) - MODEM_TX_FILTER_COEFF_1
	SPI_write(filter[0], 1);													// (data) - MODEM_TX_FILTER_COEFF_0
	SI4060_CTS_check_and_read(0);
}


/*
	The chip contains a TX Numerically Controlled Oscillator (NCO) for the purpose of creating an internal clock signal at a configurable
	multiple of the desired data rate. The oversampled NCO clock signal is used to synthesize the individual deviation steps of the Gaussian
	filtered modulation waveform.
	In 2GFSK or 4GFSK mode, the TXOSR value may be increased to 20x or 40x (from its nominal value of 10x). This increase in oversampling
	rate results in a Gaussian filtered modulation waveform with finer deviation steps.
	
	TX_DATA_RATE = (MODEM_DATA_RATE * FXTAL_HZ) / MODEM_TX_NCO_MODE / TXOSR
	Example: 1200 = (12000 * 32000000) / 32000000 / 10
*/
void SI4060_data_rate(uint32_t data_rate)
{
	uint8_t data_rate1 = (uint8_t)(data_rate >> 16);
	uint8_t data_rate2 = (uint8_t)(data_rate >> 8);
	uint8_t data_rate3 = (uint8_t)data_rate;
	
	SPI_write(0x11, 0);							// SET_PROPERTY (cmd)
	SPI_write(0x20, 0);							// MODEM (group)
	SPI_write(0x04, 0);							// 4 (num_props)
	SPI_write(0x06, 0);							// MODEM_TX_NCO_MODE (start_prop), Gaussian filter oversampling ratio derived from TCXO's frequency
	SPI_write(0x01, 0);							// (data) - MODEM_TX_NCO_MODE - TX Gaussian filter oversampling ratio is 10x.
	SPI_write(0xE8, 0);							// (data) - MODEM_TX_NCO_MODE
	SPI_write(0x48, 0);							// (data) - MODEM_TX_NCO_MODE
	SPI_write(0x00, 1);							// (data) - MODEM_TX_NCO_MODE - 32000000
	SI4060_CTS_check_and_read(0);
	
	SPI_write(0x11, 0);							// SET_PROPERTY (cmd)
	SPI_write(0x20, 0);							// MODEM (group)
	SPI_write(0x03, 0);							// 3 (num_props)
	SPI_write(0x03, 0);							// MODEM_DATA_RATE (start_prop)
	SPI_write(data_rate1, 0);					// (data) - MODEM_DATA_RATE
	SPI_write(data_rate2, 0);					// (data) - MODEM_DATA_RATE
	SPI_write(data_rate3, 1);					// (data) - MODEM_DATA_RATE
	SI4060_CTS_check_and_read(0);
}


/*
	NOCHANGE	0x00	No change, remain in current state.
	SLEEP		0x01 	SLEEP or STANDBY state.
	SPI_ACTIVE	0x02	SPI_ACTIVE state.
	READY		0x03	READY state.
	TX_TUNE		0x05	TX_TUNE state.
	TX			0x07	TX state.
*/
void SI4060_change_state(uint8_t state)
{
	SPI_write(0x34, 0);							// CHANGE_STATE
	SPI_write(state, 1);
	SI4060_CTS_check_and_read(0);
}


/*
	This command switches the chip to TX state and begins transmission of a packet.
*/
void SI4060_start_TX(uint8_t channel)
{
	SPI_write(0x31, 0);							// START_TX
	SPI_write(channel, 0);						// CHANNEL
	SPI_write((1 << 4) | 0x00, 0);				// CONDITION - 0x01 or 0x00 ??, (7 for TX_STATE, 1 for SLEEP_STATE)
	SPI_write(0x00, 0);							// TX_LEN
	SPI_write(0x00, 1);							// TX_DELAY
	SI4060_CTS_check_and_read(0);
}


/*
	byte 0 - CTS		0xFF
	byte 1 - CHIPREV	0x11
	byte 2 - PART		0x40
	byte 3 - PART		0x60
	byte 4 - PBUILD		0x00
	byte 5 - ID			0x00
	byte 6 - ID			0x0F
	byte 7 - CUSTOMER	0x00
	byte 8 - ROMID		0x00
*/
void SI4060_info(void)
{
	SPI_write(0x01, 0);							// PART_INFO
	SPI_write(0x00, 1);							// for some reason one byte commands need to be executed this way
	SI4060_CTS_check_and_read(9);
}


/*
	Used in combination with SI4060_RTTY_TX_string_TC0().
	Allows more precise timing and thus the use of higher BAUD RATES.
*/
void TC0_init_RTTY_NORMAL(void)
{
	// disable interrupt
	NVIC_DisableIRQ(TC0_IRQn);
	
	PMC->PMC_PCER0 |= (1 << ID_TC0);											// enable clock to the peripheral
	TC0->TC_CHANNEL[0].TC_CMR = (1 << 14) | (TIMER_CLOCK_RTTY << 0);			// CPCTRG, TIMER_CLOCK
	TC0->TC_CHANNEL[0].TC_RC = COMPARE_VALUE_RTTY;								// compare value
	TC0->TC_CHANNEL[0].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;					// enable the clock
}


/*

*/
void TC0_init_RTTY_INTERRUPT(void)
{
	// disable and clear any pending interrupt input before configuring it
	NVIC_DisableIRQ(TC0_IRQn);
	NVIC_ClearPendingIRQ(TC0_IRQn);
	NVIC_SetPriority(TC0_IRQn, 0);
	
	PMC->PMC_PCER0 |= (1 << ID_TC0);											// enable clock to the peripheral
	TC0->TC_CHANNEL[0].TC_CMR = (1 << 14) | (TIMER_CLOCK_RTTY << 0);			// CPCTRG, TIMER_CLOCK
	TC0->TC_CHANNEL[0].TC_RC = COMPARE_VALUE_RTTY;								// compare value
	TC0->TC_CHANNEL[0].TC_IER = (1 << 4);										// CPCS enable RC Compare interrupt
	TC0->TC_CHANNEL[0].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;					// enable the clock
	
	// enable interrupt input (system exceptions/interrupts don't use NVIC)
	NVIC_EnableIRQ(TC0_IRQn);
}


/*
	Set to 26400Hz to oversample both 1200Hz and 2200Hz sine waves.
*/
void TC0_init_APRS_GFSK_sync(void)
{
	// disable and clear any pending interrupt input before configuring it
	NVIC_DisableIRQ(TC0_IRQn);
	NVIC_ClearPendingIRQ(TC0_IRQn);
	NVIC_SetPriority(TC0_IRQn, 0);
	
	PMC->PMC_PCER0 |= (1 << ID_TC0);												// enable clock to the peripheral
	TC0->TC_CHANNEL[0].TC_CMR = (0x01 << 14) | (TIMER_CLOCK_GFSK_SYNC_TC0 << 0);	// CPCTRG, TIMER_CLOCK
	TC0->TC_CHANNEL[0].TC_RC = COMPARE_VALUE_GFSK_SYNC_TC0;							// compare value
	TC0->TC_CHANNEL[0].TC_IER = (1 << 4);											// CPCS enable RC Compare interrupt
	TC0->TC_CHANNEL[0].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;						// enable the clock
	
	// enable interrupt input (system exceptions/interrupts don't use NVIC)
	NVIC_EnableIRQ(TC0_IRQn);
}


/*
	Set to 1200Hz to signal the next bit.
*/
void TC0_init_APRS_GFSK_async(void)
{
	// disable and clear any pending interrupt input before configuring it
	NVIC_DisableIRQ(TC0_IRQn);
	NVIC_ClearPendingIRQ(TC0_IRQn);
	NVIC_SetPriority(TC0_IRQn, 0);
	
	PMC->PMC_PCER0 |= (1 << ID_TC0);												// enable clock to the peripheral
	TC0->TC_CHANNEL[0].TC_CMR = (0x01 << 14) | (TIMER_CLOCK_GFSK_ASYNC_TC0 << 0);	// CPCTRG, TIMER_CLOCK
	TC0->TC_CHANNEL[0].TC_RC = COMPARE_VALUE_GFSK_ASYNC_TC0;						// compare value
	TC0->TC_CHANNEL[0].TC_IER = (1 << 4);											// CPCS enable RC Compare interrupt
	TC0->TC_CHANNEL[0].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;						// enable the clock
	
	// enable interrupt input (system exceptions/interrupts don't use NVIC)
	NVIC_EnableIRQ(TC0_IRQn);
}


/*
	Set to either 2400Hz (for 1200Hz tone) or 4400Hz (for 2200Hz tone) to generate the sine waves.
	
	Naming of individual Timer Counter channels is somewhat confusing.
	
	ID_TC0	TC0_IRQn	TC0_Handler		located on:	TC0
	ID_TC1	TC1_IRQn	TC1_Handler		located on:	TC0
*/
void TC1_init_APRS_GFSK_async(void)
{
	// disable and clear any pending interrupt input before configuring it
	NVIC_DisableIRQ(TC1_IRQn);
	NVIC_ClearPendingIRQ(TC1_IRQn);
	NVIC_SetPriority(TC1_IRQn, 0);
	
	PMC->PMC_PCER0 |= (1 << ID_TC1);												// enable clock to the peripheral
	TC0->TC_CHANNEL[1].TC_CMR = (0x01 << 14) | (TIMER_CLOCK_GFSK_ASYNC_TC1 << 0);	// CPCTRG, TIMER_CLOCK
	TC0->TC_CHANNEL[1].TC_RC = COMPARE_VALUE_GFSK_ASYNC_TC1_1200;					// compare value
	TC0->TC_CHANNEL[1].TC_IER = (1 << 4);											// CPCS enable RC Compare interrupt
	TC0->TC_CHANNEL[1].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;						// enable the clock
	
	// enable interrupt input (system exceptions/interrupts don't use NVIC)
	NVIC_EnableIRQ(TC1_IRQn);
}


/*
	Set to 1200Hz to signal the next bit.
*/
void TC0_init_APRS_lookup(void)
{
	// disable and clear any pending interrupt input before configuring it
	NVIC_DisableIRQ(TC0_IRQn);
	NVIC_ClearPendingIRQ(TC0_IRQn);
	NVIC_SetPriority(TC0_IRQn, 0);
	
	PMC->PMC_PCER0 |= (1 << ID_TC0);											// enable clock to the peripheral
	TC0->TC_CHANNEL[0].TC_CMR = (0x01 << 14) | (TIMER_CLOCK_LOOKUP_TC0 << 0);	// CPCTRG, TIMER_CLOCK
	TC0->TC_CHANNEL[0].TC_RC = COMPARE_VALUE_LOOKUP_TC0;						// compare value
	TC0->TC_CHANNEL[0].TC_IER = (1 << 4);										// CPCS enable RC Compare interrupt
	TC0->TC_CHANNEL[0].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;					// enable the clock
	
	// enable interrupt input (system exceptions/interrupts don't use NVIC)
	NVIC_EnableIRQ(TC0_IRQn);
}


/*
	Set to 21739Hz to go through the lookup table.
*/
void TC1_init_APRS_lookup(void)
{
	// disable and clear any pending interrupt input before configuring it
	NVIC_DisableIRQ(TC1_IRQn);
	NVIC_ClearPendingIRQ(TC1_IRQn);
	NVIC_SetPriority(TC1_IRQn, 0);
	
	PMC->PMC_PCER0 |= (1 << ID_TC1);											// enable clock to the peripheral
	TC0->TC_CHANNEL[1].TC_CMR = (0x01 << 14) | (TIMER_CLOCK_LOOKUP_TC1 << 0);	// CPCTRG, TIMER_CLOCK
	TC0->TC_CHANNEL[1].TC_RC = COMPARE_VALUE_LOOKUP_TC1;						// compare value
	TC0->TC_CHANNEL[1].TC_IER = (1 << 4);										// CPCS enable RC Compare interrupt
	TC0->TC_CHANNEL[1].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;					// enable the clock
	
	// enable interrupt input (system exceptions/interrupts don't use NVIC)
	NVIC_EnableIRQ(TC1_IRQn);
}


/*
	RTTY_INTERRUPT
		TC0				50-1200Hz	Baud Rate dependent
	
	GFSK_SYNC
		TC0				26400Hz		(26400 interrupts per second)
		Baud Rate		1200		(every 22 interrupts)
		Slow Sine Wave	1200Hz		(1 full wave length per Baud) -> every 11 interrupts change of HIGH/LOW on PB4 to create a half of the full wave
		Fast Sine Wave	2200Hz		(1.83 wave length per Baud) -> every 6 interrupts change of HIGH/LOW on PB4 to create a half of the full wave
	
	GFSK_ASYNC
		TC0				1200Hz		Baud Rate
		TC1				2400Hz		1200Hz Sine Wave
		TC1				4400Hz		2200Hz Sine Wave
		
	LOOKUP
		TC0				1200Hz		Baud Rate
		TC1				21739Hz		As fast as Si4060 manages to apply modified frequency offset.
*/
void TC0_Handler(void)
{
	interruptStatusTC0 = TC0->TC_CHANNEL[0].TC_SR;							// read the Status Register and clear the interrupt
	
	
	// RTTY_INTERRUPT -----------------------------------------------------------------------------------------------------------------------
	if(TC_rtty_gfsk_lookup == 0)
	{
		switch(TXstate)
		{
			case TXPAUSE:													// optional delay between transmissions, TXpause * TC0 period
				TXdone_get_data = 0;
				if(TXpause) TXpause--;
				else{
					TXstate = TXSTARTBIT;
					TXbyte = SI4060_interrupt_TXbuffer[0];
					TXreload = 1;
				}
				break;
			
			case TXSTARTBIT:												// every character starts with a '0' start bit
				PIOB->PIO_CODR |= PIO_PB4;
				TXstopbits = 1;
				TXstate = TXBYTE;
				TXbit = TXBITS;
				break;
			
			case TXBYTE:													// transmission of individual character bits (7 or 8)
				if(TXbyte & 0x01) PIOB->PIO_SODR |= PIO_PB4;
				else PIOB->PIO_CODR |= PIO_PB4;
				TXbyte >>= 1;
				TXbit--;
				if(!TXbit) TXstate = TXSTOPBIT;
				break;
			
			case TXSTOPBIT:													// every character stops with two '1' stop bits
				if(TXstopbits) {PIOB->PIO_SODR |= PIO_PB4; TXstopbits = 0;}
				else{
					PIOB->PIO_SODR |= PIO_PB4;
					if(TXreload) TXstate = TXRELOAD;
					else TXstate = TXWAIT;
				}
				break;
			
			case TXRELOAD:													// loading the next byte of the message
				TXbyte = SI4060_interrupt_TXbuffer[TXreload];
				if((TXreload + 1) >= TXmessageLEN || (TXreload + 1) >= TX_BUFFER_SIZE) TXreload = 0;
				else TXreload++;
				TXstate = TXSTARTBIT;
				break;
			
			case TXWAIT:													// the routine waits for TXdata_ready flag to start a new transmission
				TXdone_get_data = 1;
				if(TXdata_ready)
				{
					for(uint32_t i = 0; i < TX_BUFFER_SIZE; i++)
					{
						SI4060_interrupt_TXbuffer[i] = TXbuffer[i];
					}
					TXdata_ready = 0;
					if(TXPAUSE == 0) TXstate = TXPAUSE;
					else {TXstate = TXPAUSE; TXpause = TXPAUSE - 1;}
				}
				break;
			
			default:
				break;
		}
	}
	
	
	// GFSK_SYNC ----------------------------------------------------------------------------------------------------------------------------
	else if(TC_rtty_gfsk_lookup == 1)
	{
		APRS_GFSK_TC0++;
		
		// serves to create the 1200Hz and 2200Hz sine waves -------------
		if(APRS_GFSK_Sine)
		{
			if(APRS_GFSK_TC0 == 6 || APRS_GFSK_TC0 == 12 || APRS_GFSK_TC0 == 18 || APRS_GFSK_TC0 == 22)	// 2200Hz
			{
				if(PIOB->PIO_ODSR && PIO_PB4) PIOB->PIO_CODR |= PIO_PB4;								// Clear Output Data Register - Si4060's GPIO1
				else PIOB->PIO_SODR |= PIO_PB4;															// Set Output Data Register - Si4060's GPIO1
			}
		}else{
			if(APRS_GFSK_TC0 == 11 || APRS_GFSK_TC0 == 22)												// 1200Hz
			{
				if(PIOB->PIO_ODSR && PIO_PB4) PIOB->PIO_CODR |= PIO_PB4;								// Clear Output Data Register - Si4060's GPIO1
				else PIOB->PIO_SODR |= PIO_PB4;															// Set Output Data Register - Si4060's GPIO1
			}
		}
		
		// operates the 1200 baud rate -----------------------------------
		if(APRS_GFSK_TC0 >= 22)
		{
			APRS_GFSK_TC0 = 0;
			APRS_bit = 1;
		}
	}
	
	
	// GFSK_ASYNC ---------------------------------------------------------------------------------------------------------------------------
	else if(TC_rtty_gfsk_lookup == 2)
	{
		APRS_bit = 1;
	}
	
	
	// LOOKUP -------------------------------------------------------------------------------------------------------------------------------
	else if(TC_rtty_gfsk_lookup == 3)
	{
		APRS_bit = 1;
	}
}


/*

*/
void TC1_Handler(void)
{
	interruptStatusTC1 = TC0->TC_CHANNEL[1].TC_SR;										// read the Status Register and clear the interrupt
	
	
	// RTTY_INTERRUPT -----------------------------------------------------------------------------------------------------------------------
	if(TC_rtty_gfsk_lookup == 0)
	{
		
	}
	
	
	// GFSK_SYNC ----------------------------------------------------------------------------------------------------------------------------
	else if(TC_rtty_gfsk_lookup == 1)
	{
		
	}
	
	
	// GFSK_ASYNC ---------------------------------------------------------------------------------------------------------------------------
	else if(TC_rtty_gfsk_lookup == 2)
	{
		if(PIOB->PIO_ODSR && PIO_PB4) PIOB->PIO_CODR |= PIO_PB4;						// Clear Output Data Register - Si4060's GPIO1
		else PIOB->PIO_SODR |= PIO_PB4;													// Set Output Data Register - Si4060's GPIO1
	}
	
	
	// LOOKUP -------------------------------------------------------------------------------------------------------------------------------
	else if(TC_rtty_gfsk_lookup == 3)
	{
		APRS_lookup_wave = 1;
	}
}


/*

*/
void TC0_stop(void)
{
	TC0->TC_CHANNEL[0].TC_IDR = (1 << 4);					// disable RC Compare interrupt
	TC0->TC_CHANNEL[0].TC_CCR = TC_CCR_CLKDIS;				// disable the clock
	PMC->PMC_PCDR0 |= (1 << ID_TC0);						// enable clock to the peripheral
}


/*
	
*/
void TC1_stop(void)
{
	TC0->TC_CHANNEL[1].TC_IDR = (1 << 4);					// disable RC Compare interrupt
	TC0->TC_CHANNEL[1].TC_CCR = TC_CCR_CLKDIS;				// disable the clock
	PMC->PMC_PCDR0 |= (1 << ID_TC1);						// enable clock to the peripheral
}


/*
	Function using SysTick_delay() while the radio stays on.
*/
void SI4060_tx_OOK_blips(uint32_t count, uint32_t duration, uint32_t delay)
{
	SI4060_modulation(1, 1);								// OOK, Asynchronous
	SI4060_change_state(7);									// TX
	for(uint32_t i = 0; i < count; i++)
	{
		PIOB->PIO_SODR |= PIO_PB4;							// Set Output Data Register
		SysTick_delay_ms(duration);
		PIOB->PIO_CODR |= PIO_PB4;							// Clear Output Data Register
		SysTick_delay_ms(delay);
	}
	SI4060_change_state(1);									// Sleep/Standby
}


/*
	Different implementation aimed at saving power. The radio gets turned off during the delays.
	
	State/Mode		Response Time to TX		Current in State/Mode
	Shutdown State		15ms					30 nA
	Standby State		440 ?s					50 nA
	Sleep State			440 ?s					900 nA
	SPI Active State	340 ?s					1.35 mA
	Ready State			126 ?s					1.8 mA
	TX Tune State		58 ?s					8mA
	TX State			—						18 mA (+10 dBm)
*/
void SI4060_tx_OOK_blips_PS(uint32_t count, uint32_t duration, uint32_t delay)
{
	SI4060_modulation(1, 1);								// OOK, Asynchronous
	
	for(uint32_t i = 0; i < count; i++)
	{
		SI4060_change_state(0x07);							// TX
		SysTick_delay_ms(duration);
		SI4060_change_state(0x01);							// Sleep/Standby
		SysTick_delay_ms(delay);
	}
}


/*
	Uses SysTick_delay_ms() to time the delays between individual bits and thus allows BAUD RATES only up to 200.
	
	TIMING x BAUD RATE
		Transmitting 50 bytes (550bits) RTTY 8N2.
		
		baud		s		SysTick_delay_ms
		50			11			20
		100			5.5			10
		200			2.75		5
		300			1.83		-
		600			0.92		-
		1200		0.46		-
*/
void SI4060_tx_RTTY_string_DELAY(uint8_t *string)
{
	uint8_t c;
	c = *string++;
	
	while(c != '\0')
	{
		PIOB->PIO_CODR |= PIO_PB4;								// clear GPIO1 - START BIT
		SysTick_delay_ms(TXDELAY_RTTY);
		for(uint8_t i = 0; i < TXBITS; i++)						// TX CHARACTER (7 or 8 bits)
		{
			if(c & 0x01)
			{
				PIOB->PIO_SODR |= PIO_PB4;						// set GPIO1
		}else{
				PIOB->PIO_CODR |= PIO_PB4;						// clear GPIO1
			}
			SysTick_delay_ms(TXDELAY_RTTY);
			c = c >> 1;
		}
		PIOB->PIO_SODR |= PIO_PB4;								// set GPIO1 - STOP BIT
		SysTick_delay_ms(TXDELAY_RTTY);
		PIOB->PIO_SODR |= PIO_PB4;								// set GPIO1 - STOP BIT
		SysTick_delay_ms(TXDELAY_RTTY);
		c = *string++;
	}
}


/*
	Used in combination with TC0_init_RTTY_NORMAL().
	As opposed to SI4060_RTTY_TX_string_DELAY() it uses TC0 to time the delays between individual bits.
*/
void SI4060_tx_RTTY_string_TC0(uint8_t *string)
{	
	uint8_t c;
	c = *string++;
	
	while(!(TC0->TC_CHANNEL[0].TC_SR & (0x01 << 4)));			// wait for CPCS flag - initial synchronization
	
	while(c != '\0')
	{
		PIOB->PIO_CODR |= PIO_PB4;								// clear GPIO1 - START BIT
		while(!(TC0->TC_CHANNEL[0].TC_SR & (0x01 << 4)));		// wait for CPCS flag - programmed delay
		for(uint8_t i = 0; i < TXBITS; i++)						// TX CHARACTER (7 or 8 bits)
		{
			if(c & 0x01)
			{
				PIOB->PIO_SODR |= PIO_PB4;						// set GPIO1
			}else{
				PIOB->PIO_CODR |= PIO_PB4;						// clear GPIO1
			}
			while(!(TC0->TC_CHANNEL[0].TC_SR & (0x01 << 4)));	// wait for CPCS flag - programmed delay
			c = c >> 1;
		}
		PIOB->PIO_SODR |= PIO_PB4;								// set GPIO1 - STOP BIT
		while(!(TC0->TC_CHANNEL[0].TC_SR & (0x01 << 4)));		// wait for CPCS flag - programmed delay
		PIOB->PIO_SODR |= PIO_PB4;								// set GPIO1 - STOP BIT
		while(!(TC0->TC_CHANNEL[0].TC_SR & (0x01 << 4)));		// wait for CPCS flag - programmed delay
		c = *string++;
	}
}


/*
	A routine to transmit an APRS packet present in the APRSpacket[] array. Uses GFSK modulation to create the 1200Hz and 2200Hz sine waves.
	
					TC0_init_GFSK()						SPI_init()
	64MHz		TIMER_CLOCK2		303				SPI_SCBR		32
	12MHz		TIMER_CLOCK1		227				SPI_SCBR		6
	
	When using different MCK speeds, the TC0 settings and SPI speed need to be adjusted. SPI must be fast enough (>2MHz) to be able to deliver
	the commands that shape the 'AFSK' sine wave on time. TC0 has to run at 26400Hz.
	
	Example:
		12MHz MCK, TC0 26.4kHz, 6MHz SPI, 7 * SPI byte (command to change SINE WAVE SPEED) -> should fit inside one TC0 interrupt firing
		The rest of the commands (bits and bytes switching) should at 12MHz MCK fit easily within one interrupt firing.
*/
void SI4060_tx_APRS_GFSK_sync(void)
{
	SI4060_modulation(3, 0);										// GFSK, synchronous
	SI4060_data_rate(0x002EE0);										// 12000 for 1200Hz sine wave and 22000 for 2200Hz sine wave
	SI4060_filter_coeffs();											// set up the FIR filter
	SI4060_frequency(APRS_tx_frequency);
	SI4060_frequency_deviation(TX_DEVIATION_APRS);
	SI4060_power_level(POWER_LEVEL);
	SI4060_change_state(0x07);
	
	TC0_init_APRS_GFSK_sync();										// set up the GFSK timer running at 26400Hz
	
	APRS_bit = 0;													// flag signaling the time for the next bit operated by the TC0_Handler()
	uint32_t APRSbyte = 0;											// holds the currently TXed byte's order within APRSpacket[]
	uint8_t bitStuffCounter = 0;									// counter of successive '1' bits to signal the time to insert the '0' stuffing bit
	uint8_t bitStuffFlag = 0;										// signals to insert a '0' into the bit stream
	uint8_t APRSpacketReady = 1;									// flag signaling the end of the packet within APRSpacket[]
	uint8_t bit = 0;												// counter for bits within one byte of the packet
	uint8_t dataByte = APRSpacket[APRSbyte];						// holds the currently TXed byte from APRSpacket[]
	uint8_t APRSstate = 0;											// used to signal that the current byte is an APRS FLAG 0x7E
	
	#ifdef BIT_DEBUG												// DEBUG: Used to verify that the packet was constructed properly on the bit level.
		uint32_t DEBUG_bit_rank = 0;
		uint8_t DEBUG_bits[1000];
	#endif															// BIT_DEBUG
	
	if(APRSpacket[APRSbyte] == 0x7E) APRSstate = 1;
	else APRSstate = 0;
	
	while(APRSpacketReady)											// handles switching between 1200Hz and 2200Hz sine waves while TXing APRS packet
	{
		
		// 2200Hz SINE WAVE
		if(SineWaveFast)											// SPI at this stage must operate quickly enough (2MHz verified to be enough)
		{
			SPI_write(0x11, 0);										// SET_PROPERTY (CMD)
			SPI_write(0x20, 0);										// MODEM (group)
			SPI_write(0x03, 0);										// 3 (num_props)
			SPI_write(0x03, 0);										// MODEM_DATA_RATE (start_prop)
			SPI_write(0x00, 0);										// (data) - MODEM_DATA_RATE
			SPI_write(0x55, 0);										// (data) - MODEM_DATA_RATE 0x55 (with custom FIR)
			SPI_write(0xF0, 1);										// (data) - MODEM_DATA_RATE 0xF0 (with custom FIR) - 22000
			SI4060_CTS_check_and_read(0);
			
			SineWaveFast = 0;
		}
		
		// 1200Hz SINE WAVE
		if(SineWaveSlow)											// SPI at this stage must operate quickly enough (2MHz verified to be enough)
		{
			SPI_write(0x11, 0);										// SET_PROPERTY (CMD)
			SPI_write(0x20, 0);										// MODEM (group)
			SPI_write(0x03, 0);										// 3 (num_props)
			SPI_write(0x03, 0);										// MODEM_DATA_RATE (start_prop)
			SPI_write(0x00, 0);										// (data) - MODEM_DATA_RATE
			SPI_write(0x2E, 0);										// (data) - MODEM_DATA_RATE 0x2E (with custom FIR)
			SPI_write(0xE0, 1);										// (data) - MODEM_DATA_RATE 0xE0 (with custom FIR) - 12000
			SI4060_CTS_check_and_read(0);	
			
			SineWaveSlow = 0;
		}
		
		// NEXT BIT
		if(APRS_bit)												// moving through APRSpacket[] bit by bit
		{
			
			// BIT STUFFING '0'
			if(bitStuffFlag)										// insert a '0' after five '1's
			{
				if(APRS_GFSK_Sine == 0)								// switch from 1200Hz to 2200Hz
				{
					SineWaveFast = 1;
					APRS_GFSK_Sine = 1;
				}else{												// switch from 2200Hz to 1200Hz
					SineWaveSlow = 1;
					APRS_GFSK_Sine = 0;
				}
				
				bitStuffCounter = 0;								// clear the counter
				bitStuffFlag = 0;									// clear the flag
				
				#ifdef BIT_DEBUG
					DEBUG_bits[DEBUG_bit_rank++] = 0;
				#endif												// BIT_DEBUG
				
			}
			else
			{
			
				// BIT '1'
				if(dataByte & 0x01)									// transmit LSB first
				{
					// in NRZI encoding '1' leaves the SINE WAVE's speed the same
					
					bitStuffCounter++;
					
					if(bitStuffCounter == 5 && APRSstate == 0)
					{
						bitStuffFlag = 1;							// signal five '1's in a row
					}
					
					bit++;											// shift to the next bit as with a regular '1'
					dataByte >>= 1;									// shift to the next bit as with a regular '1'
						
					#ifdef BIT_DEBUG
						DEBUG_bits[DEBUG_bit_rank++] = 1;
					#endif											// BIT_DEBUG
					
				}
			
				// BIT '0'
				else
				{
					// in NRZI encoding '0' represents a transition (change in SINE WAVE's speed)
				
					if(APRS_GFSK_Sine == 0)							// switch from 1200Hz to 2200Hz
					{
						SineWaveFast = 1;
						APRS_GFSK_Sine = 1;
					}else{											// switch from 2200Hz to 1200Hz
						SineWaveSlow = 1;
						APRS_GFSK_Sine = 0;
					}
				
					bitStuffCounter = 0;							// clear the counter
					bit++;											// shift to the next bit
					dataByte >>= 1;									// shift to the next bit
				
					#ifdef BIT_DEBUG
						DEBUG_bits[DEBUG_bit_rank++] = 0;
					#endif											// BIT_DEBUG
				}
			}
			
			// NEXT BYTE
			if(bit >= 8)											// signal the end of the current byte and load the next one
			{
				bit = 0;
				APRSbyte++;
				dataByte = APRSpacket[APRSbyte];
				
				if(APRSpacket[APRSbyte] == 0x7E) APRSstate = 1;		// flag
				else APRSstate = 0;									// normal byte
			}
			
			APRS_bit = 0;											// clear the flag
		}
		
		// END OF THE PACKET
		if(APRSbyte >= APRS_packet_size) APRSpacketReady = 0;		// signal the end of the packet
	}

	TC0_stop();
	SI4060_change_state(0x01);										// Sleep/Standby
	
	
	// DEBUG: Used to verify that the packet was on the bit level constructed properly.
	#ifdef BIT_DEBUG
		for(uint32_t i = 0; i < DEBUG_bit_rank; i++)
		{
			udi_cdc_putc(DEBUG_bits[i]+'0');
		}
	#endif															// BIT_DEBUG
}


/*
	A bit version of the previous function.
	
	Accepts an array such as:	buffer[] = {0,1,1,1,1,1,1,0...};
	
	STARTFLAGSEND:	The order of the last byte (bit) of 0x7E flag at the beginning of the message within the array has to be entered manually.
	ENDFLAGSSTART:	The order of the first byte (bit) of 0x7E flag at the end of the message has to be entered manually.
*/
void SI4060_tx_APRS_GFSK_sync_BITS(uint8_t * buffer, uint32_t startFlagsEnd, uint32_t endFlagsStart)
{
	SI4060_modulation(3, 0);										// GFSK, synchronous
	SI4060_data_rate(0x002EE0);										// 12000 for 1200Hz sine wave and 22000 for 2200Hz sine wave
	SI4060_filter_coeffs();											// set up the FIR filter
	SI4060_frequency(APRS_tx_frequency);
	SI4060_frequency_deviation(TX_DEVIATION_APRS);
	SI4060_power_level(POWER_LEVEL);
	SI4060_change_state(0x07);
	
	TC0_init_APRS_GFSK_sync();										// setup the GFSK timer running at 26400Hz
	
	// prepare TX
	APRS_bit = 0;													// flag signaling the time for the next bit operated by the TC0_Handler()
	uint32_t APRSbyte = 0;											// holds the currently TXed bit's order within buffer[]
	uint8_t bitStuffCounter = 0;									// counter of successive '1' bits to signal the time to insert the '0' stuffing bit
	uint8_t bitStuffFlag = 0;										// signals to insert a '0' into the bit stream
	uint8_t APRSpacketReady = 1;									// flag signaling the end of the packet within APRSpacket[]
	uint8_t bit = 0;												// flag signaling the next byte
	uint8_t APRSstate = 0;											// used to signal that the current byte is an APRS FLAG 0x7E
	
	while(APRSpacketReady)											// handles switching between 1200Hz and 2200Hz sine waves while TXing APRS packet
	{
		
		// 2200Hz SINE WAVE
		if(SineWaveFast)											// SPI at this stage must operate quickly enough (2MHz verified to be enough)
		{
			SPI_write(0x11, 0);										// SET_PROPERTY (CMD)
			SPI_write(0x20, 0);										// MODEM (group)
			SPI_write(0x03, 0);										// 3 (num_props)
			SPI_write(0x03, 0);										// MODEM_DATA_RATE (start_prop)
			SPI_write(0x00, 0);										// (data) - MODEM_DATA_RATE
			SPI_write(0x55, 0);										// (data) - MODEM_DATA_RATE 0x55 (with custom FIR)
			SPI_write(0xF0, 1);										// (data) - MODEM_DATA_RATE 0xF0 (with custom FIR) - 22000
			SI4060_CTS_check_and_read(0);
			
			SineWaveFast = 0;
		}
		
		// 1200Hz SINE WAVE
		if(SineWaveSlow)											// SPI at this stage must operate quickly enough (2MHz verified to be enough)
		{
			SPI_write(0x11, 0);										// SET_PROPERTY (CMD)
			SPI_write(0x20, 0);										// MODEM (group)
			SPI_write(0x03, 0);										// 3 (num_props)
			SPI_write(0x03, 0);										// MODEM_DATA_RATE (start_prop)
			SPI_write(0x00, 0);										// (data) - MODEM_DATA_RATE
			SPI_write(0x2E, 0);										// (data) - MODEM_DATA_RATE 0x2E (with custom FIR)
			SPI_write(0xE0, 1);										// (data) - MODEM_DATA_RATE 0xE0 (with custom FIR) - 12000
			SI4060_CTS_check_and_read(0);
			
			SineWaveSlow = 0;
		}
		
		// NEXT BIT
		if(APRS_bit)												// moving through APRSpacket[] bit by bit
		{
			
			// BIT STUFFING '0'
			if(bitStuffFlag)										// insert a '0' after five '1's
			{
				if(APRS_GFSK_Sine == 0)								// switch from 1200Hz to 2200Hz
				{
					SineWaveFast = 1;
					APRS_GFSK_Sine = 1;
				}else{												// switch from 2200Hz to 1200Hz
					SineWaveSlow = 1;
					APRS_GFSK_Sine = 0;
				}
				
				bitStuffCounter = 0;								// clear the counter
				bitStuffFlag = 0;									// clear the flag
			}
			else
			{
				
				// BIT '1'
				if(buffer[APRSbyte] & 0x01)							// transmit LSB first
				{
					// in NRZI encoding '1' leaves the SINE WAVE's speed the same
					
					bitStuffCounter++;
					
					if(bitStuffCounter == 5 && APRSstate == 0)
					{
						bitStuffFlag = 1;							// signal five '1's in a row
					}
					
					bit = 1;										// shift to the next bit as with a regular '1'
				}
			
				// BIT '0'
				else
				{
					// in NRZI encoding '0' represents a transition (change in SINE WAVE's speed)
				
					if(APRS_GFSK_Sine == 0)							// switch from 1200Hz to 2200Hz
					{
						SineWaveFast = 1;
						APRS_GFSK_Sine = 1;
					}else{											// switch from 2200Hz to 1200Hz
						SineWaveSlow = 1;
						APRS_GFSK_Sine = 0;
					}
				
					bitStuffCounter = 0;							// clear the counter
					bit = 1;										// shift to the next bit
				}
			}
				
			// NEXT BYTE
			if(bit)													// signal the end of the current byte and load the next one
			{
				bit = 0;
				APRSbyte++;
					
				if(APRSbyte < startFlagsEnd || APRSbyte >= endFlagsStart) APRSstate = 1;
				else APRSstate = 0;
			}
							
			APRS_bit = 0;											// clear the flag
		}
		
		// END OF THE PACKET
		if(APRSbyte >= APRS_packet_size) APRSpacketReady = 0;		// signal the end of the packet
	}
	
	TC0_stop();
	SI4060_change_state(0x01);										// Sleep/Standby
}


/*
	EXPERIMENTAL. Do NOT use! Doesn't work properly.
*/
void SI4060_tx_APRS_GFSK_async(void)
{
	SI4060_modulation(3, 0);										// GFSK, synchronous
	SI4060_data_rate(0x002EE0);										// 12000 for 1200Hz sine wave and 22000 for 2200Hz sine wave
	SI4060_filter_coeffs();											// set up the FIR filter
	SI4060_frequency(APRS_tx_frequency);
	SI4060_frequency_deviation(TX_DEVIATION_APRS);
	SI4060_power_level(POWER_LEVEL);
	SI4060_change_state(0x07);
	
	TC0_init_APRS_GFSK_async();										// set up the timer to run at 1200Hz - Baud Rate
	TC1_init_APRS_GFSK_async();										// set up the timer to run at 2400Hz or 4400Hz - Sine Wave
	
	APRS_bit = 0;													// flag signaling the time for the next bit operated by the TC0_Handler()
	GFSKwave = 0;													// current state off the SINE WAVE (0 - 1200Hz, 1 - 2200Hz)
	uint32_t APRSbyte = 0;											// holds the currently TXed byte's order within APRSpacket[]
	uint8_t bitStuffCounter = 0;									// counter of successive '1' bits to signal the time to insert the '0' stuffing bit
	uint8_t bitStuffFlag = 0;										// signals to insert a '0' into the bit stream
	uint8_t APRSpacketReady = 1;									// flag signaling the end of the packet within APRSpacket[]
	uint8_t bit = 0;												// counter for bits within one byte of the packet
	uint8_t dataByte = APRSpacket[APRSbyte];						// holds the currently TXed byte from APRSpacket[]
	uint8_t APRSstate = 0;											// used to signal that the current byte is an APRS FLAG 0x7E
	
	#ifdef BIT_DEBUG												// DEBUG: Used to verify that the packet was constructed properly on the bit level.
		uint32_t DEBUG_bit_rank = 0;
		uint8_t DEBUG_bits[1000];
	#endif															// BIT_DEBUG
	
	if(APRSpacket[APRSbyte] == 0x7E) APRSstate = 1;
	else APRSstate = 0;
	
	while(APRSpacketReady)											// handles switching between 1200Hz and 2200Hz sine waves while TXing APRS packet
	{
		
		// NEXT BIT
		if(APRS_bit)												// moving through APRSpacket[] bit by bit
		{
			
			// BIT STUFFING '0'
			if(bitStuffFlag)										// insert a '0' after five '1's
			{
				
				if(GFSKwave == 0)									// switch from 1200Hz to 2200Hz
				{
					TC0->TC_CHANNEL[1].TC_RC = COMPARE_VALUE_GFSK_ASYNC_TC1_2200;
					
					GFSKwave = 1;
					
					SPI_write(0x11, 0);								// SET_PROPERTY (CMD)
					SPI_write(0x20, 0);								// MODEM (group)
					SPI_write(0x03, 0);								// 3 (num_props)
					SPI_write(0x03, 0);								// MODEM_DATA_RATE (start_prop)
					SPI_write(0x00, 0);								// (data) - MODEM_DATA_RATE
					SPI_write(0x55, 0);								// (data) - MODEM_DATA_RATE 0x55 (with custom FIR)
					SPI_write(0xF0, 1);								// (data) - MODEM_DATA_RATE 0xF0 (with custom FIR) - 22000
					SI4060_CTS_check_and_read(0);
				}
				else												// switch from 2200Hz to 1200Hz
				{
					TC0->TC_CHANNEL[1].TC_RC = COMPARE_VALUE_GFSK_ASYNC_TC1_1200;
					
					GFSKwave = 0;
					
					SPI_write(0x11, 0);								// SET_PROPERTY (CMD)
					SPI_write(0x20, 0);								// MODEM (group)
					SPI_write(0x03, 0);								// 3 (num_props)
					SPI_write(0x03, 0);								// MODEM_DATA_RATE (start_prop)
					SPI_write(0x00, 0);								// (data) - MODEM_DATA_RATE
					SPI_write(0x2E, 0);								// (data) - MODEM_DATA_RATE 0x55 (with custom FIR)
					SPI_write(0xE0, 1);								// (data) - MODEM_DATA_RATE 0xF0 (with custom FIR) - 12000
					SI4060_CTS_check_and_read(0);
				}
				
				bitStuffCounter = 0;								// clear the counter
				bitStuffFlag = 0;									// clear the flag
				
				#ifdef BIT_DEBUG
					DEBUG_bits[DEBUG_bit_rank++] = 0;
				#endif												// BIT_DEBUG
				
			}
			else
			{
			
				// BIT '1'
				if(dataByte & 0x01)									// transmit LSB first
				{
					// in NRZI encoding '1' leaves the SINE WAVE's speed the same
					
					bitStuffCounter++;
					
					if(bitStuffCounter == 5 && APRSstate == 0)
					{
						bitStuffFlag = 1;							// signal five '1's in a row
					}

					bit++;											// shift to the next bit
					dataByte >>= 1;									// shift to the next bit
					
					#ifdef BIT_DEBUG
						DEBUG_bits[DEBUG_bit_rank++] = 1;
					#endif											// BIT_DEBUG
				}
				
				// BIT '0'
				else
				{
					// in NRZI encoding '0' represents a transition (change in SINE WAVE's speed)
					
					if(GFSKwave == 0)								// switch from 1200Hz to 2200Hz
					{
						TC0->TC_CHANNEL[1].TC_RC = COMPARE_VALUE_GFSK_ASYNC_TC1_2200;
					
						GFSKwave = 1;
						
						SPI_write(0x11, 0);							// SET_PROPERTY (CMD)
						SPI_write(0x20, 0);							// MODEM (group)
						SPI_write(0x03, 0);							// 3 (num_props)
						SPI_write(0x03, 0);							// MODEM_DATA_RATE (start_prop)
						SPI_write(0x00, 0);							// (data) - MODEM_DATA_RATE
						SPI_write(0x55, 0);							// (data) - MODEM_DATA_RATE 0x55 (with custom FIR)
						SPI_write(0xF0, 1);							// (data) - MODEM_DATA_RATE 0xF0 (with custom FIR) - 22000
						SI4060_CTS_check_and_read(0);
					}
					else											// switch from 2200Hz to 1200Hz
					{
						TC0->TC_CHANNEL[1].TC_RC = COMPARE_VALUE_GFSK_ASYNC_TC1_1200;
						
						GFSKwave = 0;
					
						SPI_write(0x11, 0);							// SET_PROPERTY (CMD)
						SPI_write(0x20, 0);							// MODEM (group)
						SPI_write(0x03, 0);							// 3 (num_props)
						SPI_write(0x03, 0);							// MODEM_DATA_RATE (start_prop)
						SPI_write(0x00, 0);							// (data) - MODEM_DATA_RATE
						SPI_write(0x2E, 0);							// (data) - MODEM_DATA_RATE 0x55 (with custom FIR)
						SPI_write(0xE0, 1);							// (data) - MODEM_DATA_RATE 0xF0 (with custom FIR) - 12000
						SI4060_CTS_check_and_read(0);
					}
				
					bitStuffCounter = 0;							// clear the counter
					bit++;											// shift to the next bit
					dataByte >>= 1;									// shift to the next bit
				
					#ifdef BIT_DEBUG
						DEBUG_bits[DEBUG_bit_rank++] = 0;
					#endif											// BIT_DEBUG
				}
			}
			
			// NEXT BYTE
			if(bit >= 8)											// signal the end of the current byte and load the next one
			{
				bit = 0;
				APRSbyte++;
				dataByte = APRSpacket[APRSbyte];
				
				if(APRSpacket[APRSbyte] == 0x7E) APRSstate = 1;		// flag
				else APRSstate = 0;									// normal byte
			}
			
			APRS_bit = 0;											// clear the flag
		}
		
		// END OF THE PACKET
		if(APRSbyte >= APRS_packet_size) APRSpacketReady = 0;		// signal the end of the packet		
	}

	TC1_stop();
	TC0_stop();
	SI4060_change_state(0x01);										// Sleep/Standby
	
	
	// DEBUG: Used to verify that the packet was on the bit level constructed properly.
	#ifdef BIT_DEBUG
	for(uint32_t i = 0; i < DEBUG_bit_rank; i++)
	{
		udi_cdc_putc(DEBUG_bits[i]+'0');
	}
	#endif															// BIT_DEBUG
}


/*
	Function to transmit the contents of APRSpacket[] by offsetting a CW based on a lookup table to create 1200Hz and 2200Hz sine waves.
	Bytes are transmitted LSB first with NRZI encoding (bit '1' leaves the sine wave speed as it is while bit '0' changes it).
	After every series of five '1' bits there is one extra '0' bit stuffed into the bit stream.
	Bit stuffing is not applied when transmitting the 0x7E FLAGS (0b01111110) which signal the start and the end of a packet.
*/
void SI4060_tx_APRS_look_up(void)
{
	SI4060_modulation(0, 1);										// uses CW asynchronous modulation
	SI4060_frequency(APRS_tx_frequency - FREQ_OFFSET);				// FREQ_OFFSET is applied to center the created sine wave on the desired frequency
	SI4060_power_level(POWER_LEVEL);
	SI4060_change_state(0x07);
	
	TC0_init_APRS_lookup();											// sets up TC0 at 1200Hz - Baud Rate
	TC1_init_APRS_lookup();											// sets up TC1 at 21739Hz - Sine Wave step
	
	APRS_bit = 0;													// flag signaling the time for the next bit operated by the TC0_Handler()
	APRS_lookup_wave = 0;											// flag signaling the next step within the Sine Wave's lookup table
	uint32_t APRSbyte = 0;											// holds the currently TXed byte's order within APRSpacket[]
	uint8_t bitStuffCounter = 0;									// counter of successive '1' bits to signal the time to insert the '0' stuffing bit
	uint8_t bitStuffFlag = 0;										// signals to insert a '0' into the bit stream
	uint8_t APRSpacketReady = 1;									// flag signaling the end of the packet within APRSpacket[]
	uint8_t bit = 0;												// counter for bits within one byte of the packet
	uint8_t dataByte = APRSpacket[APRSbyte];						// holds the currently TXed byte from APRSpacket[]
	uint8_t APRSstate = 0;											// used to signal that the current byte is an APRS FLAG 0x7E
	
	uint8_t table = 0;
	uint8_t tableStep = 14;											// 14 - slow (1200Hz), 26 - fast (2200Hz)
	
	if(APRSpacket[APRSbyte] == 0x7E) APRSstate = 1;
	else APRSstate = 0;
	
	while(APRSpacketReady)
	{
		if(APRS_bit)												// moving through APRSpacket[] bit by bit
		{
			
			// BIT STUFFING '0'
			if(bitStuffFlag)										// insert a '0' after five '1's
			{
				if(tableStep == 14) tableStep = 26;					// change the sine wave to 2200Hz
				else tableStep = 14;								// change the sine wave to 1200Hz
				
				bitStuffCounter = 0;								// clear the counter
				bitStuffFlag = 0;									// clear the flag
			}
			else
			{
				
				// BIT '1'
				if(dataByte & 0x01)									// transmit LSB first
				{
					// in NRZI encoding '1' leaves the SINE WAVE's speed the same
					
					bitStuffCounter++;
					
					if(bitStuffCounter == 5 && APRSstate == 0)
					{
						bitStuffFlag = 1;							// signal five '1's in a row
					}
					
					bit++;											// shift to the next bit
					dataByte >>= 1;									// shift to the next bit
				}
			
				// BIT '0'
				else
				{
					// in NRZI encoding '0' represents a transition (change in SINE WAVE's speed)
				
					if(tableStep == 14) tableStep = 26;				// change the sine wave to 2200Hz
					else tableStep = 14;							// change the sine wave to 1200Hz
								
					bitStuffCounter = 0;							// clear the counter
					bit++;											// shift to the next bit
					dataByte >>= 1;									// shift to the next bit
				}
				
				// NEXT BYTE
				if(bit >= 8)										// signal the end of the current byte and load the next one
				{
					bit = 0;
					APRSbyte++;
					dataByte = APRSpacket[APRSbyte];
				
					if(APRSpacket[APRSbyte] == 0x7E) APRSstate = 1;	// flag
					else APRSstate = 0;								// normal byte
				}
			}
			
			APRS_bit = 0;											// clear the flag
		}
		
		if(APRS_lookup_wave)										// servicing the Sine Wave formation and speed shifts
		{
			APRS_lookup_wave = 0;
			table += tableStep;
			SI4060_frequency_offset(SineLookUp[table] * 5);
		}
		
		if(APRSbyte >= APRS_packet_size) APRSpacketReady = 0;		// signal the end of the packet
	}
	
	TC0_stop();
	TC1_stop();
	SI4060_change_state(0x01);
}


/*
	A bit version of the previous function.
	
	Accepts an array such as:	buffer[] = {0,1,1,1,1,1,1,0...};
	
		STARTFLAGSEND:	The order of the last byte (bit) of 0x7E flag at the beginning of the message within the array has to be entered manually.
		ENDFLAGSSTART:	The order of the first byte (bit) of 0x7E flag at the end of the message has to be entered manually.
*/
void SI4060_tx_APRS_look_up_BITS(uint8_t * buffer, uint32_t startFlagsEnd, uint32_t endFlagsStart)
{
	SI4060_modulation(0, 1);										// uses CW asynchronous modulation
	SI4060_frequency(APRS_tx_frequency - FREQ_OFFSET);				// FREQ_OFFSET is applied to center the created sine wave on the desired frequency
	SI4060_power_level(POWER_LEVEL);
	SI4060_change_state(0x07);
	
	TC0_init_APRS_lookup();											// sets up TC0 at 1200Hz - Baud Rate
	TC1_init_APRS_lookup();											// sets up TC1 at 21739Hz - Sine Wave step
	
	APRS_bit = 0;													// flag signaling the time for the next bit operated by the TC0_Handler()
	APRS_lookup_wave = 0;											// flag signaling the next step within the Sine Wave's lookup table
	uint32_t APRSbyte = 0;											// holds the currently TXed byte's order within APRSpacket[]
	uint8_t bitStuffCounter = 0;									// counter of successive '1' bits to signal the time to insert the '0' stuffing bit
	uint8_t bitStuffFlag = 0;										// signals to insert a '0' into the bit stream
	uint8_t APRSpacketReady = 1;									// flag signaling the end of the packet within APRSpacket[]
	uint8_t bit = 0;												// flag signaling the next byte
	uint8_t APRSstate = 0;											// used to signal that it is currently processing an APRS FLAG 0x7E - no BITSTUFFING
	
	uint8_t table = 0;
	uint8_t tableStep = 14;											// 14 - slow (1200Hz), 26 - fast (2200Hz)
	
	#ifdef BIT_DEBUG												// DEBUG: Used to verify that the packet was constructed properly on the bit level.
		uint32_t DEBUG_bit_rank = 0;
		uint8_t DEBUG_bits[1000];
	#endif															// BIT_DEBUG
	
	while(APRSpacketReady)
	{
		if(APRS_bit)												// moving through APRSpacket[] bit by bit
		{
			
			if(bitStuffFlag)										// insert a '0' after five '1's
			{
				if(tableStep == 14) tableStep = 26;					// change the sine wave to 2200Hz
				else tableStep = 14;								// change the sine wave to 1200Hz
				
				bitStuffCounter = 0;								// clear the counter
				bitStuffFlag = 0;									// clear the flag
				
				#ifdef BIT_DEBUG
					DEBUG_bits[DEBUG_bit_rank++] = 0;
				#endif												// BIT_DEBUG
				
			}
			else
			{
				
				// BIT '1'
				if(buffer[APRSbyte] & 0x01)							// transmit LSB first
				{
					// in NRZI encoding '1' leaves the SINE WAVE's speed the same
					
					bitStuffCounter++;
				
					if(bitStuffCounter == 5 && APRSstate == 0)
					{
						bitStuffFlag = 1;							// signal five '1's in a row
					}
				
					bit = 1;										// shift to the next bit
				
					#ifdef BIT_DEBUG
						DEBUG_bits[DEBUG_bit_rank++] = 1;
					#endif											// BIT_DEBUG
				
				}
			
				// BIT '0'
				else
				{
					// in NRZI encoding '0' represents a transition (change in SINE WAVE's speed)
				
					if(tableStep == 14) tableStep = 26;				// change the sine wave to 2200Hz
					else tableStep = 14;							// change the sine wave to 1200Hz
				
					bitStuffCounter = 0;							// clear the counter
					bit = 1;										// shift to the next bit
				
					#ifdef BIT_DEBUG
						DEBUG_bits[DEBUG_bit_rank++] = 0;
					#endif											// BIT_DEBUG
				
				}
			
			}
			
			// NEXT BYTE
			if(bit)													// signal the end of the current byte and load the next one
			{
				bit = 0;
				APRSbyte++;
				
				if(APRSbyte < startFlagsEnd || APRSbyte >= endFlagsStart) APRSstate = 1;
				else APRSstate = 0;
			}
			
			APRS_bit = 0;											// clear the flag
		}
		
		if(APRS_lookup_wave)										// servicing the Sine Wave formation and speed shifts
		{
			APRS_lookup_wave = 0;
			
			table += tableStep;
			SI4060_frequency_offset(SineLookUp[table] * 5);
		}
		
		if(APRSbyte >= APRS_packet_size) APRSpacketReady = 0;		// signal the end of the packet
	}
	
	TC0_stop();
	TC1_stop();
	SI4060_change_state(0x01);
	
	
	// DEBUG: Used to verify that the packet was on the bit level constructed properly.
	#ifdef BIT_DEBUG
		for(uint32_t i = 0; i < DEBUG_bit_rank; i++)
		{
			udi_cdc_putc(DEBUG_bits[i]+'0');
		}
	#endif															// BIT_DEBUG
}


#ifdef SI4060_ORDINARY_GFSK


/*
	This function is for GFSK as such. It is not used in the APRS transmission.
	After initialization and changing state to TX, the SPI's SDO pin is used as TX_DATA_CLK output and a SAM3S8's interrupt fires on every new bit.
	This, however, disables the SPI communication to the Si4060 and requires a hard reset of the radio and re-initialization of SPI to re-establish
	communication with the radio.
*/
void SI4060_setup_ordinary_GFSK(void)
{
	SI4060_modulation(3, 0);								// GFSK, synchronous
	SI4060_frequency_deviation(TX_DEVIATION_APRS);			// 0x06E9 18kHz, 0x0625 16kHz
	SI4060_data_rate(0x002EE0);								// 13200Hz needed for creating 1200Hz and 2200Hz signal (0203A0 - 13200Hz, 00ABE0 - 4400Hz)
	SI4060_filter_coeffs();
	SI4060_power_level(POWER_LEVEL);						// 0x7F max
	SI4060_change_state(0x07);								// TX state
	SI4060_setup_pins(0x02, 0x04, 0x02, 0x02, 0x00, 0x10);	// enable TX_DATA_CLK output on SDO
	
	PMC->PMC_PCER0 |= (1 << ID_PIOA);						// enable clock for PIOA
	PIOA->PIO_IER |= (1 << 12);								// enable Pin Change interrupt
	PIOA->PIO_AIMER |= (1 << 12);							// additional interrupt modes enabled
	PIOA->PIO_ESR |= (1 << 12);								// edge interrupt selection
	PIOA->PIO_REHLSR |= (1 << 12);							// rising edge interrupt selection
	
	NVIC_EnableIRQ(PIOA_IRQn);
}


/*
	This is an Interrupt Handler for the SI4060_setup_GFSK() function.
	It receives TX_DATA_CLK output on SDO, detection of the rising edge of the signal.
*/
void PIOA_Handler(void)
{
	if(PIOA->PIO_ISR & (1 << 12))
	{
		// TX bit
		if(PIOB->PIO_ODSR && PIO_PB4) PIOB->PIO_CODR |= PIO_PB4;				// Clear Output Data Register
		else PIOB->PIO_SODR |= PIO_PB4;											// Set Output Data Register
	}
}


#endif // SI4060_ORDINARY_GFSK