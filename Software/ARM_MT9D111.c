/*
 * ARM_MT9D111.c
 *
 * Created: 21.6.2016 11:02:42
 *  Author: Tomy2
 */ 

#include "sam.h"
#include "ARM_MT9D111.h"
#include "ARM_SSDV.h"
#include "ARM_TWI.h"
#include "ARM_DELAY.h"
#include "ARM_SI4060.h"
#include "ARM_PIODC.h"
#include "ARM_UBLOX.h"
#include "ARM_ADC.h"


/*

*/
uint8_t MT9D111_test_write(uint8_t address, uint16_t data)
{
	TWI0->TWI_CR = TWI_CR_MSEN | TWI_CR_SVDIS; // set master enable bit and slave mode disable bit
	TWI0->TWI_MMR = (DEVICE_ADDRESS << 16) | (1 << 8); // device address ADDR, internal device address length LEN 0/1/2/3
	TWI0->TWI_IADR = address; // set internal address for device
	TWI0->TWI_CR = TWI_CR_START;
	
	uint32_t status = 0;
	
	uint32_t timeout = TWI_TIMEOUT;
	TWI0->TWI_THR = data >> 8;
	while (!(status & TWI_SR_TXRDY) && timeout)
	{
		status = TWI0->TWI_SR;
		if(status & TWI_SR_NACK) return 0;
		timeout--;
	}
	
	timeout = TWI_TIMEOUT;
	TWI0->TWI_THR = data;
	while (!(status & TWI_SR_TXRDY) && timeout)
	{
		status = TWI0->TWI_SR;
		if(status & TWI_SR_NACK) return 0;
		timeout--;
	}

	TWI0->TWI_CR = TWI_CR_STOP; // send STOP bit
	timeout = TWI_TIMEOUT;
	while (!(status & TWI_SR_TXCOMP) && timeout)
	{
		status = TWI0->TWI_SR;
		if(status & TWI_SR_NACK) return 0;
		timeout--;
	}
	
	return 1;
}


/*

*/
void MT9D111_register_write(uint8_t address, uint16_t data)
{
	TWI0->TWI_CR = TWI_CR_MSEN | TWI_CR_SVDIS; // set master enable bit and slave mode disable bit
	TWI0->TWI_MMR = (DEVICE_ADDRESS << 16) | (1 << 8); // device address ADDR, internal device address length LEN 0/1/2/3
	TWI0->TWI_IADR = address; // set internal address for device
	TWI0->TWI_CR = TWI_CR_START;
	
	uint32_t timeout = TWI_TIMEOUT;
	TWI0->TWI_THR = data >> 8;
	while (!(TWI0->TWI_SR & TWI_SR_TXRDY) && timeout) timeout--;

	timeout = TWI_TIMEOUT;
	TWI0->TWI_THR = data;
	while (!(TWI0->TWI_SR & TWI_SR_TXRDY) && timeout) timeout--;

	TWI0->TWI_CR = TWI_CR_STOP; // send STOP bit
	timeout = TWI_TIMEOUT;
	while (!(TWI0->TWI_SR & TWI_SR_TXCOMP) && timeout) timeout--;
}


/*

*/
uint16_t MT9D111_register_read(uint8_t address)
{
	uint16_t data;
	uint32_t timeout;
	
	TWI0->TWI_CR = TWI_CR_MSEN | TWI_CR_SVDIS; // set master enable bit and slave mode disable bit
	TWI0->TWI_MMR = (DEVICE_ADDRESS << 16) | (0 << 8); // device address ADDR, internal device address length LEN 0/1/2/3
	TWI0->TWI_CR = TWI_CR_START | TWI_CR_STOP;
	
	timeout = TWI_TIMEOUT;
	TWI0->TWI_THR = address;
	while (!(TWI0->TWI_SR & TWI_SR_TXRDY) && timeout) timeout--;
	timeout = TWI_TIMEOUT;
	while(!(TWI0->TWI_SR & TWI_SR_TXCOMP) && timeout) timeout--;
	
	TWI0->TWI_CR = TWI_CR_MSEN | TWI_CR_SVDIS; // set master enable bit and slave mode disable bit
	TWI0->TWI_MMR = TWI_MMR_MREAD | (DEVICE_ADDRESS << 16) | (0 << 8); // device address ADDR, internal device address length LEN 0/1/2/3
	TWI0->TWI_CR = TWI_CR_START;
	
	timeout = TWI_TIMEOUT;
	while(!(TWI0->TWI_SR & TWI_SR_RXRDY) && timeout) timeout--;
	data = (uint8_t)TWI0->TWI_RHR;
	data <<= 8;
	
	TWI0->TWI_CR = TWI_CR_STOP;
	
	timeout = TWI_TIMEOUT;
	while(!(TWI0->TWI_SR & TWI_SR_RXRDY) && timeout) timeout--;
	data |= (uint8_t)TWI0->TWI_RHR;
	
	timeout = TWI_TIMEOUT;
	while(!(TWI0->TWI_SR & TWI_SR_TXCOMP) && timeout) timeout--;
	
	return data;
}


