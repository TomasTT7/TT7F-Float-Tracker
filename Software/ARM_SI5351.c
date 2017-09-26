/*
	
*/

#include "sam3s8b.h"
#include "ARM_TWI.h"
#include "ARM_SI5351.h"
#include <math.h>


/*
	Writes one byte to an 8-bit address.
*/
uint8_t SI5351_register_write(uint8_t address, uint8_t data)
{
	uint32_t timeout;
	
	TWI0->TWI_CR = TWI_CR_MSEN | TWI_CR_SVDIS;									// set master enable bit and slave mode disable bit
	TWI0->TWI_MMR = (SI5351_ADDRESS << 16) | (1 << 8);							// device address ADDR, internal device address length LEN 0/1/2/3
	TWI0->TWI_IADR = address;													// set internal address for device
	TWI0->TWI_CR = TWI_CR_START;
	
	timeout = TWI_TIMEOUT;
	TWI0->TWI_THR = data;														// send the data
	while (!(TWI0->TWI_SR & TWI_SR_TXRDY) && timeout) timeout--;
	if(!timeout) return 0;														// signal timeout
	
	TWI0->TWI_CR = TWI_CR_STOP;													// send STOP bit
	
	timeout = TWI_TIMEOUT;
	while (!(TWI0->TWI_SR & TWI_SR_TXCOMP) && timeout) timeout--;
	
	if(!timeout) return 0;														// signal timeout
	else return 1;																// signal transmission success
}


/*
	Reads and returns a byte from an 8-bit address.
*/
uint8_t SI5351_register_read(uint8_t address)
{
	uint8_t data;
	uint32_t timeout;
	
	TWI0->TWI_CR = TWI_CR_MSEN | TWI_CR_SVDIS;									// set master enable bit and slave mode disable bit
	TWI0->TWI_MMR = (SI5351_ADDRESS << 16) | (0 << 8);							// device address ADDR, internal device address length LEN 0/1/2/3
	TWI0->TWI_CR = TWI_CR_START | TWI_CR_STOP;
	
	timeout = TWI_TIMEOUT;
	TWI0->TWI_THR = address;
	while (!(TWI0->TWI_SR & TWI_SR_TXRDY) && timeout) timeout--;
	if(!timeout) return 0xFF;													// signal timeout
	timeout = TWI_TIMEOUT;
	while(!(TWI0->TWI_SR & TWI_SR_TXCOMP) && timeout) timeout--;
	if(!timeout) return 0xFF;													// signal timeout
	
	TWI0->TWI_CR = TWI_CR_MSEN | TWI_CR_SVDIS;									// set master enable bit and slave mode disable bit
	TWI0->TWI_MMR = TWI_MMR_MREAD | (SI5351_ADDRESS << 16) | (0 << 8);			// device address ADDR, internal device address length LEN 0/1/2/3
	TWI0->TWI_CR = TWI_CR_START | TWI_CR_STOP;
	
	timeout = TWI_TIMEOUT;
	while(!(TWI0->TWI_SR & TWI_SR_RXRDY) && timeout) timeout--;
	if(!timeout) return 0xFF;													// signal timeout
	data = (uint8_t)TWI0->TWI_RHR;												// get the data
	
	timeout = TWI_TIMEOUT;
	while(!(TWI0->TWI_SR & TWI_SR_TXCOMP) && timeout) timeout--;
	if(!timeout) return 0xFF;													// signal timeout
	
	return data;
}


/*
	Turns off the Si5351 module's CLK1 and CLK2 outputs, sets the CLK0's output power to ~25mW (?) and resets the PLLs.
*/
void SI5351_init(void)
{
	SI5351_register_write(3, 0b11111111);											// disable all CLKs
	SI5351_register_write(183, 0b11010010);											// 10pF (default) - ABM8G-25.000MHZ-B4Y-T (10pF, +-30ppm, -20°C +70°C)
	SI5351_register_write(9, 0b00000000);											// 0: OEB pin controls enable/disable state of CLKx output.
	SI5351_register_write(15, 0b00000000);											// Input Source for PLLs.
	SI5351_register_write(16, 0b00001111);											// CLK0: 8mA, PLLA, on
	SI5351_register_write(17, 0b10001100);											// CLK1: 2mA, PLLA, off
	SI5351_register_write(18, 0b10001100);											// CLK2: 2mA, PLLB, off
	SI5351_register_write(19, 0b10001100);											// CLK3: 2mA, PLLB, off
	SI5351_register_write(20, 0b10001100);											// CLK4: 2mA, PLLB, off
	SI5351_register_write(21, 0b10001100);											// CLK5: 2mA, PLLB, off
	SI5351_register_write(22, 0b10001100);											// CLK6: 2mA, PLLB, off
	SI5351_register_write(23, 0b10001100);											// CLK7: 2mA, PLLB, off
	SI5351_register_write(149, 0b00000000);											// Spread Spectrum disable.
	SI5351_register_write(187, 0b00000000);											// Disable Fanout.
	SI5351_register_write(177, 0b10100000);											// PLLB and PLLA reset
}


