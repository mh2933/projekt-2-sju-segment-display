
#include "header.h"

/********************************************************************************
* setup: Initierar systemet enligt följande:
*
*        1. Initierar Watchdog-timern med en timeout på 1024 ms. System reset
*           aktiveras så att systemåterställning sker ifall Watchdog-timern
*           löper ut.
*
*        2. Initierar 7-segmentsdisplayerna med startvärde 0 och aktiverar
*           uppräkning en gång per sekund.
*
*        3. Avbrottstimer Timer 0 initieras för debounce.
*
*        4. Knappar initieras samt avbrott för dessa.
********************************************************************************/
void setup(void)
{
	wdt_init(WDT_TIMEOUT_1024_MS);
	wdt_enable_interrupt();
	
	display_init();
	
	timer_init(&t0, TIMER_SEL_0, 300);
	
	button_init(&b1, 13); // tända/släcka display
	button_init(&b2, 12); // riktning upp/ned- räkning
	button_init(&b3, 11); // start/stop av räknaren
	button_enable_interrupt(&b1);
	button_enable_interrupt(&b2);
	button_enable_interrupt(&b3);
	
	return;
}
