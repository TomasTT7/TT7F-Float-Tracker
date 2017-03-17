/*
CLOCK GENERATORS
	A Low Power 32,768 Hz Slow Clock Oscillator with bypass mode.
	A Low Power RC Oscillator
	A 3 to 20 MHz Crystal or Ceramic Resonator-based Oscillator, which can be bypassed.
	A factory programmed Fast RC Oscillator. 3 output frequencies can be selected: 4, 8 or 12 MHz. By default 4MHz is selected.
	Two 60 to 130 MHz programmable PLL (input from 3.5 to 20 MHz), capable of providing the clock MCK to the processor and to the peripherals.

CLOCKS
	SLCK, the Slow Clock, the only permanent clock within the system.
	MAINCK, the output of the Main Clock Oscillator selection: either the Crystal or Ceramic Resonator-based Oscillator or 4/8/12 MHz Fast RC Oscillator.
	PLLACK, the output of the Divider and 60 to 130 MHz programmable PLL (PLLA).
	PLLBCK, the output of the Divider and 60 to 130 MHz programmable PLL (PLLB).

PMC_PCER0
	SUPC	-	(0)	Supply Controller
	RSTC	-	(1)	Reset Controller
	RTC		2	Real Time Clock
	RTT		3	Real Time Timer
	WDT		4	Watchdog Timer
	PMC		5	Power Management Controller
	EFC		6	Enhanced Embedded Flash Controller
	UART0	8	UART 0
	UART1	9	UART 1
	PIOA	11	Parallel I/O Controller A
	PIOB	12	Parallel I/O Controller B
	USART0	14	USART 0
	USART1	15	USART 1
	HSMCI	18	Multimedia Card Interface
	TWI0	19	Two Wire Interface 0
	TWI1	20	Two Wire Interface 1
	SPI		21	Serial Peripheral Interface
	SSC		22	Synchronous Serial Controller
	TC0		23	Timer/Counter 0
	TC1		24	Timer/Counter 1
	TC2		25	Timer/Counter 2
	ADC		29	Analog To Digital Converter
	DACC	30	Digital To Analog Converter
	PWM		31	Pulse Width Modulation

PMC_PCER1
	CRCCU	0	(32)	CRC Calculation Unit
	ACC		1	(33)	Analog Comparator
	UDP		2	(34)	USB Device Port
*/

#ifndef ARM_POWER_SAVE_H
#define ARM_POWER_SAVE_H

#include "stdint.h"


#define CKGR_MOR_PASSWORD (0x37u << 16)									// KEY to write CKGR_MOR


// Functions
void PS_SystemInit(uint8_t mula, uint8_t diva, uint8_t pres);
void PS_FLASH_init(void);
void PS_switch_MCK_to_FastRC(uint32_t moscrcf, uint32_t pres);			// moscrcf 0 - 4MHz, 1 - 8MHz, 2 - 12MHz
void PS_switch_FastRC_to_XTAL(void);
void PS_switch_FastRC_to_SLCK(void);
void PS_Brownout_Detector_enable(void);
void PS_Brownout_Detector_disable(void);
void PS_enter_Sleep_Mode(uint8_t type, uint8_t rtt, uint8_t rtc);		// type 0 WFI, type 1 WFE, RTT or RTC alarm
void PS_enter_Wait_Mode(uint8_t rtt, uint8_t rtc, uint8_t wkup12);		// enable RTT, RTC or WKUP12 as a wakeup source
void PS_enter_Backup_Mode(uint8_t rtt, uint8_t rtc);					// enable RTT or RTC alarm as a wakeup source
void PS_disable_peripheral_clocks(uint8_t rtc, uint8_t rtt, uint8_t uart0, uint8_t uart1, uint8_t pioa, uint8_t piob,
									uint8_t twi0, uint8_t twi1, uint8_t spi, uint8_t tc0, uint8_t adc, uint8_t pwm);

#endif // ARM_POWER_SAVE_H_