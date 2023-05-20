
/********************************************************************************
* Filerna som �r modifierade/skapade i detta projekt �r:
* 
*  1. display.c
*  2. header.h        
*  3. isr.c
*  4. main.c
*  5. setup.c
*     
* Resterande filer �r f�r funktionalitet och test.  
********************************************************************************/


/********************************************************************************
* main.c: Demonstration av inbyggt system innefattande 7-segmentsdisplayer.
*         Timerkrets Timer 1 anv�nds f�r att r�kna upp befintligt tal p�
*         7-segmentsdisplayerna en g�ng per sekund.
*
*         Tre knappar styr displayernas funktionalitet f�r 
*         1. start/stop.
*         2. upp/ned -r�kning.
*         3. t�nd/sl�ck.
*
*         Detta sparas i sin tur i eeprom f�r att f� ett permanent minne efter 
*         att str�mtillf�rsel har brutits.
*
********************************************************************************/


#include "header.h"

/********************************************************************************
* main: Initierar systemet vid start. Uppr�kning sker sedan kontinuerligt
*       av talet p� 7-segmentsdisplayerna en g�ng per sekund, 0-99.
*       
*       setup() initierar systemet. 
*       wdt_reset() system�terst�ller systemet utefter tidsinst�llning i setup().
*       display_reset() kan anv�ndas f�r att �terst�lla alla v�rden till 
*       startv�rden. 
********************************************************************************/
int main(void)
{
	setup();
	
	//display_reset();
	
	while (1)
	{
		wdt_reset();
	}

	return 0;
}