/*
	size 8bit - 1 / 16bit - 0, [15:0] s01IDIDIDIDIDOFOFOFOFOFOFOFOF
*/
void MT9D111_variable_write(uint8_t driverID, uint8_t offset, uint8_t size, uint16_t val)
{
	uint16_t data = 0;
	data = (size << 15) | (1 << 13) | (driverID << 8) | offset;
	MT9D111_register_write(0xC6, data);
	MT9D111_register_write(0xC8, val);
}


/*
	size 8bit - 1 / 16bit - 0, [15:0] s01IDIDIDIDIDOFOFOFOFOFOFOFOF
*/
uint16_t MT9D111_variable_read(uint8_t driverID, uint8_t offset, uint8_t size)
{
	uint16_t returnData = 0;
	uint16_t data = 0;
	data = (size << 15) | (1 << 13) | (driverID << 8) | offset;
	MT9D111_register_write(0xC6, data);
	returnData = MT9D111_register_read(0xC8);
	
	return returnData;
}


/*

*/
void MT9D111_init(void)
{
	PMC->PMC_PCER0 |= (1 << ID_PIOA); // enable clock to the peripheral
	// disable PIOC control on the pin (disable peripheral control) - VSYNC, HREF, PCLK, D0, D1, D2, D3, D4, D5, D6, D7
	PIOA->PIO_PDR |= PIO_PA15 | PIO_PA16 | PIO_PA23 | PIO_PA24 | PIO_PA25 | PIO_PA26 | PIO_PA27 | PIO_PA28 | PIO_PA29 | PIO_PA30 | PIO_PA31;
	// disable pull-up - VSYNC, HREF, PCLK, D0, D1, D2, D3, D4, D5, D6, D7
	PIOA->PIO_PUDR |= PIO_PA15 | PIO_PA16 | PIO_PA23 | PIO_PA24 | PIO_PA25 | PIO_PA26 | PIO_PA27 | PIO_PA28 | PIO_PA29 | PIO_PA30 | PIO_PA31;
	// select Peripheral D function - VSYNC, HREF, PCLK, D0, D1, D2, D3, D4, D5, D6, D7
	PIOA->PIO_ABCDSR[0] |= PIO_PA15 | PIO_PA16 | PIO_PA23 | PIO_PA24 | PIO_PA25 | PIO_PA26 | PIO_PA27 | PIO_PA28 | PIO_PA29 | PIO_PA30 | PIO_PA31;
	PIOA->PIO_ABCDSR[1] |= PIO_PA15 | PIO_PA16 | PIO_PA23 | PIO_PA24 | PIO_PA25 | PIO_PA26 | PIO_PA27 | PIO_PA28 | PIO_PA29 | PIO_PA30 | PIO_PA31;
}


/*
	Not necessary to use for power saving. The camera takes care of the pins when entering STANDBY.
	Just in case I needed to de-init the pins.
*/
void MT9D111_deinit(void)
{
	// enable pull-up - VSYNC, HREF, PCLK, D0, D1, D2, D3, D4, D5, D6, D7
	PIOA->PIO_PUER |= PIO_PA15 | PIO_PA16 | PIO_PA23 | PIO_PA24 | PIO_PA25 | PIO_PA26 | PIO_PA27 | PIO_PA28 | PIO_PA29 | PIO_PA30 | PIO_PA31;
}


/*

*/
uint32_t MT9D111_wait_for_state(uint8_t state)
{
	uint32_t stateTimeout = STATE_TIMEOUT;
	MT9D111_register_write(WRITE_PAGE, 1);
	while(MT9D111_variable_read(1, 4, 1) != state && stateTimeout) {SysTick_delay_ms(25); stateTimeout--;}
	if(!stateTimeout) return 0;
	else return stateTimeout;
}


/*

*/
uint32_t MT9D111_get_state(void)
{
	MT9D111_register_write(WRITE_PAGE, 1);
	return MT9D111_variable_read(1, 4, 1);
}


