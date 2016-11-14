/*
 * ARM_POWER_SAVE.c
 *
 * Created: 8.9.2016 14:43:57
 *  Author: Tomy2
 */ 

#include "sam.h"
#include "ARM_POWER_SAVE.h"


/*
	Identical to SystemInit()
	
	Sets the access method and number of cycles for the Enhanced Embedded Flash Controller (EEFC).
	Step by step goes from Fast RC Oscillator to PLLA as the Main Clock.
	
	CLOCKS
		MCK		The Master Clock, programmable from a few hundred Hz to the maximum operating frequency. Slow or Main Clock.
		HCLK	Processor Clock, must be switched off when entering the processor in Sleep Mode.
		FCLK	Free running processor Clock.
		SysTick	The Cortex-M3 SysTick external clock.
		UDPCK	UDP Clock, required by USB Device Port operations.
		MCK		Peripheral Clocks, typically MCK, provided to the embedded peripherals.
	
	The Slow Clock
		By default, the RC Oscillator is enabled and selected.
		SUPC_CR = XTALSEL[1] to switch the slow clock on the crystal oscillator (XIN32, XOUT32).
		SUPC_MR = OSCBYPASS[1] and SUPC_CR = XTALSEL[1] to set in bypass mode (external clock signal on XIN32 has to be provided)
	
	The Main Clock
		After reset, the 4/8/12 MHz Fast RC Oscillator is enabled with the 4 MHz frequency selected and it is selected as the source of MAINCK.
		MAINCK is the default clock selected to start up the system.
		4/8/12 MHz Fast RC Oscillator
			CKGR_MOR = MOSCRCEN[0/1] disable or enable Fast RC Oscillator
			CKGR_MOR = MOSCRCF[] to select between 4/8/12MHz Fast RC Oscillator frequency
			PMC_SR -> MOSCRCS indicating the state of the Main Clock
		It is recommended to disable the Main Clock as soon as the processor no longer uses it and runs out of SLCK, PLLACK or PLLBCK.
		3 to 20 MHz Crystal or Ceramic Resonator-based Oscillator
			CKGR_MOR = MOSCXTEN[0/1] disable or enable Crystal or Ceramic Resonator-based Oscillator
			CKGR_MOR = MOSCXTCNT value for the Resonator's startup time
			PMC_SR -> MOSCXTS indicating the state of the Main Clock
		The 4/8/12 MHz Fast RC oscillator provides fast startup time.
		The 3 to 20 MHz Crystal or Ceramic Resonator-based oscillator is very accurate.
			CKGR_MOR = MOSCSEL[] selection between RC and Crystal Oscillator
			PMC_SR -> MOSCSELS signals the selection is done
		PLLA, PLLB
			The PLL clock signal has a frequency that depends on the respective source signal frequency and on the parameters DIV and MUL.
			The applied factor is (MUL + 1)/DIV. PLL is disabled when MUL = 0.
			CKGR_PLLR = PLLCOUNT value for the PLL's startup time
			PMC_MCKR = PLLDIV2[] to divide the PLL frequency by 2
			PMC_SR -> LOCK indicating the state of the PLL
		It is forbidden to change 4/8/12 MHz Fast RC oscillator, or main selection in CKGR_MOR register while Master clock source is PLL
		and PLL reference clock is the Fast RC oscillator.
	
	PMC_MCKR must not be programmed in a single write operation.
		if programming PLL: PMC_MCKR = CSS[PLL_CLK]
			Program PMC_MCKR = PRES.
			Wait PMC_SR -> MCKRDY.
			Program PMC_MCKR = CSS.
			Wait PMC_SR- > MCKRDY.
		if programming SCLK/Main CLK: PMC_MCKR = CSS[SLOW_CLK/MAIN_CLK]
			Program PMC_MCKR = CSS.
			Wait PMC_SR -> MCKRDY.
			Program PMC_MCKR = PRES.
			Wait PMC_SR -> MCKRDY.
	
	CONSUMPTION
			128-bit FLASH access	64-bit FLASH access		SRAM
		MHz		VDDCORE	Total		VDDCORE	Total		VDDCORE	Total
		64		38.11	39.22		33.88	36.99		32.29	35.46	mA
		48		29.46	31.81		27.23	29.56		24.51	26.9	mA
		32		22.13	23.72		21.3	22.9		16.56	18.18	mA
		24		17.66	19.97		17.8	20.1		12.98	15.32	mA
		12		9.3		9.42		9.05	9.14		6.24	6.37	mA
		8		6.31	6.41		6.13	6.2			4.17	4.3		mA
		4		2.91	2.92		2.78	2.85		1.9		2.01	mA
		2		1.54	1.56		1.43	1.5			1		1.12	mA
		1		0.85	0.84		0.79	0.86		0.57	0.67	mA
		0.5		0.49	0.5			0.46	0.53		0.35	0.45	mA
		0.25	0.3		0.33		0.3		0.34		0.23	0.33	mA
		0.125	0.21	0.25		0.22	0.24		0.2		0.28	mA
		0.032	0.035	0.093		0.033	0.093		0.03	0.12	mA
*/
void PS_SystemInit(void)
{
	// EEFC Flash Mode Register - Number of cycles for Read/Write operations = 3 + 1 (defines the maximum frequency); 128-bit access in read Mode only
	EFC->EEFC_FMR = (3 << 8);
	
	// Initialize main oscillator
	if(!(PMC->CKGR_MOR & (1 << 24))) // IF the Main On-Chip RC Oscillator is selected (the Main Crystal Oscillator is not selected).
	{
		// PMC Clock Generator Main Oscillator Register - Main Crystal Oscillator start-up time 8 x 8; the Main On-Chip RC Oscillator is enabled; the Main Crystal Oscillator is enabled
		PMC->CKGR_MOR = CKGR_MOR_PASSWORD | (0x08u << 8) | (0x01u << 3) | (0x01u << 0);
		while(!(PMC->PMC_SR & (0x01u << 0))); // wait for the Main XTAL oscillator to stabilize
	}
	
	// Switch to 3-20MHz Xtal oscillator
	PMC->CKGR_MOR = CKGR_MOR_PASSWORD | (0x08u << 8) | (0x01u << 3) | (0x01u << 0) | (0x01u << 24); // the Main Crystal Oscillator is selected
	while(!(PMC->PMC_SR & (0x01u << 16))); // wait for the Main Oscillator to be selected
	
	PMC->PMC_MCKR = (PMC->PMC_MCKR & ~(uint32_t)(0x03u << 0)) | (0x01u << 0); // Master Clock Source = Main Clock
	while(!(PMC->PMC_SR & (0x01u << 3))); // wait for the Master Clock to be ready
	
	// Initialize PLLA
	PMC->CKGR_PLLAR = (0x01u << 29) | (0x1fUL << 16) | (0x3fUL << 8) | (0x03UL << 0); // PLLA Multiplier = 31 + 1; PLLA Counter = 63 * 8; Divider = 3
	while(!(PMC->PMC_SR & (0x01u << 1))); // wait for PLLA to lock
	
	// Switch to main clock
	PMC->PMC_MCKR = (((0x01u << 4) | (0x02u << 0)) & ~(0x03u << 0)) | (0x01u << 0); // Selected clock divided by 2; Master Clock Source = Main Clock
	while(!(PMC->PMC_SR & (0x01u << 3))); // wait for the Master Clock to be ready
	
	// Switch to PLLA
	PMC->PMC_MCKR = (0x01u << 4) | (0x02u << 0); // Selected clock divided by 2; Master Clock Source = PLLA Clock
	while(!(PMC->PMC_SR & (0x01u << 3))); // wait for the Master Clock to be ready

	SystemCoreClock = 64000000UL;
}


