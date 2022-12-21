/*
 * Kaai_ElTitan.c
 *
 * Created: 19/12/2022 12:58:45 p. m.
 * Author : axel9
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "leds.h"
#include "ports.h"
#include "us_sensor.h"

int main(void){
	init_ports();
	power_on();
	
	
}