/*

*/
void MT9D111_reset(void)
{
	MT9D111_register_write(WRITE_PAGE, 1);
	MT9D111_register_write(0xC3, 0x0501); // soft reset
	MT9D111_register_write(WRITE_PAGE, 0);
	MT9D111_register_write(0x0D, 0x0021);
	MT9D111_register_write(0x0D, 0x0000);
	SysTick_delay_ms(1); // wait 24 clock cycles before using I2C (at 8MHz 3us)
	MT9D111_wait_for_state(3); // wait for the camera's PREVIEW state
	MT9D111_register_write(WRITE_PAGE, 1);
	MT9D111_variable_write(1, 3, 1, 5); // command REFRESH
}


/*

*/
void MT9D111_standby(void)
{
	MT9D111_register_write(WRITE_PAGE, 1);
	MT9D111_variable_write(1, 3, 1, 3); // command DO STANDBY
	MT9D111_wait_for_state(9); // wait for the camera's STANBY state
	MT9D111_register_write(WRITE_PAGE, 0);
	MT9D111_register_write(0x65, 0xE000); // bypass PLL
	MT9D111_register_write(WRITE_PAGE, 1);
	MT9D111_register_write(0x0A, 0x0488); // to prevent elevated standby current
	MT9D111_register_write(WRITE_PAGE, 0);
	MT9D111_register_write(0x0D, 0x0040); // makes outputs high impedance
	MT9D111_register_write(WRITE_PAGE, 1);
	MT9D111_variable_write(10, 120, 0, 0x00); // internal reserved I/O as outputs and driven LOW
	MT9D111_variable_write(10, 121, 0, 0x00);
	MT9D111_variable_write(10, 112, 0, 0x00);
	MT9D111_variable_write(10, 113, 0, 0x00);
	MT9D111_register_write(WRITE_PAGE, 0);
	MT9D111_register_write(0x0D, 0x0044); // enter standby state
	// for soft STANDBY don't turn off CLK
}


/*

*/
void MT9D111_exit_standby(void)
{
	// for soft STANDBY CLK should be already on
	MT9D111_register_write(0x0D, 0x0000); // de-assert standby
	MT9D111_register_write(WRITE_PAGE, 1);
	MT9D111_variable_write(1, 3, 1, 1); // command DO PREVIEW
	MT9D111_wait_for_state(3); // wait for the camera's PREVIEW state
}


/*
	CONTEXT A - PREVIEW mode, CONTEXT B - CAPTURE mode
*/
uint32_t MT9D111_get_mode(void)
{
	MT9D111_register_write(WRITE_PAGE, 1);
	return MT9D111_variable_read(7, 2, 1); // 0 - context A, 1 - context B
}


/*

*/
void MT9D111_preview_mode(void)
{
	MT9D111_register_write(WRITE_PAGE, 1);
	MT9D111_variable_write(1, 32, 1, 0b00000000); // all off
	MT9D111_variable_write(1, 3, 1, 1); // command DO PREVIEW
	MT9D111_wait_for_state(3); // PREVIEW state
}


/*

*/
void MT9D111_capture_mode(void)
{
	MT9D111_register_write(WRITE_PAGE, 1);
	MT9D111_variable_write(1, 32, 1, 0b00000010); // capture video
	MT9D111_variable_write(1, 3, 1, 2); // command DO CAPTURE
	MT9D111_wait_for_state(7); // CAPTURE state
}


/*

*/
void MT9D111_refresh(void)
{
	MT9D111_register_write(WRITE_PAGE, 1);
	MT9D111_variable_write(1, 3, 1, 5); // command REFRESH
}


/*

*/
void MT9D111_refresh_mode(void)
{
	MT9D111_register_write(WRITE_PAGE, 1);
	MT9D111_variable_write(1, 3, 1, 6); // command REFRESH MODE
}


/*

*/
uint32_t MT9D111_get_version(void)
{
	uint32_t data = 0;
	MT9D111_register_write(WRITE_PAGE, 0);
	data = MT9D111_register_read(0x00); // sensor chip version
	data <<= 16;
	MT9D111_register_write(WRITE_PAGE, 1);
	data |= MT9D111_variable_read(0, 12, 1); // firmware version
	return data;
}