/*
	Use at the start of the script when the standard SystemInit() or PS_SystemInit() are not used.
*/
void PS_FLASH_init(void)
{
	// EEFC Flash Mode Register - Number of cycles for Read/Write operations = 3 + 1 (defines the maximum frequency); 128-bit access in read Mode only
	EFC->EEFC_FMR = (3 << 8);
}


/*
	Manages disabling the PLL and switching the Main Clock to the Fast RC Oscillator.
	Required for the Wait Mode.
	
	moscrcf 0 - 4MHz, 1 - 8MHz, 2 - 12MHz
*/
void PS_switch_MCK_to_FastRC(uint32_t moscrcf, uint32_t prescaler)
{
	// Enable Fast RC oscillator but DO NOT switch to RC now . Keep MOSCSEL to 1
	PMC->CKGR_MOR = CKGR_MOR_PASSWORD | (0x01u << 24) | (0x01u << 3) | (0x01u << 0);
	while(!(PMC->PMC_SR & (0x01u << 17))); // wait for the Fast RC to stabilize
	
	// Switch from Main XTAL oscillator to Fast RC
	PMC->CKGR_MOR = CKGR_MOR_PASSWORD | (0x01u << 3) | (0x01u << 0);
	while(!(PMC->PMC_SR & (0x01u << 16))); // wait for Main Oscillator Selection Status bit MOSCSELS
	
	// Disable Main XTAL Oscillator
	PMC->CKGR_MOR = CKGR_MOR_PASSWORD | (0x01u << 3);
	// Change frequency of Fast RC oscillator
	PMC->CKGR_MOR = CKGR_MOR_PASSWORD | (PMC->CKGR_MOR & ~(0x07u << 4)) | (moscrcf << 4);
	while(!(PMC->PMC_SR & (0x01u << 17))); // wait for the Fast RC to stabilize
	
	// Switch to main clock
	PMC->PMC_MCKR = (PMC->PMC_MCKR & (uint32_t)~(0x03u << 0)) | (0x01u << 0);
	while(!(PMC->PMC_SR & (0x01u << 3)));
	
	PMC->PMC_MCKR = (PMC->PMC_MCKR & (uint32_t)~(0x07u << 4)) | (prescaler << 4);
	while(!(PMC->PMC_SR & (0x01u << 3)));
	
	// Stop PLLA and PLLB
	PMC->CKGR_PLLAR = (0x01 << 29);
	PMC->CKGR_PLLBR = (0x01 << 29);
}


