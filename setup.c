
#include "header.h"

/********************************************************************************
* setup: Initierar systemet enligt f�ljande:
*
*        1. Initierar Watchdog-timern med en timeout p� 1024 ms. System reset
*           aktiveras s� att system�terst�llning sker ifall Watchdog-timern
*           l�per ut.
*
*        2. Initierar 7-segmentsdisplayerna med startv�rde 0 och aktiverar
*           uppr�kning en g�ng per sekund.
*
*        3. Avbrottstimer Timer 0 initieras f�r debounce.
*
*        4. Knappar initieras samt avbrott f�r dessa.
********************************************************************************/
void setup(void)
{
	wdt_init(WDT_TIMEOUT_1024_MS);
	wdt_enable_interrupt();
	
	display_init();
	
	timer_init(&t0, TIMER_SEL_0, 300);
	
	button_init(&b1, 13); // t�nda/sl�cka display
	button_init(&b2, 12); // riktning upp/ned- r�kning
	button_init(&b3, 11); // start/stop av r�knaren
	button_enable_interrupt(&b1);
	button_enable_interrupt(&b2);
	button_enable_interrupt(&b3);
	
	return;
}
