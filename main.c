
/********************************************************************************
* Filerna som är modifierade/skapade i detta projekt är:
* 
*  1. display.c
*  2. header.h        
*  3. isr.c
*  4. main.c
*  5. setup.c
*     
* Resterande filer är för funktionalitet och test.  
********************************************************************************/


/********************************************************************************
* main.c: Demonstration av inbyggt system innefattande 7-segmentsdisplayer.
*         Timerkrets Timer 1 används för att räkna upp befintligt tal på
*         7-segmentsdisplayerna en gång per sekund.
*
*         Tre knappar styr displayernas funktionalitet för 
*         1. start/stop.
*         2. upp/ned -räkning.
*         3. tänd/släck.
*
*         Detta sparas i sin tur i eeprom för att få ett permanent minne efter 
*         att strömtillförsel har brutits.
*
********************************************************************************/


#include "header.h"

/********************************************************************************
* main: Initierar systemet vid start. Uppräkning sker sedan kontinuerligt
*       av talet på 7-segmentsdisplayerna en gång per sekund, 0-99.
*       
*       setup() initierar systemet. 
*       wdt_reset() systemåterställer systemet utefter tidsinställning i setup().
*       display_reset() kan användas för att återställa alla värden till 
*       startvärden. 
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