/*
	CONTEXT B - JPEG
*/
void MT9D111_mode_1(void)
{
	MT9D111_register_write(WRITE_PAGE, 0);
	MT9D111_register_write(0x20, 0b0000000000000000); // Context B - binning, mirroring, column & row skipping (0b1000010010010000) - bits 4 and 7 ?
	//MT9D111_register_write(0x05, 0x015C); // Horizontal Blanking in Context B - 0x015C default
	//MT9D111_register_write(0x06, 0x20); // Vertical Blanking in Context B - 0x20 default
	MT9D111_register_write(WRITE_PAGE, 1);
	MT9D111_register_write(0x0B, 0b11011111); // enable JPEG clock
	MT9D111_variable_write(1, 2, 1, JPEG_DRIVERS); // enabling various drivers - Auto Focus
	MT9D111_variable_write(7, 114, 0, 0b0000000000000000); // 0x0D(2) FIFO Buffer configuration 0 Context B (DS p.54)
	MT9D111_variable_write(7, 116, 0, 0b0000001000000011); // 0x0E(2) FIFO Buffer configuration 1 Context B (DS p.55)
	MT9D111_variable_write(7, 118, 1, 0b00000001); // 0x0F(2) FIFO Buffer configuration 2 Context B (DS p.55)
	MT9D111_variable_write(7, 37, 0, 0b0000000000110001); // 0x0A(0) Row Speed Context B (delay Pixel Clock, Pixel Clock speed)
	MT9D111_variable_write(7, 7, 0, RES_X); // set X for Context B
	MT9D111_variable_write(7, 9, 0, RES_Y); // set Y for Context B
	MT9D111_variable_write(7, 53, 0, 0); // Lower-x decimator zoom window (context B shadow register) CROP
	MT9D111_variable_write(7, 55, 0, 1600); // Upper-x decimator zoom window (context B shadow register) CROP
	MT9D111_variable_write(7, 57, 0, 0); // Lower-y decimator zoom window (context B shadow register) CROP
	MT9D111_variable_write(7, 59, 0, 1200); // Upper-y decimator zoom window (context B shadow register) CROP
	MT9D111_variable_write(7, 61, 0, 0b0000000000000000); // decimator control register (context B shadow register)
	MT9D111_variable_write(7, 27, 0, 28); // First sensor-readout row (context B shadow register) PAN
	MT9D111_variable_write(7, 29, 0, 60); // First sensor-readout column (context B shadow register) PAN
	MT9D111_variable_write(7, 31, 0, 1200); // No. of sensor-readout rows (context B shadow register) PAN
	MT9D111_variable_write(7, 33, 0, 1600); // No. of sensor-readout columns (context B shadow register) PAN
	MT9D111_variable_write(7, 11, 0, 0); // mode config - enable JPEG
	MT9D111_variable_write(7, 68, 1, (JPEG_CONTRAST << 4) | JPEG_GAMMA); // Gamma and contrast settings (context B shadow register) 0x42 - default
	MT9D111_variable_write(1, 33, 1, 1); // Number of frames captured in still capture mode
	MT9D111_variable_write(1, 32, 1, 0b00000000); // still images
	MT9D111_variable_write(9, 6, 1, JPEG_COLOR_FORMAT); // JPEG image format : 0 - YCbCr 4:2:2, 1 - YCbCr 4:2:0, 2 - Monochrome
	MT9D111_variable_write(9, 7, 1, 0b00111010); // JPEG configuration and handshaking
	MT9D111_variable_write(9, 8, 0, JPEG_RESTART_INTERVAL); // Restart marker interval
	MT9D111_variable_write(9, 10, 1, (0b10000000 | QSCALE_1)); // QSCALE1
	MT9D111_variable_write(9, 11, 1, (0b10000000 | QSCALE_2)); // QSCALE2
	MT9D111_variable_write(9, 12, 1, (0b10000000 | QSCALE_3)); // QSCALE3
	MT9D111_variable_write(1, 3, 1, 2); // command DO CAPTURE
	MT9D111_wait_for_state(7); // CAPTURE state
}