/*
	
*/
void PS_switch_FastRC_to_XTAL(void)
{
	// Initialize main oscillator
	if(!(PMC->CKGR_MOR & (1 << 24))) // IF the Main On-Chip RC Oscillator is selected (the Main Crystal Oscillator is not selected).
	{
		// PMC Clock Generator Main Oscillator Register - Main Crystal Oscillator start-up time 8 x 8; the Main On-Chip RC Oscillator is enabled; the Main Crystal Oscillator is enabled
		PMC->CKGR_MOR = CKGR_MOR_PASSWORD | (0x08u << 8) | (0x01u << 3) | (0x01u << 0);
		while(!(PMC->PMC_SR & (0x01u << 0))); // wait for the Main XTAL oscillator to stabilize
	}
	
	// Switch to 3-20MHz Xtal oscillator
	PMC->CKGR_MOR = CKGR_MOR_PASSWORD | (0x08u << 8) | (0x01u << 3) | (0x01u << 0) | (0x01u << 24); // the Main Crystal Oscillator is selected
	while(!(PMC->PMC_SR & (0x01u << 16))); // wait for the Main Oscillator to be selected
	
	PMC->PMC_MCKR = (PMC->PMC_MCKR & ~(uint32_t)(0x03u << 0)) | (0x01u << 0); // Master Clock Source = Main Clock
	while(!(PMC->PMC_SR & (0x01u << 3))); // wait for the Master Clock to be ready
}


/*
	
*/
void PS_switch_FastRC_to_SLCK(void)
{
	PMC->PMC_MCKR = 0; // Master Clock Source = Slow Clock
	while(!(PMC->PMC_SR & (0x01u << 3))); // wait for the Master Clock to be ready
	
	PMC->CKGR_MOR = CKGR_MOR_PASSWORD; // the Main Crystal Oscillator and FastRC Oscillator are disabled
}


/*

*/
void PS_Brownout_Detector_enable(void)
{
	SUPC->SUPC_MR = (SUPC->SUPC_MR | (0xA5 << 24)) & ~(0x01u << 13); // KEY 0xA5; BODDIS 0
}


