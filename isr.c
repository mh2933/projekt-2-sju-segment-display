

/********************************************************************************
* isr.c: Innehåller avbrottsrutiner där 
*        PCINT_0 avnänds för styrning av de tre knapparna
*
*        button 1(pin 13) = tänder/släcker displayer.
*        button 2(pin 12) = sätter upp/ned räkning.
*        button 3(pin 11) = startar/stoppar upp/ned räkning.
********************************************************************************/
#include "header.h"

struct led l1;
struct timer t0, t1;
struct button b1, b2, b3;

bool button_enabled = false;

ISR (PCINT0_vect)
{
	/* debounce */
	 disable_pin_change_interrupt(IO_PORTB);
	 timer_enable_interrupt(&t0);
	
	if (button_is_pressed(&b1))
	{
		display_enable_output();
		
		button_enabled = !button_enabled;
		
		if (button_enabled)
		{
			display_toggle_output(); // släcker display om button_enabled
		}
	}
	
	if (button_is_pressed(&b2))
	{
		timer_enable_interrupt(&t0);
		
		button_enabled = !button_enabled;
		
		if (button_enabled)
		{
			display_toggle_count_direction(); // togglar riktning av upp/ned räkning
		}	
	}
	
	if (button_is_pressed(&b3))
	{
		display_enable_count();
		timer_enable_interrupt(&t0);
		
		button_enabled = !button_enabled;
		
		if (button_enabled & display_count_enabled())
		{
			display_toggle_count();
		}
		else if (!button_enabled & !display_count_enabled())
		{
			display_toggle_count();
		}
	}
	return;
}

/********************************************************************************
* TIMER0_OVF_vect: Innehåller avbrottsrutin för debounce timer 0
*              
********************************************************************************/
ISR (TIMER0_OVF_vect)
{
	timer_count(&t0);

	if (timer_elapsed(&t0))
	{
		enable_pin_change_interrupt(IO_PORTB);
		timer_disable_interrupt(&t0);
	}

	return;
}

/********************************************************************************
* ISR (TIMER1_COMPA_vect): Avbrottsrutin som äger rum vid uppräkning till 256 av
*                          Timer 1 i CTC Mode, vilket sker var 0.128:e
*                          millisekund när timern är aktiverad. En gång per
*                          millisekund togglas talet utskrivet på
*                          7-segmentsdisplayerna mellan tiotal och ental.
********************************************************************************/
ISR (TIMER1_COMPA_vect)
{
	display_toggle_digit();
	return;
}

/********************************************************************************
* ISR (TIMER2_OVF_vect): Avbrottsrutin som äger rum vid uppräkning till 256 av
*                        Timer 2 i Normal Mode, vilket sker var 0.128:e
*                        millisekund när timern är aktiverad. En gång per sekund
*                        inkrementeras talet utskrivet på 7-segmentsdisplayerna.
********************************************************************************/
ISR (TIMER2_OVF_vect)
{
	display_count();
	return;
}
