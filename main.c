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
#include "adc.h"

// Global variables
volatile float us_distance = 0.0;

void turn_back(void);

int main(){
	
	init_ports();
	power_on();
	init_timer1();
	
	adc_init();
	
	init_ext_int0();
	init_timer0();
	
	while(1){
		PORTB |= 1 << PB5;
		example_sonar();
		
		if(read_rightSensor() == 0 && read_leftSensor() == 0){
			us_distance = get_distance();
			if (us_distance > 50){
				motor_left(motor_forward,254);
				motor_right(motor_forward,254);
			}
			else if(us_distance < 50){
				motor_left(motor_stop,0);
				motor_right(motor_forward,100);
			}
		}
		else if (read_rightSensor() == 1 || read_leftSensor() == 1){
			turn_back();
		}
	}
}

void turn_back(void){
	motor_right(motor_stop,0);
	motor_left(motor_stop,0);
	_delay_ms(500);
	
	motor_left(motor_backward,100);
	motor_right(motor_backward,100);
	_delay_ms(2500);
	
	motor_right(motor_stop,0);
	motor_left(motor_backward,250);
	_delay_ms(2500);
	
	motor_left(motor_stop,0);
	motor_right(motor_forward,250);
	_delay_ms(2500);
}