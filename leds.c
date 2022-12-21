/*
 * leds.c
 *
 * Created: 19/12/2022 02:44:30 p. m.
 *  Author: axel9
 */ 
#include <avr/io.h>
#include <util/delay.h>

void power_on(void){
	int i;
	for (i=0;i<6;i++){
		PORTB ^= 1 << PB5;
		_delay_ms(100);
	}
}