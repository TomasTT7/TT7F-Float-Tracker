/*
 * ARM_MT9D111.c
 *
 * Created: 21.6.2016 11:02:42
 *  Author: Tomy2
 */ 

#include "sam3s8b.h"
#include "ARM_MT9D111.h"
#include "ARM_SSDV.h"
#include "ARM_TWI.h"
#include "ARM_DELAY.h"
#include "ARM_SI4060.h"
#include "ARM_PIODC.h"
#include "ARM_UBLOX.h"
#include "ARM_ADC.h"
#include "ARM_PWM.h"
#include "ARM_LED.h"

/*
	Writes 16 bits of data to an 8 bit address.
	Returns 1 if OK, 0 if NACK and 2 if TIMEOUT.
	
	120us		at 64MHz		MT9D111 disconnected
*/
uint8_t MT9D111_test_write(uint8_t address, uint16_t data)
{
	TWI0->TWI_CR = TWI_CR_MSEN | TWI_CR_SVDIS;									// set master enable bit and slave mode disable bit
	TWI0->TWI_MMR = (DEVICE_ADDRESS << 16) | (1 << 8);							// device address ADDR, internal device address length LEN 0/1/2/3
	TWI0->TWI_IADR = address;													// set internal address for device
	TWI0->TWI_CR = TWI_CR_START;
	
	uint32_t status = 0;
	
	uint32_t timeout = TWI_TIMEOUT;
	TWI0->TWI_THR = data >> 8;													// send the data
	while (!(status & TWI_SR_TXRDY) && timeout)
	{
		status = TWI0->TWI_SR;
		if(status & TWI_SR_NACK) return 0;										// return not acknowledged
		timeout--;
	}
	if(!timeout) return 2;														// return timeout
	
	timeout = TWI_TIMEOUT;
	TWI0->TWI_THR = data;														// send the data
	while (!(status & TWI_SR_TXRDY) && timeout)
	{
		status = TWI0->TWI_SR;
		if(status & TWI_SR_NACK) return 0;										// return not acknowledged
		timeout--;
	}
	if(!timeout) return 2;														// return timeout

	TWI0->TWI_CR = TWI_CR_STOP;													// send STOP bit
	timeout = TWI_TIMEOUT;
	while (!(status & TWI_SR_TXCOMP) && timeout)
	{
		status = TWI0->TWI_SR;
		if(status & TWI_SR_NACK) return 0;										// return not acknowledged
		timeout--;
	}
	if(!timeout) return 2;														// return timeout
	
	return 1;
}


/*
	Writes 16 bits of data to an 8 bit address.
	
	220us		at 64MHz		MT9D111 disconnected
*/
void MT9D111_register_write(uint8_t address, uint16_t data)
{
	TWI0->TWI_CR = TWI_CR_MSEN | TWI_CR_SVDIS;									// set master enable bit and slave mode disable bit
	TWI0->TWI_MMR = (DEVICE_ADDRESS << 16) | (1 << 8);							// device address ADDR, internal device address length LEN 0/1/2/3
	TWI0->TWI_IADR = address;													// set internal address for device
	TWI0->TWI_CR = TWI_CR_START;
	
	uint32_t timeout = TWI_TIMEOUT;
	TWI0->TWI_THR = data >> 8;													// send the data
	while (!(TWI0->TWI_SR & TWI_SR_TXRDY) && timeout) timeout--;

	timeout = TWI_TIMEOUT;
	TWI0->TWI_THR = data;														// send the data
	while (!(TWI0->TWI_SR & TWI_SR_TXRDY) && timeout) timeout--;

	TWI0->TWI_CR = TWI_CR_STOP;													// send STOP bit
	timeout = TWI_TIMEOUT;
	while (!(TWI0->TWI_SR & TWI_SR_TXCOMP) && timeout) timeout--;
}