/*
	CONTEXT A
*/
void MT9D111_mode_2(void)
{
  /*
  RGB565 400kHz
  */
  //MT9D111_register_write(WRITE_PAGE, 0);
  //MT9D111_register_write(0x21, 0b1000010010010000); // Context A - binning, mirroring, column & row skipping (2x)
  //MT9D111_register_write(0x07, 0xAE); // Horizontal Blanking in Context A - 0xAE default
  //MT9D111_register_write(0x08, 0x10); // Vertical Blanking in Context A - 0x10 default
  MT9D111_register_write(WRITE_PAGE, 1);
  MT9D111_register_write(0x0B, 0b11001111); // disable JPEG clock
  MT9D111_variable_write(1, 44, 1, 1); // Auto focus configuration in Preview state
  MT9D111_variable_write(7, 107, 0, 0b0000000000000000); // 0x0D(2) FIFO Buffer configuration 0 Context A (DS p.54)
  MT9D111_variable_write(7, 109, 0, 0b0000010100001111); // 0x0E(2) FIFO Buffer configuration 1 Context A (DS p.55)
  MT9D111_variable_write(7, 111, 1, 0b00000010); // 0x0F(2) FIFO Buffer configuration 2 Context A (DS p.55)
  MT9D111_variable_write(7, 25, 0, 0b0000000000110111); // 0x0A(0) Row Speed Context A (PCLK speed as low as +-400kHz)
  MT9D111_variable_write(7, 3, 0, 144); // set X for Context A
  MT9D111_variable_write(7, 5, 0, 112); // set Y for Context A
  //MT9D111_variable_write(7, 39, 0, 0); // Lower-x decimator zoom window (context A shadow register) CROP
  //MT9D111_variable_write(7, 41, 0, RES_X_A); // Upper-x decimator zoom window (context A shadow register) CROP
  //MT9D111_variable_write(7, 43, 0, 0); // Lower-y decimator zoom window (context A shadow register) CROP
  //MT9D111_variable_write(7, 45, 0, RES_Y_A); // Upper-y decimator zoom window (context A shadow register) CROP
  MT9D111_variable_write(7, 15, 0, 50); // First sensor-readout row (context A shadow register) PAN
  MT9D111_variable_write(7, 17, 0, 50); // First sensor-readout column (context A shadow register) PAN
  MT9D111_variable_write(7, 19, 0, 112); // No. of sensor-readout rows (context A shadow register) PAN
  MT9D111_variable_write(7, 21, 0, 144); // No. of sensor-readout columns (context A shadow register) PAN
  MT9D111_variable_write(7, 11, 0, 0b0000000000110000); // mode config - bypass JPEG
  MT9D111_variable_write(7, 125, 1, 0b00100000); // Output Format Configuration for Context A (RGB565)
  MT9D111_variable_write(7, 67, 1, 0b00010010); // Gamma and contrast settings (context A shadow register) 0x42 - default
}


/*

*/
void MT9D111_TX_SSDV_image(void)
{
	
#ifdef GO_TO_STANDBY
	
	PWM_init();
	SysTick_delay_ms(1);
	MT9D111_exit_standby();
	MT9D111_reset();
	
#endif // GO_TO_STANDBY	
	
	uint32_t len = CreateJpegHeader(JPEGbuffer, RES_X, RES_Y, JPEG_COLOR_FORMAT, JPEG_RESTART_INTERVAL, QSCALE_1);
	
	MT9D111_mode_1();
	
	while(PIOA->PIO_PDSR & (1 << 15)); // wait for the end of the current frame (VSYNC HIGH->LOW)
	while(!(PIOA->PIO_PDSR & (1 << 15))); // wait for the start of a new frame (VSYNC LOW->HIGH)
	PDC_transfer(JPEGbuffer + len, MT9D111_BUFFER_SIZE - len);
	while(PIOA->PIO_PDSR & (1 << 15)); // wait for the end of the sampled frame (VSYNC HIGH->LOW)
	
	MT9D111_register_write(WRITE_PAGE, 1);
	uint16_t da5 = MT9D111_variable_read(9, 15, 1); // last JPEG length [23:16]
	uint16_t da6 = MT9D111_variable_read(9, 16, 0); // last JPEG length [15:0]
	
	JPEGlength = ((uint32_t)da5 << 16) | da6; // size of the current JPG image
	JPEGlength += len;
	
#ifdef GO_TO_STANDBY
	
	MT9D111_wait_for_state(3); // wait for the camera's PREVIEW state
	MT9D111_standby();
	SysTick_delay_ms(1);
	PWM_stop();
	
#endif // GO_TO_STANDBY	
	
	if(JPEGlength <= MT9D111_BUFFER_SIZE - 2)
	{
		JPEGbuffer[JPEGlength++] = 0xFF;
		JPEGbuffer[JPEGlength++] = 0xD9;
		
		uint8_t *_JPEGbufferP = JPEGbuffer;
		ssdv_t ssdv;
		
		ssdv_enc_init(&ssdv, SSDV_TYPE_NORMAL, SSDV_CALLSIGN, img_id++);
		ssdv_enc_set_buffer(&ssdv, pkt);
		
		uint8_t SSDV_done = 0; // flag to end the loop after last TX is finished
		
		while(!SSDV_done)
		{
			
		#ifdef TELEMETRY_IN_BETWEEN_PACKETS
		
			// UBLOX telemetry in between SSDV packets
			SysTick_delay_ms(21); // delay for even the 50 baud ISR fire again
			while(!TXdone_get_data); // wait for flag that TX has finished
			
			uint32_t seq = 0;
			
			ADC_start();
			AD3data = ADC_sample(3, 100);
			AD9data = ADC_sample(9, 100);
			AD15data = ADC_sample_temperature(100);
			ADC_stop();
			
			UBLOX_send_message(request0107, 8);
			UBLOX_fill_buffer_UBX(GPSbuffer, 100); // length MUST be changed for UBLOX 7 (92), UBLOX 8 (100)
			UBLOX_parse_0107(GPSbuffer);
			
			TXmessageLEN = TX_BUFFER_fill_UBX(TXbuffer, seq) - 1;			
			
			TXdata_ready = 1; // flag the data is ready
			
		#endif // TELEMETRY_IN_BETWEEN_PACKETS
		
			// SSDV packet
			while((ssdv_enc_get_packet(&ssdv)) == SSDV_FEED_ME)
			{
				size_t r = 0;
				
				for(uint8_t i = 0; i < 64; i++)
				{
					if(_JPEGbufferP > JPEGbuffer + JPEGlength) continue;
					img[i] = *_JPEGbufferP++;
					r++;
				}
				
				if(r == 0) SSDV_done = 1; // experimental
				if(r == 0) break;
				ssdv_enc_feed(&ssdv, img, r);
			}
			
			SysTick_delay_ms(21); // delay for even the 50 baud ISR fire again
			for(uint16_t x = 0; x < 256; x++) TXbuffer[x] = pkt[x];
			while(!TXdone_get_data); // wait for flag that TX has finished
			
			TXmessageLEN = 256;
			TXdata_ready = 1; // flag the data is ready
			
			if(ssdv.state == S_EOI) SSDV_done = 1;
		}
		
		SysTick_delay_ms(21); // delay for even the 50 baud ISR fire again
		while(!TXdone_get_data); // wait for flag that the last TX has finished
	}
}