/*

*/
void PS_Brownout_Detector_disable(void)
{
	SUPC->SUPC_MR |= (0xA5 << 24) | (0x01u << 13); // KEY 0xA5; BODDIS 1
}


/*
	SLEEP MODE
		Only the core clock is stopped. The peripheral clocks can be enabled.

	'type' 0 WFI, 'type' 1 WFE
	
	CONSUMPTION
	MHz		VDDCORE	Total
	64		17.46	17.61	mA
	48		13.2	13.33	mA
	32		8.9		8.99	mA
	24		8.25	8.33	mA
	12		2.81	2.84	mA
	8		1.89	1.92	mA
	4		0.88	0.89	mA
	2		0.51	0.52	mA
	1		0.32	0.33	mA
	0.5		0.23	0.24	mA
	0.25	0.18	0.19	mA
	0.125	0.16	0.17	mA
	0.032	0.018	0.03	mA
*/
void PS_enter_Sleep_Mode(uint8_t type, uint8_t rtt, uint8_t rtc)
{
	PMC->PMC_FSMR = 0;							// LPM 0 - the WaitForInterrupt (WFI) or WaitForEvent (WFE) instruction makes the processor enter Sleep Mode
	if(rtt) PMC->PMC_FSMR |= (0x01u << 16);		// the RTT alarm enables a fast restart signal to the Power Management Controller
	if(rtc) PMC->PMC_FSMR |= (0x01u << 17);		// the RTC alarm enables a fast restart signal to the Power Management Controller
	SCB->SCR &= (uint32_t)~(0x01u << 2);		// SLEEPDEEP 0 - controls whether the processor uses sleep or deep sleep as its low power mode
	
	if(type) __WFE();
	else __WFI();
}


/*
	WAIT MODE
		The clocks of the core, peripherals and memories are stopped. However, the core, peripherals and memories power supplies are still powered.
		Requires switching MCK from external XTAL oscillator to Fast RC oscillator.
		After waking up the PMC automatically restarts the embedded 4/8/12 MHz fast RC oscillator.
		After waking up the processor executes the next instruction.
	
	routine:
		RTT_init()								-initialize wakeup method
		PS_switch_MCK_to_FastRC()				-switch the clock to Fast RC Oscillator
		PS_enter_Wait_Mode()					-command to enter the Wait Mode
		while(!(RTT->RTT_SR & (0x01u << 0)))	-wait for the RTT Alarm
		---
			waiting for the RTT Alarm
		---
		PS_SystemInit()							-reinitialize the PLLA clock (64MHz)
		
	CONSUMPTION
	VDDOUT	Total
	12.3	20.0	uA

*/
void PS_enter_Wait_Mode(uint8_t rtt, uint8_t rtc, uint8_t wkup12)
{
	uint32_t i;
	
	PMC->PMC_FSMR = (0x01u << 20);				// LPM 1 - the WaitForEvent (WFE) instruction of the processor makes the system to enter in Wait Mode
	if(rtt) PMC->PMC_FSMR |= (0x01u << 16);		// the RTT alarm enables a fast restart signal to the Power Management Controller
	if(rtc) PMC->PMC_FSMR |= (0x01u << 17);		// the RTC alarm enables a fast restart signal to the Power Management Controller
	if(wkup12) PMC->PMC_FSMR |= (0x01u << 12);	// the corresponding wake up input enables a fast restart signal to the Power Management Controller
	if(wkup12) PMC->PMC_FSPR &= ~(0x01u << 12);	// Defines the active polarity of the corresponding wake up input.
	SCB->SCR &= (uint32_t)~(0x01u << 2);		// SLEEPDEEP 0 - controls whether the processor uses sleep or deep sleep as its low power mode
	
	__WFE();
	
	// Wait for MOSCRCEN bit to ensure the core will not execute undesired instructions
	for (i = 0; i < 500; i++) __NOP();
	while(!(PMC->CKGR_MOR & (0x01u << 3)));		// wait while the Main On-Chip RC Oscillator is disabled
}


