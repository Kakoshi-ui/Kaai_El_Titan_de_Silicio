/*
 * leds.c
 *
 * Created: 19/12/2022 02:44:30 p. m.
 *  Author: axel9
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include "us_sensor.h"

volatile int us_detect=0;

void power_on(void){
	int i;
	for(i=0;i<10;i++){
		PORTB ^= 1 << PB5;
		_delay_ms(500);
	}
}
