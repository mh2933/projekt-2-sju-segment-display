
#ifndef HEADER_H_
#define HEADER_H_

/* Inkluderingsdirektiv: */
#include <avr/io.h>
#include "led.h"
#include "button.h"
#include "timer.h"
#include "eeprom.h"
#include "wdt.h"
#include "display.h"
#include "misc.h"
#include "wdt.h"
#include "serial.h"



/* Deklaration av globala objekt: */
extern struct led l1;
extern struct button b1, b2, b3;
extern struct timer t0, t1;

void setup(void);

#endif /* HEADER_H_ */