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
#include "motors.h"
#include "ir_sensor.h"

int object_presence=0;

int main(){
	
	init_ports(); 
	init_irSensor();//Initialize all ports needed in the system
	power_on();				//Turn on the L led, it will count to five until the fights starts 
	init_ext_int0();
	init_timer0();			//initialize the timer in INT1
	init_timer1();
	example_sonar();
	
	
	
}

