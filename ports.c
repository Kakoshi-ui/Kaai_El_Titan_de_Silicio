/*
 * Ports.c
 *
 * Created: 19/12/2022 01:08:05 p. m.
 *  Author: josel
 */ 
#include <avr/io.h>

void init_ports(void){
	//Ultrasonic sensor
	DDRB |= (1 << PB0);			//PB0 Enable output for trigger
	PORTB &= (0 << PB0);		//Clear Output
	DDRD &= 0 << PD2;			//Input for echo on external interrupt
	PORTD |= (1 << PD1);		//Activate PullUp Resistor
	//Timer
	DDRB |= (1 << PB1);			//OC1A enable Output for Left Motor
	DDRB |= (1 << PB2);			//OC1B enable Output for right motor
	//Motor Direction
	DDRB |= (1 << PB3) | (1 << PB4);//Left motor
	DDRC |= (1 << PC4) | (1 << PC5);//Right motor
	//Power on indicator
	DDRB |= (1 << PB5);				//Power on led indicator
}