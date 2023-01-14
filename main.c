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

int main(){
	init_ports();
	power_on();
	init_timer1();
	
	motor_left(motor_stop,0);
	motor_right(motor_stop,0);
	
	init_ext_int0();
	init_timer0();
	
	while (1){
		example_sonar();
		if(get_distance() >= 0.10){
			PORTB |= 1 << PB5;
			motor_left(motor_forward,250);
			motor_right(motor_forward,250);
		}
		else{
			PORTB &= 0 << PB5;
			motor_left(motor_stop,0);
			motor_right(motor_stop,0);
		}
	}
}
