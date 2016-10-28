/*
 * ARM_WATCHDOG.c
 *
 * Created: 28.10.2016 17:28:29
 *  Author: Tomy2
 */ 


#include "sam.h"
#include "ARM_WATCHDOG.h"


/*
	The Watchdog is built around a 12-bit down counter.
	The Watchdog Timer uses the Slow Clock divided by 128.
	The maximum period is 16 seconds (Slow Clock of 32.768 kHz).
	
	After a Processor Reset, the value of WDV is 0xFFF.
	A default Watchdog is running at reset, i.e., at power-up.
	
	The Watchdog Mode Register (WDT_MR) can be written only once. Only a processor reset resets it.
	Writing the WDT_MR register reloads the timer with the newly programmed mode parameters.
	
		PERIOD		A 12-bit value for the Slow Clock counter.
		
		IDLEHALT	1	The Watchdog stops when the system is in idle state.
					0	The Watchdog runs when the system is in idle mode.
*/
void WATCHDOG_enable(uint16_t period, uint8_t idleHalt)
{
	period &= 0x0FFF;																		// WatchDog Timer is 12-bits
	
	WDT->WDT_MR = (idleHalt << 29) | (period << 16) | WDT_MR_WDRSTEN | (period << 0);
}


/*
	WatchDog enabled by default.
	Must be disabled when not used.
*/
void WATCHDOG_disable(void)
{
	WDT->WDT_MR = WDT_MR_WDDIS;																// disable WatchDog
}


/*
	In normal operation, the user reloads the Watchdog at regular intervals before the timer underflow occurs,
	by writing the Control Register (WDT_CR) with the bit WDRSTT to 1.
	The Watchdog counter is then immediately reloaded from WDT_MR and restarted, and the Slow Clock 128 divider is reset and restarted.
*/
void WATCHDOG_restart(void)
{
	WDT->WDT_MR = (0xA5 << 24) | WDT_CR_WDRSTT;												// restarts the WatchDog
}