// JPEG HEADER Functions


/*

*/
uint32_t JfifApp0Marker(uint8_t *pbuf)
{
	*pbuf++ = 0xFF; // APP0 marker
	*pbuf++ = 0xE0;
	*pbuf++ = 0x00; // length
	*pbuf++ = 0x10;
	*pbuf++ = 0x4A; // JFIF identifier
	*pbuf++ = 0x46;
	*pbuf++ = 0x49;
	*pbuf++ = 0x46;
	*pbuf++ = 0x00;
	*pbuf++ = 0x01; // version
	*pbuf++ = 0x02;
	*pbuf++ = 0x00; // units
	*pbuf++ = 0x00; // X density
	*pbuf++ = 0x01;
	*pbuf++ = 0x00; // Y density
	*pbuf++ = 0x01;
	*pbuf++ = 0x00; // X thumbnail
	*pbuf++ = 0x00; // Y thumbnail
	
	return 18;
}


/*

*/
uint32_t FrameHeaderMarker(uint8_t *pbuf, uint32_t width, uint32_t height, uint8_t format)
{
	uint32_t length;
	
	if(format == FORMAT_MONOCHROME) length = 11;
	else length = 17;
	
	*pbuf++ = 0xFF;				// start of frame: baseline DCT
	*pbuf++ = 0xC0;
	*pbuf++ = length >> 8;		// length field
	*pbuf++ = length & 0xFF;
	*pbuf++ = 0x08;				// sample precision
	*pbuf++ = height >> 8;		// number of lines
	*pbuf++ = height & 0xFF;
	*pbuf++ = width >> 8;		// number of samples per line
	*pbuf++ = width & 0xFF;
	
	if(format == FORMAT_MONOCHROME) // monochrome
	{
		*pbuf++ = 0x01; // number of image components in frame
		*pbuf++ = 0x00; // component identifier: Y
		*pbuf++ = 0x11; // horizontal | vertical sampling factor: Y
		*pbuf++ = 0x00; // quantization table selector: Y
	}
	else if(format == FORMAT_YCBCR422) // YCbCr422
	{
		*pbuf++ = 0x03; // number of image components in frame
		*pbuf++ = 0x01; // component identifier: Y --------------------- ORIG 0x00
		*pbuf++ = 0x21; // horizontal | vertical sampling factor: Y
		*pbuf++ = 0x00; // quantization table selector: Y
		*pbuf++ = 0x02; // component identifier: Cb -------------------- ORIG 0x01
		*pbuf++ = 0x11; // horizontal | vertical sampling factor: Cb
		*pbuf++ = 0x01; // quantization table selector: Cb
		*pbuf++ = 0x03; // component identifier: Cr -------------------- ORIG 0x02
		*pbuf++ = 0x11; // horizontal | vertical sampling factor: Cr
		*pbuf++ = 0x01; // quantization table selector: Cr
	}
	else // YCbCr420
	{
		*pbuf++ = 0x03; // number of image components in frame
		*pbuf++ = 0x01; // component identifier: Y --------------------- ORIG 0x00
		*pbuf++ = 0x22; // horizontal | vertical sampling factor: Y
		*pbuf++ = 0x00; // quantization table selector: Y
		*pbuf++ = 0x02; // component identifier: Cb -------------------- ORIG 0x01
		*pbuf++ = 0x11; // horizontal | vertical sampling factor: Cb
		*pbuf++ = 0x01; // quantization table selector: Cb
		*pbuf++ = 0x03; // component identifier: Cr -------------------- ORIG 0x02
		*pbuf++ = 0x11; // horizontal | vertical sampling factor: Cr
		*pbuf++ = 0x01; // quantization table selector: Cr
	}
	
	return (length + 2);
}