/*
	Turns off the CLK0 output.
*/
void SI5351_deinit(void)
{
	SI5351_register_write(3, 0b11111111);											// disable all CLKs
	SI5351_register_write(16, 0b10001100);											// CLK0: 2mA, PLLA, off
	SI5351_register_write(177, 0b10100000);											// PLLB and PLLA reset
}


/*
	Enables output on CLK0 and disables output on CLK1 and CLK2.
*/
void SI5351_start_TX(void)
{
	SI5351_register_write(3, 0b11111110);											// enable CLK0
}


/*
	Disables output on CLK0, CLK1 and CLK3 - all three output clocks on an Si5351A.
*/
void SI5351_stop_TX(void)
{
	SI5351_register_write(3, 0b11111111);											// disable CLK0
}


/*
	VCO frequency in the range of 600 to 900 MHz.
	Where (a+b/c) is in the range 15+0/1,048,575 to 90+0/1,048,575.
	
	Fvco = Fxtal * (a + b / c)
	
	MSNA_P1 - integer part of the PLLA Feedback Multisynth divider
	MSNA_P2 - numerator for the fractional part of the PLLA Feedback Multisynth divider
	MSNA_P3 - denominator for the fractional part of the PLLA Feedback Multisynth divider
*/
void SI5351_PLLA_frequency(uint64_t freqHZ)
{
	PLLAfreq = freqHZ;
	uint32_t a = freqHZ / XTALfreq;
	uint64_t b = (freqHZ % XTALfreq) * 1048575 / XTALfreq;
	uint32_t c = 1048575;
	uint32_t p1 = 128 * a + floor(128 * b / c) - 512;
	uint32_t p2 = 128 * b - c * floor(128 * b / c);
  
	SI5351_register_write(26, (c & 0x0000FF00) >> 8);								// MSNA_P3[15:8]
	SI5351_register_write(27, (c & 0x000000FF));									// MSNA_P3[7:0]
	SI5351_register_write(28, (p1 & 0x00030000) >> 16);								// MSNA_P1[17:16]
	SI5351_register_write(29, (p1 & 0x0000FF00) >> 8);								// MSNA_P1[15:8]
	SI5351_register_write(30, (p1 & 0x000000FF));									// MSNA_P1[7:0]
	SI5351_register_write(31, ((c & 0x000F0000) >> 12) | ((p2 & 0x000F0000) >> 16));	// MSNA_P3[19:16], MSNA_P2[19:16]
	SI5351_register_write(32, (p2 & 0x0000FF00) >> 8);								// MSNA_P2[15:8]
	SI5351_register_write(33, (p2 & 0x000000FF));									// MSNA_P2[7:0]
}


/*
	Where (a+b/c) is in the range 6+0/1,048,575 to 1800+0/1,048,575.
	
	Fout = Fvco / (Multisynth * R)
	Multisynth = a + b / c
	
	For Fvco=689929800Hz the range is 383,081Hz to 114,988,300Hz. Step size 0.3Hz (?).
	
	MS0_DIVBY4 - MS0 Divide by 4 Enable 0b00/0b11
	R0_DIV - R0 Output Divider: 1/2/4/8/16/32/64/128
	MS0_P1 - integer part of the Multi-Synth1 divider
	MS0_P2 - numerator for the fractional part of the MultiSynth1 Divider
	MS0_P3 - denominator for the fractional part of the MultiSynth0 Divider
*/
void SI5351_MS0_frequency(uint64_t freq001HZ)
{
	uint64_t a = (PLLAfreq * 1000) / freq001HZ;
	uint64_t b = (PLLAfreq * 1000 % freq001HZ) * 1048575 / freq001HZ;
	uint32_t c = 1048575;
	uint32_t p1 = 128 * a + floor(128 * b / c) - 512;
	uint32_t p2 = 128 * b - c * floor(128 * b / c);
  
	SI5351_register_write(42, 0xFF);												// MS0_P3[15:8]
	SI5351_register_write(43, 0xFF);												// MS0_P3[7:0]
	SI5351_register_write(44, (p1 & 0x00030000) >> 16);								// R0_DIV[2:0], MS0_DIVBY4[1:0], MS0_P1[17:16]
	SI5351_register_write(45, (p1 & 0x0000FF00) >> 8);								// MS0_P1[15:8]
	SI5351_register_write(46, (p1 & 0x000000FF));									// MS0_P1[7:0]
	SI5351_register_write(47, 0xF0 | ((p2 & 0x000F0000) >> 16));					// MS0_P3[19:16], MS0_P2[19:16]
	SI5351_register_write(48, (p2 & 0x0000FF00) >> 8);								// MS0_P2[15:8]
	SI5351_register_write(49, (p2 & 0x000000FF));									// MS0_P2[7:0]
}