/*
	BACKUP MODE
		After waking up the processor restarts and executes the instructions from the beginning.
	
	routine:
		RTT_init()						-initialize backup method
		PS_enter_Backup_Mode()			-command to enter the Backup Mode
		---
			waiting for the RTT Alarm
		---
		MCU resets						-MCU resets after RTT alarm and starts executing instructions from the beginning
*/
void PS_enter_Backup_Mode(uint8_t rtt, uint8_t rtc)
{
	if(rtt) SUPC->SUPC_WUMR |= (0x01u << 2);	// RTTEN - the RTT alarm signal forces the wake up of the core power supply
	else SUPC->SUPC_WUMR &= ~(0x01u << 2);
	if(rtc) SUPC->SUPC_WUMR |= (0x01u << 3);	// RTCEN - the RTC alarm signal forces the wake up of the core power supply
	else SUPC->SUPC_WUMR &= ~(0x01u << 3);
	SCB->SCR |= (0x01u << 2);					// SLEEPDEEP 1 - controls whether the processor uses sleep or deep sleep as its low power mode
	__WFE();
}


/*
		PERIPHERAL CONSUMPTION
				?A/MHz	4		12		64		MHz
		UART0	17.28	0.069	0.207	1.106	mA
		UART1	16.85	0.067	0.202	1.078	mA
		SMC		21.05	0.084	0.253	1.347	mA
		PIOA	20.03	0.080	0.240	1.282	mA
		PIOB	5.37	0.021	0.064	0.344	mA
		PIOC	11.44	0.046	0.137	0.732	mA
		USART0	27.62	0.110	0.331	1.768	mA
		USART1	28.14	0.113	0.338	1.801	mA
		HSMCI	38.32	0.153	0.460	2.452	mA
		TWI0	17.9	0.072	0.215	1.146	mA
		TWI1	18.49	0.074	0.222	1.183	mA
		SPI		15.73	0.063	0.189	1.007	mA
		SSC		28.82	0.115	0.346	1.844	mA
		TC0		9.73	0.039	0.117	0.623	mA
		TC1		5.77	0.023	0.069	0.369	mA
		TC2		5.88	0.024	0.071	0.376	mA
		TC3		10.3	0.041	0.124	0.659	mA
		TC4		5.68	0.023	0.068	0.364	mA
		TC5		5.57	0.022	0.067	0.356	mA
		ADC		23.68	0.095	0.284	1.516	mA
		DACC	12.51	0.050	0.150	0.801	mA
		PWM		65.76	0.263	0.789	4.209	mA
		CRCCU	0.2		0.001	0.002	0.013	mA
		MAX		412.120	1.648	4.945	26.376	mA
*/
void PS_disable_peripheral_clocks(uint8_t rtc, uint8_t rtt, uint8_t uart0, uint8_t uart1, uint8_t pioa, uint8_t piob,
									 uint8_t twi0, uint8_t twi1, uint8_t spi, uint8_t tc0, uint8_t adc, uint8_t pwm)
{
	if(rtc)		PMC->PMC_PCDR0 |= (1 << ID_RTC);		// disable clock for RTC
	if(rtt)		PMC->PMC_PCDR0 |= (1 << ID_RTT);		// disable clock for RTT
	if(uart0)	PMC->PMC_PCDR0 |= (1 << ID_UART0);		// disable clock for UART0
	if(uart1)	PMC->PMC_PCDR0 |= (1 << ID_UART1);		// disable clock for UART1
	if(pioa)	PMC->PMC_PCDR0 |= (1 << ID_PIOA);		// disable clock for PIOA
	if(piob)	PMC->PMC_PCDR0 |= (1 << ID_PIOB);		// disable clock for PIOB
	if(twi0)	PMC->PMC_PCDR0 |= (1 << ID_TWI0);		// disable clock for TWI0
	if(twi1)	PMC->PMC_PCDR0 |= (1 << ID_TWI1);		// disable clock for TWI1
	if(spi)		PMC->PMC_PCDR0 |= (1 << ID_SPI);		// disable clock for SPI
	if(tc0)		PMC->PMC_PCDR0 |= (1 << ID_TC0);		// disable clock for TC0
	if(adc)		PMC->PMC_PCDR0 |= (1 << ID_ADC);		// disable clock for ADC
	if(pwm)		PMC->PMC_PCDR0 |= (1 << ID_PWM);		// disable clock for PWM
}