/*

*/
uint32_t ScanHeaderMarker(uint8_t *pbuf, uint8_t format)
{
	uint32_t length;
	if(format == FORMAT_MONOCHROME) length = 8;
	else length = 12;
	
	*pbuf++ = 0xFF;				// start of scan
	*pbuf++ = 0xDA;
	*pbuf++ = length >> 8;		// length field
	*pbuf++ = length & 0xFF;
	
	if(format == FORMAT_MONOCHROME) // monochrome
	{
		*pbuf++ = 0x01; // number of image components in scan
		*pbuf++ = 0x00; // scan component selector: Y
		*pbuf++ = 0x00; // DC | AC huffman table selector: Y
	}
	else // YCbCr
	{
		*pbuf++ = 0x03; // number of image components in scan
		*pbuf++ = 0x01; // scan component selector: Y --------------------- ORIG 0x00
		*pbuf++ = 0x00; // DC | AC huffman table selector: Y
		*pbuf++ = 0x02; // scan component selector: Cb -------------------- ORIG 0x01
		*pbuf++ = 0x11; // DC | AC huffman table selector: Cb
		*pbuf++ = 0x03; // scan component selector: Cr -------------------- ORIG 0x02
		*pbuf++ = 0x11; // DC | AC huffman table selector: Cr
	}
	
	*pbuf++ = 0x00; // Ss: start of predictor selector
	*pbuf++ = 0x3F; // Se: end of spectral selector
	*pbuf++ = 0x00; // Ah | Al: successive approximation bit position
	
	return (length + 2);
}


/*

*/
uint32_t DefineQuantizationTableMarker(uint8_t *pbuf, uint32_t qscale, uint8_t format)
{
	uint32_t i, length, temp;
	uint8_t newtbl[64]; // temporary array to store scaled zigzagged quantization entries

	if(format == FORMAT_MONOCHROME) length = 67;
	else length = 132;

	*pbuf++ = 0xFF; // define quantization table marker
	*pbuf++ = 0xDB;
	*pbuf++ = length >> 8; // length field
	*pbuf++ = length & 0xFF;
	*pbuf++ = 0; // quantization table precision | identifier for luminance
	
	// calculate scaled zigzagged luminance quantization table entries
	for(i = 0; i < 64; i++)
	{
		temp = (JPEG_StdQuantTblY[i] * qscale + 16) / 32;
		// limit the values to the valid range
		if(temp <= 0) temp = 1;
		if(temp > 255) temp = 255;
		newtbl[zigzag[i]] = (uint8_t)temp;
	}
	
	// write the resulting luminance quantization table to the output buffer
	for(i = 0; i < 64; i++) *pbuf++ = newtbl[i];

	// if format is monochrome we're finished, otherwise continue on, to do chrominance quantization table
	if(format == FORMAT_MONOCHROME) return (length + 2);

	*pbuf++ = 1; // quantization table precision | identifier for chrominance

	// calculate scaled zigzagged chrominance quantization table entries
	for(i = 0; i < 64; i++)
	{
		temp = (JPEG_StdQuantTblC[i] * qscale + 16) / 32;
		// limit the values to the valid range
		if(temp <= 0) temp = 1;
		if(temp > 255) temp = 255;
		newtbl[zigzag[i]] = (uint8_t)temp;
	}
	
	// write the resulting chrominance quantization table to the output buffer
	for(i = 0; i < 64; i++)	*pbuf++ = newtbl[i];

	return (length + 2);
}


/*

*/
uint32_t DefineHuffmanTableMarkerDC(uint8_t *pbuf, uint32_t *htable, uint8_t class_id)
{
	uint32_t i, l, count;
	uint8_t *plength;
	uint32_t length;
	
	*pbuf++ = 0xFF; // define huffman table marker
	*pbuf++ = 0xC4;
	plength = pbuf; // place holder for length field
	*pbuf++;
	*pbuf++;
	*pbuf++ = class_id; // huffman table class | identifier
	
	for(l = 0; l < 16; l++)
	{
		count = 0;
		
		for(i = 0; i < 12; i++)
		{
			if((htable[i] >> 8) == l) count++;
		}
		*pbuf++ = count; // number of huffman codes of length l+1
	}
	
	length = 19;
	
	for(l = 0; l < 16; l++)
	{
		for(i = 0; i < 12; i++)
		{
			if((htable[i] >> 8) == l)
			{
				*pbuf++ = i; // HUFFVAL with huffman codes of length l+1
				length++;
			}
		}
	}
	
	*plength++ = length >> 8; // length field
	*plength = length & 0xFF;
	
	return (length + 2);
}