/*
	VCO frequency in the range of 600 to 900 MHz.
	Where (a+b/c) is in the range 15+0/1,048,575 to 90+0/1,048,575.
	
	Fvco = Fxtal * (a + b / c)
	
	MSNA_P1 - integer part of the PLLA Feedback Multisynth divider
	MSNA_P2 - numerator for the fractional part of the PLLA Feedback Multisynth divider
	MSNA_P3 - denominator for the fractional part of the PLLA Feedback Multisynth divider
*/
void SI5351_PLLA_frequency_ABC(uint32_t a, uint32_t b, uint32_t c)
{
	uint32_t p1 = 128 * a + floor(128 * b / c) - 512;
	uint32_t p2 = 128 * b - c * floor(128 * b / c);
  
	SI5351_register_write(26, (c & 0x0000FF00) >> 8);								// MSNA_P3[15:8]
	SI5351_register_write(27, (c & 0x000000FF));									// MSNA_P3[7:0]
	SI5351_register_write(28, (p1 & 0x00030000) >> 16);								// MSNA_P1[17:16]
	SI5351_register_write(29, (p1 & 0x0000FF00) >> 8);								// MSNA_P1[15:8]
	SI5351_register_write(30, (p1 & 0x000000FF));									// MSNA_P1[7:0]
	SI5351_register_write(31, ((c & 0x000F0000) >> 12) | ((p2 & 0x000F0000) >> 16));	// MSNA_P3[19:16], MSNA_P2[19:16]
	SI5351_register_write(32, (p2 & 0x0000FF00) >> 8);								// MSNA_P2[15:8]
	SI5351_register_write(33, (p2 & 0x000000FF));									// MSNA_P2[7:0]
}


/*
	Where (a+b/c) is in the range 6+0/1,048,575 to 1800+0/1,048,575.
	
	Fout = Fvco / (Multisynth * R)
	Multisynth = a + b / c
	
	For Fvco=689929800Hz the range is 383,081Hz to 114,988,300Hz. Step size 0.3Hz (?).
	
	MS0_DIVBY4 - MS0 Divide by 4 Enable 0b00/0b11
	R0_DIV - R0 Output Divider: 1/2/4/8/16/32/64/128
	MS0_P1 - integer part of the Multi-Synth1 divider
	MS0_P2 - numerator for the fractional part of the MultiSynth1 Divider
	MS0_P3 - denominator for the fractional part of the MultiSynth0 Divider
*/
void SI5351_MS0_frequency_ABC(uint32_t a, uint32_t b, uint32_t c)
{
	uint32_t p2 = 128 * b - c * floor(128 * b / c);
	uint32_t p1 = 128 * a + floor(128 * b / c) - 512;
  
	SI5351_register_write(42, (c & 0x0000FF00) >> 8);								// MS0_P3[15:8]
	SI5351_register_write(43, (c & 0x000000FF));									// MS0_P3[7:0]
	SI5351_register_write(44, (p1 & 0x00030000) >> 16);								// R0_DIV[2:0], MS0_DIVBY4[1:0], MS0_P1[17:16]
	SI5351_register_write(45, (p1 & 0x0000FF00) >> 8);								// MS0_P1[15:8]
	SI5351_register_write(46, (p1 & 0x000000FF));									// MS0_P1[7:0]
	SI5351_register_write(47, ((c & 0x000F0000) >> 12) | ((p2 & 0x000F0000) >> 16));	// MS0_P3[19:16], MS0_P2[19:16]
	SI5351_register_write(48, (p2 & 0x0000FF00) >> 8);								// MS0_P2[15:8]
	SI5351_register_write(49, (p2 & 0x000000FF));									// MS0_P2[7:0]
}


/*
	Sets the defined VCO frequency (limits the range of available TX frequencies).
	Then sets the actual TX frequency (should be ensured the VCO frequency is right for it).
	
	Enter desired frequency * 1000.
*/
void SI5351_frequency(uint64_t freq001Hz)
{
	SI5351_PLLA_frequency(VCO_FREQUENCY);
	SI5351_MS0_frequency(freq001Hz);
}