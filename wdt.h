/*
 * wdt.h
 *
 * Created: 2023-04-03 17:04:58
 *  Author: mh293
 */ 


/********************************************************************************
* wdt.h: Inneh�ller drivrutiner f�r mikrokontrollerns Watchdog-timer, b�de i
*        System Reset Mode, vilket inneb�r att mikrodatorn �terst�lls vid
*        timeout, samt i Interrupt Mode, vilket inneb�r avbrott vid timeout.
*        Det �r ocks� m�jligt att kombinera tidigare n�mnda modes f�r att
*        avbrott sker, f�ljt av system�terst�llning.
*
*        Avbrottsvektorn f�r timeout-avbrott �r WDT_vect.
********************************************************************************/
#ifndef WDT_H_
#define WDT_H_

/* Inkluderingsdirektiv: */
#include "misc.h"

/********************************************************************************
* wdt_timeout: Enumeration f�r val av timeout f�r mikrodatorns Watchdog-timer.
********************************************************************************/
enum wdt_timeout
{
	WDT_TIMEOUT_16_MS   = 0,                                       /* 16 ms. */
	WDT_TIMEOUT_32_MS   = (1 << WDP0),                             /* 32 ms. */
	WDT_TIMEOUT_64_MS   = (1 << WDP1),                             /* 64 ms. */
	WDT_TIMEOUT_128_MS  = (1 << WDP1) | (1 << WDP0),               /* 128 ms. */
	WDT_TIMEOUT_256_MS  = (1 << WDP2),                             /* 256 ms. */
	WDT_TIMEOUT_512_MS  = (1 << WDP2) | (1 << WDP0),               /* 512 ms. */
	WDT_TIMEOUT_1024_MS = (1 << WDP2) | (1 << WDP1),               /* 1024 ms. */
	WDT_TIMEOUT_2048_MS = (1 << WDP2) | (1 << WDP1) | (1 << WDP0), /* 2048 ms. */
	WDT_TIMEOUT_4096_MS = (1 << WDP3),                             /* 4096 ms. */
	WDT_TIMEOUT_8192_MS = (1 << WDP3) | (1 << WDP0)                /* 8192 ms. */
};

/********************************************************************************
* wdt_reset: �terst�ller Watchdog-timern, vilket m�ste ske kontinuerligt innan
*            timern l�per ut f�r att undvika system�terst�llning eller avbrott.
********************************************************************************/
static inline void wdt_reset(void)
{
	asm("CLI");
	asm("WDR");
	MCUSR &= ~(1 << WDRF);
	asm("SEI");
	return;
}

/********************************************************************************
* wdt_init: Initierar Watchdog-timern med angiven timeout m�tt i millisekunder.
*
*           - timeout_ms: Timeout m�tt i millisekunder.
********************************************************************************/
static inline void wdt_init(const enum wdt_timeout timeout_ms)
{
	asm("CLI");
	WDTCSR = (1 << WDE) | (1 << WDCE);
	WDTCSR = (1 << WDE) | (uint8_t)(timeout_ms);
	asm("SEI");
	WDTCSR &= ~(1 << WDE);
	return;
}

/********************************************************************************
* wdt_clear: Nollst�ller Watchdog-timern.
********************************************************************************/
static inline void wdt_clear(void)
{
	wdt_reset();
	WDTCSR = 0x00;
	return;
}

/********************************************************************************
* wdt_enable_system_reset: Aktiverar Watchdog-timern i System Reset Mode,
*                          vilket inneb�r att systemet �terst�lls ifall
*                          Watchdog-timern l�per ut.
********************************************************************************/
static inline void wdt_enable_system_reset(void)
{
	wdt_reset();
	WDTCSR |= (1 << WDE);
	return;
}

/********************************************************************************
* wdt_disable_system_reset: Inaktiverar Watchdog-timern i System Reset Mode,
*                           vilket inneb�r att systemet inte �terst�lls ifall
*                           Watchdog-timern l�per ut.
********************************************************************************/
static inline void wdt_disable_system_reset(void)
{
	wdt_reset();
	WDTCSR &= ~(1 << WDE);
	return;
}

/********************************************************************************
* wdt_enable_interrupt: Aktiverar Watchdog-timern i Interrupt Mode, vilket
*                       inneb�r att ett avbrott med avbrottsvektor WDT_vect
*                       �ger rum ifall Watchdog-timern l�per ut.
********************************************************************************/
static inline void wdt_enable_interrupt(void)
{
	wdt_reset();
	WDTCSR |= (1 << WDIE);
	return;
}

/********************************************************************************
* wdt_disable_interrupt: Inaktiverar Watchdog-timern i Interrupt Mode, vilket
*                        inneb�r att avbrott inte �ger rum ifall Watchdog-timern
*                        l�per ut.
********************************************************************************/
static inline void wdt_disable_interrupt(void)
{
	wdt_reset();
	WDTCSR &= ~(1 << WDIE);
	return;
}

#endif /* WDT_H_ */