/*
	Reads 16 bits of data from an 8 bit address.
	
	7ms			at 64MHz		MT9D111 disconnected
*/
uint16_t MT9D111_register_read(uint8_t address)
{
	uint16_t data;
	uint32_t timeout;
	
	TWI0->TWI_CR = TWI_CR_MSEN | TWI_CR_SVDIS;									// set master enable bit and slave mode disable bit
	TWI0->TWI_MMR = (DEVICE_ADDRESS << 16) | (0 << 8);							// device address ADDR, internal device address length LEN 0/1/2/3
	TWI0->TWI_CR = TWI_CR_START | TWI_CR_STOP;
	
	timeout = TWI_TIMEOUT;
	TWI0->TWI_THR = address;
	while (!(TWI0->TWI_SR & TWI_SR_TXRDY) && timeout) timeout--;
	timeout = TWI_TIMEOUT;
	while(!(TWI0->TWI_SR & TWI_SR_TXCOMP) && timeout) timeout--;
	
	TWI0->TWI_CR = TWI_CR_MSEN | TWI_CR_SVDIS;									// set master enable bit and slave mode disable bit
	TWI0->TWI_MMR = TWI_MMR_MREAD | (DEVICE_ADDRESS << 16) | (0 << 8);			// device address ADDR, internal device address length LEN 0/1/2/3
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
	Writes specified variable.
	
	size		8-bit variable - 1		16-bit variable - 0			[15]
	
	driverID	0	Monitor											[12:8]
				1	Sequencer
				2	Auto exposure
				3	Auto white balance
				4	Flicker detection
				5	Auto focus
				6	Auto focus mechanics
				7	Mode
				9	JPEG
				11	Histogram
	
	offset		Offset for individual variables of the driver.		[7:0]
	
	val			Value to write. Either 8-bits or 16-bits.
*/
void MT9D111_variable_write(uint8_t driverID, uint8_t offset, uint8_t size, uint16_t val)
{
	uint16_t data = 0;
	data = (size << 15) | (1 << 13) | (driverID << 8) | offset;
	MT9D111_register_write(0xC6, data);
	MT9D111_register_write(0xC8, val);
}


/*
	Reads specified variable.
	
	size		8-bit variable - 1		16-bit variable - 0			[15]
	
	driverID	0	Monitor											[12:8]
				1	Sequencer
				2	Auto exposure
				3	Auto white balance
				4	Flicker detection
				5	Auto focus
				6	Auto focus mechanics
				7	Mode
				9	JPEG
				11	Histogram
	
	offset		Offset for individual variables of the driver.		[7:0]
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
	Pin initialization on SAM3S8. Default voltage on MCU pins due to pull ups is 3.05V.
	MT9D111 supply voltage (Analog, I/O, PLL) 2.83V and (digital) 1.82V. Max voltage on I/O pins 3.10V.
*/
void MT9D111_init(void)
{
	PMC->PMC_PCER0 |= (1 << ID_PIOA);											// enable clock to the peripheral
	
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
	Just in case I needed to de-init the pins. To decrease the consumption if the camera gets disconnected. 
*/
void MT9D111_deinit(void)
{
	// enable pull-up - VSYNC, HREF, PCLK, D0, D1, D2, D3, D4, D5, D6, D7
	PIOA->PIO_PUER |= PIO_PA15 | PIO_PA16 | PIO_PA23 | PIO_PA24 | PIO_PA25 | PIO_PA26 | PIO_PA27 | PIO_PA28 | PIO_PA29 | PIO_PA30 | PIO_PA31;
}


/*
	Repeatedly checks the state of the sequencer until it cycles to the desired state or it times out.
	
	WAIT_FOR_STATE_TIMEOUT		400		~13s
*/
uint32_t MT9D111_wait_for_state(uint8_t state)
{
	uint32_t stateTimeout = WAIT_FOR_STATE_TIMEOUT;
	MT9D111_register_write(WRITE_PAGE, 1);
	while(MT9D111_variable_read(1, 4, 1) != state && stateTimeout) {SysTick_delay_ms(25); stateTimeout--;}
	if(!stateTimeout) return 0;
	else return stateTimeout;
}


/*
	Returns the current state of the sequencer.
		0	Initialize
		1	Mode Change to Preview
		2	Enter Preview
		3	Preview
		4	Leave Preview
		5	Mode Change to Capture
		6	Enter Capture
		7	Capture
		8	Leave Capture
		9	Standby
*/
uint32_t MT9D111_get_state(void)
{
	MT9D111_register_write(WRITE_PAGE, 1);
	return MT9D111_variable_read(1, 4, 1);
}


/*
	Soft resets the camera, waits for it to cycle back to PREVIEW state and executes the REFRESH command.
	Necessary after POWERUP.
	
	duration	~3s
*/
void MT9D111_reset(void)
{
	MT9D111_register_write(WRITE_PAGE, 1);
	MT9D111_register_write(0xC3, 0x0501);										// Soft reset
	MT9D111_register_write(WRITE_PAGE, 0);
	MT9D111_register_write(0x0D, 0x0021);
	MT9D111_register_write(0x0D, 0x0000);
	SysTick_delay_ms(1);														// wait 24 clock cycles before using I2C (at 8MHz 3us)
	MT9D111_wait_for_state(3);													// wait for the camera's PREVIEW state
	MT9D111_register_write(WRITE_PAGE, 1);
	MT9D111_variable_write(1, 3, 1, 5);											// REFRESH command
}


/*
	Command or program to execute
		0	Run
		1	Do Preview
		2	Do Capture
		3	Do Standby
		4	Do lock
		5	Refresh
		6	Refresh mode
*/
void MT9D111_execute_command(uint8_t cmd)
{
	MT9D111_register_write(WRITE_PAGE, 1);
	MT9D111_variable_write(1, 3, 1, cmd);
}


/*
	Prepare the camera for STANDBY and enter the STANDBY mode.
	In this mode with this setup the module's consumption is close to 0mA.
	
	According to datasheet, for soft STANDBY don't turn CLK off. (I turn the PWM signal off anyway because of consumption.)
	
	duration	~1s
*/
void MT9D111_standby(void)
{
	MT9D111_register_write(WRITE_PAGE, 1);
	MT9D111_variable_write(1, 3, 1, 3);											// DO STANDBY command
	MT9D111_wait_for_state(9);													// wait for the camera's STANDBY state
	MT9D111_register_write(WRITE_PAGE, 0);
	MT9D111_register_write(0x65, 0xE000);										// bypass PLL
	MT9D111_register_write(WRITE_PAGE, 1);
	MT9D111_register_write(0x0A, 0x0488);										// to prevent elevated standby current
	MT9D111_register_write(WRITE_PAGE, 0);
	MT9D111_register_write(0x0D, 0x0040);										// makes outputs high impedance
	MT9D111_register_write(WRITE_PAGE, 1);
	MT9D111_variable_write(10, 120, 0, 0x00);									// internal reserved I/O as outputs and driven LOW
	MT9D111_variable_write(10, 121, 0, 0x00);
	MT9D111_variable_write(10, 112, 0, 0x00);
	MT9D111_variable_write(10, 113, 0, 0x00);
	MT9D111_register_write(WRITE_PAGE, 0);
	MT9D111_register_write(0x0D, 0x0044);										// enter standby state
}


/*
	Exits STANDBY state.
	CLK should be already running when calling this routine.
	
	duration	~1.25s
*/
void MT9D111_exit_standby(void)
{
	MT9D111_register_write(0x0D, 0x0000);										// de-assert standby
	MT9D111_register_write(WRITE_PAGE, 1);
	MT9D111_variable_write(1, 3, 1, 1);											// command DO PREVIEW
	MT9D111_wait_for_state(3);													// wait for the camera's PREVIEW state
}


/*
	Returns the current camera mode.
		CONTEXT A	PREVIEW mode	0
		CONTEXT B	CAPTURE mode	1
*/
uint32_t MT9D111_get_mode(void)
{
	MT9D111_register_write(WRITE_PAGE, 1);
	return MT9D111_variable_read(7, 2, 1);
}


/*
	Commands the camera to transition to PREVIEW mode.
	
	duration	~3.9s
*/
void MT9D111_preview_mode(void)
{
	MT9D111_register_write(WRITE_PAGE, 1);
	MT9D111_variable_write(1, 3, 1, 1);											// DO PREVIEW command
	MT9D111_wait_for_state(3);													// wait for PREVIEW state
}


/*
	Commands the camera to transition to CAPTURE mode (still image).
	
	duration	~2.2s
*/
void MT9D111_capture_mode(void)
{
	MT9D111_register_write(WRITE_PAGE, 1);
	MT9D111_variable_write(1, 32, 1, 0b00000000);								// still image, all video options off
	MT9D111_variable_write(1, 3, 1, 2);											// DO CAPTURE command
	MT9D111_wait_for_state(7);													// wait for CAPTURE state
}


/*
	Commands the camera to put new values into effect (variables).
	Some require REFRESH, other REFRESH_MODE.
*/
void MT9D111_refresh(void)
{
	MT9D111_register_write(WRITE_PAGE, 1);
	MT9D111_variable_write(1, 3, 1, 5);											// REFRESH command
}


/*
	Commands the camera to put new values into effect (variables).
	Some require REFRESH, other REFRESH_MODE.
*/
void MT9D111_refresh_mode(void)
{
	MT9D111_register_write(WRITE_PAGE, 1);
	MT9D111_variable_write(1, 3, 1, 6);											// REFRESH MODE command
}


/*
	Sensor chip version		0x1519
	Firmware version		0x20
*/
uint32_t MT9D111_get_version(void)
{
	uint32_t data = 0;
	MT9D111_register_write(WRITE_PAGE, 0);
	data = MT9D111_register_read(0x00);											// sensor chip version
	data <<= 16;
	MT9D111_register_write(WRITE_PAGE, 1);
	data |= MT9D111_variable_read(0, 12, 1);									// firmware version
	return data;
}


/*
	Mode 1 JPEG (Context B)
	Function that sets the settings of a desirable JPEG image and transitions to CAPTURE mode.
*/
void MT9D111_mode_1(void)
{
	MT9D111_register_write(WRITE_PAGE, 0);
	MT9D111_register_write(0x20, READ_MODE_B);									// Binning, mirroring, column & row skipping, etc. (0x0000 - default)
	MT9D111_register_write(0x05, 0x015C);										// Horizontal Blanking in Context B (0x015C - default)
	MT9D111_register_write(0x06, 0x0020);										// Vertical Blanking in Context B (0x0020 - default)
	
	MT9D111_register_write(WRITE_PAGE, 1);
	MT9D111_register_write(0x0B, 0b11011111);									// Enable JPEG clock
	
	MT9D111_variable_write(1, 2, 1, jpeg_drivers);								// Enable drivers
		
	MT9D111_variable_write(7, 7, 0, res_x);										// Output width for Context B
	MT9D111_variable_write(7, 9, 0, res_y);										// Output height for Context B
	MT9D111_variable_write(7, 11, 0, 0);										// Mode config - enable JPEG
	
	MT9D111_variable_write(7, 27, 0, 28);										// First sensor-readout row (context B) PAN
	MT9D111_variable_write(7, 29, 0, 60);										// First sensor-readout column (context B) PAN
	MT9D111_variable_write(7, 31, 0, 1200);										// No. of sensor-readout rows (context B) PAN
	MT9D111_variable_write(7, 33, 0, 1600);										// No. of sensor-readout columns (context B) PAN
	
	MT9D111_variable_write(7, 37, 0, 0b0000000000010001);						// 0x0A(0) Row Speed Context B (delay Pixel Clock, Pixel Clock speed)
	
	MT9D111_variable_write(7, 53, 0, 0);										// Lower-x decimator zoom window (context B) CROP
	MT9D111_variable_write(7, 55, 0, 1600);										// Upper-x decimator zoom window (context B) CROP
	MT9D111_variable_write(7, 57, 0, 0);										// Lower-y decimator zoom window (context B) CROP
	MT9D111_variable_write(7, 59, 0, 1200);										// Upper-y decimator zoom window (context B) CROP
	
	MT9D111_variable_write(7, 61, 0, 0b0000000000000000);						// Decimator control register (context B): Bit 4 - enable 4:2:0 mode 
	MT9D111_variable_write(7, 68, 1, (jpeg_contrast << 4) | jpeg_gamma);		// Gamma and contrast settings (0x42 - default)
	
	MT9D111_variable_write(7, 114, 0, OUTPUT_CONFIGURATION);					// 0x0D(2) FIFO Buffer configuration 0 Context B (DS p.54)
	MT9D111_variable_write(7, 116, 0, 0b0000001000000011);						// 0x0E(2) FIFO Buffer configuration 1 Context B (DS p.55)
	MT9D111_variable_write(7, 118, 1, 0b00000001);								// 0x0F(2) FIFO Buffer configuration 2 Context B (DS p.55)
	
	MT9D111_variable_write(1, 33, 1, NUM_IMAGES);								// Number of frames in still capture mode
	MT9D111_variable_write(1, 32, 1, 0b00000000);								// Still image, all video options off
	
	MT9D111_variable_write(9, 6, 1, JPEG_COLOR_FORMAT);							// JPEG image format
	MT9D111_variable_write(9, 7, 1, JPEG_CONFIGURATION);						// JPEG configuration and handshaking
	MT9D111_variable_write(9, 8, 0, JPEG_RESTART_INTERVAL);						// Restart marker interval
	MT9D111_variable_write(9, 10, 1, (0b10000000 | qscale_1));					// QSCALE1
	MT9D111_variable_write(9, 11, 1, (0b10000000 | qscale_2));					// QSCALE2
	MT9D111_variable_write(9, 12, 1, (0b10000000 | qscale_3));					// QSCALE3
	
	MT9D111_variable_write(1, 3, 1, 2);											// DO CAPTURE command
	MT9D111_wait_for_state(7);													// CAPTURE state
}


/*
	Mode 2 RGB565 (Context A)
	Function that changes the output in PREVIEW mode to a defined RGB565 image.
*/
void MT9D111_mode_2(void)
{
	MT9D111_register_write(WRITE_PAGE, 0);
	MT9D111_register_write(0x07, 0x00AE);										// Horizontal Blanking in Context A (0xAE - default)
	MT9D111_register_write(0x08, 0x0010);										// Vertical Blanking in Context A (0x10 - default)
	MT9D111_register_write(0x21, 0b1000000000000000);							// Binning, mirroring, column & row skipping (2x) (default)
	
	MT9D111_register_write(WRITE_PAGE, 1);
	MT9D111_register_write(0x0B, 0b11001111);									// Disable JPEG clock
	MT9D111_variable_write(1, 44, 1, 1);										// Auto focus configuration in Preview state
	
	MT9D111_variable_write(7, 3, 0, 144);										// Output width for Context A
	MT9D111_variable_write(7, 5, 0, 112);										// Output height for Context A
	MT9D111_variable_write(7, 11, 0, 0b0000000000110000);						// Mode config - bypass JPEG
	
	MT9D111_variable_write(7, 15, 0, 50);										// First sensor-readout row (context A) PAN
	MT9D111_variable_write(7, 17, 0, 50);										// First sensor-readout column (context A) PAN
	MT9D111_variable_write(7, 19, 0, 112);										// No. of sensor-readout rows (context A) PAN
	MT9D111_variable_write(7, 21, 0, 144);										// No. of sensor-readout columns (context A) PAN
	
	MT9D111_variable_write(7, 25, 0, 0b0000000000110111);						// Row Speed for Context A (PCLK as low as 400kHz)
	
	MT9D111_variable_write(7, 39, 0, 0);										// Lower-x decimator zoom window (context A) CROP
	MT9D111_variable_write(7, 41, 0, 800);										// Upper-x decimator zoom window (context A) CROP
	MT9D111_variable_write(7, 43, 0, 0);										// Lower-y decimator zoom window (context A) CROP
	MT9D111_variable_write(7, 45, 0, 600);										// Upper-y decimator zoom window (context A) CROP
	
	MT9D111_variable_write(7, 67, 1, 0b01000010);								// Gamma and contrast settings (0x42 - default)
	
	MT9D111_variable_write(7, 107, 0, 0b0000000000000000);						// 0x0D(2) FIFO Buffer configuration 0 Context A (DS p.54)
	MT9D111_variable_write(7, 109, 0, 0b0000010100001111);						// 0x0E(2) FIFO Buffer configuration 1 Context A (DS p.55)
	MT9D111_variable_write(7, 111, 1, 0b00000010);								// 0x0F(2) FIFO Buffer configuration 2 Context A (DS p.55)
	MT9D111_variable_write(7, 125, 1, 0b00100000);								// Output Format Configuration for Context A (RGB565)
	
	MT9D111_variable_write(1, 3, 1, 5);											// REFRESH command
}


/*
	Brings MT9D111 from standby. Initializes communication to the camera. Sets it in Context B with JPEG output.
	Samples an image and puts it inside a buffer.
*/
uint32_t MT9D111_get_image(void)
{
	
#ifdef GO_TO_STANDBY

	TWI_init_master();
	PWM_init(6, 3);
	SysTick_delay_ms(1);
	MT9D111_exit_standby();
	MT9D111_reset();

#endif // GO_TO_STANDBY
	
	if(MT9D111_get_version() != 0x15190020)										// verify that the communication to the camera was established
	{
		PWM_deinit();
		TWI_deinit();
		LED_PB5_blink(1000);
		return 1;
	}
	
	LED_PA0_blink(5);
	SysTick_delay_ms(100);
	LED_PA0_blink(5);
	
	uint32_t len = CreateJpegHeader(JPEGbuffer, res_x, res_y, JPEG_COLOR_FORMAT, JPEG_RESTART_INTERVAL, qscale_1);
	
	MT9D111_mode_1();
	
	while(PIOA->PIO_PDSR & (1 << 15));											// wait for the end of the current frame (VSYNC HIGH->LOW)
	PDC_transfer(JPEGbuffer + len, MT9D111_BUFFER_SIZE - len);					// initialize the PDC (there is not enough time after VSYNC goes HIGH)
	while(!(PIOA->PIO_PDSR & (1 << 15)));										// wait for the start of a new frame (VSYNC LOW->HIGH)
	while(PIOA->PIO_PDSR & (1 << 15));											// wait for the end of the sampled frame (VSYNC HIGH->LOW)
	
	MT9D111_register_write(WRITE_PAGE, 1);
	uint16_t da5 = MT9D111_variable_read(9, 15, 1);								// last JPEG length [23:16]
	uint16_t da6 = MT9D111_variable_read(9, 16, 0);								// last JPEG length [15:0]
	
	MT9D111_register_write(WRITE_PAGE, 2);
	uint16_t JPEGstatus = MT9D111_register_read(0x02);							// JPEG status
	
	uint32_t JPEGlength = ((uint32_t)da5 << 16) | da6;							// size of the current JPG image
	JPEGlength += len;															// size including the header
	
	uint8_t doSSDV = 0;
	if(JPEGstatus & 0x01) doSSDV = 1;											// check for the Transfer done status flag
	
#ifdef GO_TO_STANDBY
	
	MT9D111_wait_for_state(3);													// wait for the camera's PREVIEW state
	MT9D111_standby();
	SysTick_delay_ms(1);
	PWM_deinit();
	TWI_deinit();
	
#endif // GO_TO_STANDBY
	
	if(JPEGlength <= (MT9D111_BUFFER_SIZE - 2) && doSSDV)
	{
		JPEGbuffer[JPEGlength++] = 0xFF;										// finish the image with an EOI marker
		JPEGbuffer[JPEGlength++] = 0xD9;
		
		return JPEGlength;
	}
	else
	{
		for(uint32_t i = 0; i < MT9D111_BUFFER_SIZE; i++) JPEGbuffer[i] = 0;	// else clear the buffer
		return 0;
	}
}


// JPEG HEADER Functions -------------------------------------------------------------------------------------------------


/*
	APP0 marker. Start of the header.
*/
uint32_t JfifApp0Marker(uint8_t *pbuf)
{
	*pbuf++ = 0xFF;																// APP0 marker
	*pbuf++ = 0xE0;
	*pbuf++ = 0x00;																// length
	*pbuf++ = 0x10;
	*pbuf++ = 0x4A;																// JFIF identifier
	*pbuf++ = 0x46;
	*pbuf++ = 0x49;
	*pbuf++ = 0x46;
	*pbuf++ = 0x00;
	*pbuf++ = 0x01;																// version
	*pbuf++ = 0x02;
	*pbuf++ = 0x00;																// units
	*pbuf++ = 0x00;																// X density
	*pbuf++ = 0x01;
	*pbuf++ = 0x00;																// Y density
	*pbuf++ = 0x01;
	*pbuf++ = 0x00;																// X thumbnail
	*pbuf++ = 0x00;																// Y thumbnail
	
	return 18;
}


/*
	SOF0 marker.
*/
uint32_t FrameHeaderMarker(uint8_t *pbuf, uint32_t width, uint32_t height, uint8_t format)
{
	uint32_t length;
	
	if(format == FORMAT_MONOCHROME) length = 11;
	else length = 17;
	
	*pbuf++ = 0xFF;																// start of frame: baseline DCT
	*pbuf++ = 0xC0;
	*pbuf++ = length >> 8;														// length field
	*pbuf++ = length & 0xFF;
	*pbuf++ = 0x08;																// sample precision
	*pbuf++ = height >> 8;														// number of lines
	*pbuf++ = height & 0xFF;
	*pbuf++ = width >> 8;														// number of samples per line
	*pbuf++ = width & 0xFF;
	
	if(format == FORMAT_MONOCHROME)												// MONOCHROME
	{
		*pbuf++ = 0x01;															// number of image components in frame
		*pbuf++ = 0x00;															// component identifier: Y
		*pbuf++ = 0x11;															// horizontal | vertical sampling factor: Y
		*pbuf++ = 0x00;															// quantization table selector: Y
	}
	else if(format == FORMAT_YCBCR422)											// YCBCR422
	{
		*pbuf++ = 0x03;															// number of image components in frame
		*pbuf++ = 0x01;															// component identifier: Y --------------------- ORIG 0x00
		*pbuf++ = 0x21;															// horizontal | vertical sampling factor: Y
		*pbuf++ = 0x00;															// quantization table selector: Y
		*pbuf++ = 0x02;															// component identifier: Cb -------------------- ORIG 0x01
		*pbuf++ = 0x11;															// horizontal | vertical sampling factor: Cb
		*pbuf++ = 0x01;															// quantization table selector: Cb
		*pbuf++ = 0x03;															// component identifier: Cr -------------------- ORIG 0x02
		*pbuf++ = 0x11;															// horizontal | vertical sampling factor: Cr
		*pbuf++ = 0x01;															// quantization table selector: Cr
	}
	else																		// YCBCR420
	{
		*pbuf++ = 0x03;															// number of image components in frame
		*pbuf++ = 0x01;															// component identifier: Y --------------------- ORIG 0x00
		*pbuf++ = 0x22;															// horizontal | vertical sampling factor: Y
		*pbuf++ = 0x00;															// quantization table selector: Y
		*pbuf++ = 0x02;															// component identifier: Cb -------------------- ORIG 0x01
		*pbuf++ = 0x11;															// horizontal | vertical sampling factor: Cb
		*pbuf++ = 0x01;															// quantization table selector: Cb
		*pbuf++ = 0x03;															// component identifier: Cr -------------------- ORIG 0x02
		*pbuf++ = 0x11;															// horizontal | vertical sampling factor: Cr
		*pbuf++ = 0x01;															// quantization table selector: Cr
	}
	
	return (length + 2);
}


/*
	SOS marker. Start of Scan.
*/
uint32_t ScanHeaderMarker(uint8_t *pbuf, uint8_t format)
{
	uint32_t length;
	if(format == FORMAT_MONOCHROME) length = 8;
	else length = 12;
	
	*pbuf++ = 0xFF;																// start of scan
	*pbuf++ = 0xDA;
	*pbuf++ = length >> 8;														// length field
	*pbuf++ = length & 0xFF;
	
	if(format == FORMAT_MONOCHROME)												// MONOCHROME
	{
		*pbuf++ = 0x01;															// number of image components in scan
		*pbuf++ = 0x00;															// scan component selector: Y
		*pbuf++ = 0x00;															// DC | AC Huffman table selector: Y
	}
	else																		// YCBCR
	{
		*pbuf++ = 0x03;															// number of image components in scan
		*pbuf++ = 0x01;															// scan component selector: Y --------------------- ORIG 0x00
		*pbuf++ = 0x00;															// DC | AC Huffman table selector: Y
		*pbuf++ = 0x02;															// scan component selector: Cb -------------------- ORIG 0x01
		*pbuf++ = 0x11;															// DC | AC Huffman table selector: Cb
		*pbuf++ = 0x03;															// scan component selector: Cr -------------------- ORIG 0x02
		*pbuf++ = 0x11;															// DC | AC Huffman table selector: Cr
	}
	
	*pbuf++ = 0x00;																// Ss: start of predictor selector
	*pbuf++ = 0x3F;																// Se: end of spectral selector
	*pbuf++ = 0x00;																// Ah | Al: successive approximation bit position
	
	return (length + 2);
}


/*
	DQT marker.	Define a Quantization Table.
	Modified function sourced from https://blog.frankvh.com/2011/08/09/mt9d131-image-sensor-jpg-header/ blog post.
*/
uint32_t DefineQuantizationTableMarker(uint8_t *pbuf, uint32_t qscale, uint8_t format)
{
	uint32_t i, length, temp;
	uint8_t newtbl[64];															// temporary array to store scaled zigzagged quantization entries

	if(format == FORMAT_MONOCHROME) length = 67;
	else length = 132;

	*pbuf++ = 0xFF;																// define quantization table marker
	*pbuf++ = 0xDB;
	*pbuf++ = length >> 8;														// length field
	*pbuf++ = length & 0xFF;
	*pbuf++ = 0;																// quantization table precision | identifier for luminance
	
	for(i = 0; i < 64; i++)														// calculate scaled zigzagged luminance quantization table entries
	{
		temp = (JPEG_StdQuantTblY[i] * qscale + 16) / 32;
		if(temp <= 0) temp = 1;													// limit the values to the valid range
		if(temp > 255) temp = 255;
		newtbl[zigzag[i]] = (uint8_t)temp;
	}
	
	for(i = 0; i < 64; i++) *pbuf++ = newtbl[i];								// write the resulting luminance quantization table to the buffer

	if(format == FORMAT_MONOCHROME) return (length + 2);						// if monochrome we're finished, otherwise do chrominance table

	*pbuf++ = 1;																// quantization table precision | identifier for chrominance

	for(i = 0; i < 64; i++)														// calculate scaled zigzagged chrominance quantization table entries
	{
		temp = (JPEG_StdQuantTblC[i] * qscale + 16) / 32;
		if(temp <= 0) temp = 1;													// limit the values to the valid range
		if(temp > 255) temp = 255;
		newtbl[zigzag[i]] = (uint8_t)temp;
	}
	
	for(i = 0; i < 64; i++)	*pbuf++ = newtbl[i];								// write the resulting chrominance quantization table to the  buffer

	return (length + 2);
}


/*
	DHT marker. Define Huffman Table.
*/
uint32_t DefineHuffmanTableMarkerDC(uint8_t *pbuf, uint32_t *htable, uint8_t class_id)
{
	uint32_t i, l, count;
	uint8_t *plength;
	uint32_t length;
	
	*pbuf++ = 0xFF;																// define Huffman table marker
	*pbuf++ = 0xC4;
	plength = pbuf;																// place holder for length field
	*pbuf++;
	*pbuf++;
	*pbuf++ = class_id;															// Huffman table class | identifier
	
	for(l = 0; l < 16; l++)
	{
		count = 0;
		
		for(i = 0; i < 12; i++)
		{
			if((htable[i] >> 8) == l) count++;
		}
		*pbuf++ = count;														// number of Huffman codes of length l+1
	}
	
	length = 19;
	
	for(l = 0; l < 16; l++)
	{
		for(i = 0; i < 12; i++)
		{
			if((htable[i] >> 8) == l)
			{
				*pbuf++ = i;													// HUFFVAL with Huffman codes of length l+1
				length++;
			}
		}
	}
	
	*plength++ = length >> 8;													// length field
	*plength = length & 0xFF;
	
	return (length + 2);
}


/*
	DHT marker. Define Huffman Table.
*/
uint32_t DefineHuffmanTableMarkerAC(uint8_t *pbuf, uint32_t *htable, uint8_t class_id)
{
	uint32_t i, l, a, b, count;
	uint8_t *plength;
	uint32_t length;
	
	*pbuf++ = 0xFF;																// define Huffman table marker
	*pbuf++ = 0xC4;
	plength = pbuf;																// place holder for length field
	*pbuf++;
	*pbuf++;
	*pbuf++ = class_id;															// Huffman table class | identifier
	
	for(l = 0; l < 16; l++)
	{
		count = 0;
		
		for(i = 0; i < 162; i++)
		{
			if((htable[i] >> 8) == l) count++;
		}
		
		*pbuf++ = count;														// number of Huffman codes of length l+1
	}
	
	length = 19;
	
	for(l = 0; l < 16; l++)
	{
		if ((htable[160] >> 8) == l)											// check EOB: 0|0
		{
			*pbuf++ = 0;														// HUFFVAL with Huffman codes of length l+1
			length++;
		}
		
		for(i = 0; i < 150; i++)												// check HUFFVAL: 0|1 to E|A
		{
			if ((htable[i] >> 8) == l)
			{
				a = i / 10;
				b = i % 10;
				*pbuf++ = (a << 4) | (b + 1);									// HUFFVAL with Huffman codes of length l+1
				length++;
			}
		}

		if((htable[161] >> 8) == l)												// check ZRL: F|0
		{
			*pbuf++ = 0xF0;														// HUFFVAL with Huffman codes of length l+1
			length++;
		}
		
		for(i = 150; i < 160; i++)												// check HUFFVAL: F|1 to F|A
		{
			if((htable[i] >> 8) == l)
			{
				a = i / 10;
				b = i % 10;
				*pbuf++ = (a << 4) | (b + 1);									// HUFFVAL with Huffman codes of length l+1
				length++;
			}
		}
	}
	
	*plength++ = length >> 8;													// length field
	*plength = length & 0xFF;
	
	return (length + 2);
}


/*
	DD marker. Define Restart Interval.
*/
uint32_t DefineRestartIntervalMarker(uint8_t *pbuf, uint8_t ri)
{
	*pbuf++ = 0xFF;																// define restart interval marker
	*pbuf++ = 0xDD;
	*pbuf++ = 0x00;																// length
	*pbuf++ = 0x04;
	*pbuf++ = ri >> 8;															// restart interval
	*pbuf++ = ri & 0xFF;
	
	return 6;
}


/*
	Creates the JPEG header for MT9D111 images based on the input variables.
	The header is placed inside a buffer (*header). The size of the header moves about 700-800 bytes (~1000 byte buffer).
*/
uint32_t CreateJpegHeader(uint8_t *header, uint32_t width, uint32_t height, uint8_t format, uint8_t restart_int, uint32_t qscale)
{
	uint8_t *pbuf = header;
	uint32_t length;
	
	*pbuf++ = 0xFF;																		// SOI
	*pbuf++ = 0xD8;
	length = 2;
	
	length += JfifApp0Marker(pbuf);														// JFIF APP0
	
	pbuf = header + length;																// Quantization Tables
	length += DefineQuantizationTableMarker(pbuf, qscale, format);
	
	pbuf = header + length;																// Frame Header
	length += FrameHeaderMarker(pbuf, width, height, format);
	
	pbuf = header + length;																// Huffman Table DC 0 for Luma
	length += DefineHuffmanTableMarkerDC(pbuf, &JPEG_StdHuffmanTbl[352], 0x00);
	
	pbuf = header + length;																// Huffman Table AC 0 for Luma
	length += DefineHuffmanTableMarkerAC(pbuf, &JPEG_StdHuffmanTbl[0], 0x10);
	
	if(format != FORMAT_MONOCHROME)
	{
		pbuf = header + length;															// Huffman Table DC 1 for Chroma
		length += DefineHuffmanTableMarkerDC(pbuf, &JPEG_StdHuffmanTbl[368], 0x01);
		pbuf = header + length;															// Huffman Table AC 1 for Chroma
		length += DefineHuffmanTableMarkerAC(pbuf, &JPEG_StdHuffmanTbl[176], 0x11);
	}
	
	if(restart_int > 0)																	// Restart Interval
	{
		pbuf = header + length;
		length += DefineRestartIntervalMarker(pbuf, restart_int);
	}
	
	pbuf = header + length;																// Scan Header
	length += ScanHeaderMarker(pbuf, format);
	
	return length;
}