/*

*/
uint32_t DefineHuffmanTableMarkerAC(uint8_t *pbuf, uint32_t *htable, uint8_t class_id)
{
	uint32_t i, l, a, b, count;
	uint8_t *plength;
	uint32_t length;
	
	*pbuf++ = 0xFF;			// define huffman table marker
	*pbuf++ = 0xC4;
	plength = pbuf;			// place holder for length field
	*pbuf++;
	*pbuf++;
	*pbuf++ = class_id;		// huffman table class | identifier
	
	for(l = 0; l < 16; l++)
	{
		count = 0;
		
		for(i = 0; i < 162; i++)
		{
			if((htable[i] >> 8) == l) count++;
		}
		
		*pbuf++ = count; // number of huffman codes of length l+1
	}
	
	length = 19;
	
	for(l = 0; l < 16; l++)
	{
		// check EOB: 0|0
		if ((htable[160] >> 8) == l)
		{
			*pbuf++ = 0; // HUFFVAL with huffman codes of length l+1
			length++;
		}
		
		// check HUFFVAL: 0|1 to E|A
		for(i = 0; i < 150; i++)
		{
			if ((htable[i] >> 8) == l)
			{
				a = i / 10;
				b = i % 10;
				*pbuf++ = (a << 4) | (b + 1); // HUFFVAL with huffman codes of length l+1
				length++;
			}
		}

		// check ZRL: F|0
		if((htable[161] >> 8) == l)
		{
			*pbuf++ = 0xF0; // HUFFVAL with huffman codes of length l+1
			length++;
		}
		
		// check HUFFVAL: F|1 to F|A
		for(i = 150; i < 160; i++)
		{
			if((htable[i] >> 8) == l)
			{
				a = i / 10;
				b = i % 10;
				*pbuf++ = (a << 4) | (b + 1); // HUFFVAL with huffman codes of length l+1
				length++;
			}
		}
	}
	
	*plength++ = length >> 8; // length field
	*plength = length & 0xFF;
	
	return (length + 2);
}


/*

*/
uint32_t DefineRestartIntervalMarker(uint8_t *pbuf, uint8_t ri)
{
	*pbuf++ = 0xFF;			// define restart interval marker
	*pbuf++ = 0xDD;
	*pbuf++ = 0x00;			// length
	*pbuf++ = 0x04;
	*pbuf++ = ri >> 8;		// restart interval
	*pbuf++ = ri & 0xFF;
	
	return 6;
}


/*

*/
uint32_t CreateJpegHeader(uint8_t *header, uint32_t width, uint32_t height, uint8_t format, uint8_t restart_int, uint32_t qscale)
{
	uint8_t *pbuf = header;
	uint32_t length;
	
	// SOI
	*pbuf++ = 0xFF;
	*pbuf++ = 0xD8;
	length = 2;
	
	// JFIF APP0
	length += JfifApp0Marker(pbuf);
	
	// Quantization Tables
	pbuf = header + length;
	length += DefineQuantizationTableMarker(pbuf, qscale, format);
	
	// Frame Header
	pbuf = header + length;
	length += FrameHeaderMarker(pbuf, width, height, format);
	
	// Huffman Table DC 0 for Luma
	pbuf = header + length;
	length += DefineHuffmanTableMarkerDC(pbuf, &JPEG_StdHuffmanTbl[352], 0x00);
	
	// Huffman Table AC 0 for Luma
	pbuf = header + length;
	length += DefineHuffmanTableMarkerAC(pbuf, &JPEG_StdHuffmanTbl[0], 0x10);
	
	if(format != FORMAT_MONOCHROME) // YCbCr
	{
		// Huffman Table DC 1 for Chroma
		pbuf = header + length;
		length += DefineHuffmanTableMarkerDC(pbuf, &JPEG_StdHuffmanTbl[368], 0x01);
		// Huffman Table AC 1 for Chroma
		pbuf = header + length;
		length += DefineHuffmanTableMarkerAC(pbuf, &JPEG_StdHuffmanTbl[176], 0x11);
	}
	
	// Restart Interval
	if(restart_int > 0)
	{
		pbuf = header + length;
		length += DefineRestartIntervalMarker(pbuf, restart_int);
	}
	
	// Scan Header
	pbuf = header + length;
	length += ScanHeaderMarker(pbuf, format);
	
	return length;
}