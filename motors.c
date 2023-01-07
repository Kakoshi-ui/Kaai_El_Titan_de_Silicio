/*
 * motors.c
 *
 * Created: 21/12/2022 12:04:58 p. m.
 *  Author: josel
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include "motors.h"

//PWM for speed control
void init_timer1(){
	TCCR1A |= (1<<WGM10);//WGM10=1 PWM, Phase correct, 8-bit
	TCCR1A |= (1<<COM1A1)|(1<<COM1B1);	//low level on OC1A/OC1B when up-counting
	
	TCCR1B |= (1<<CS12)|(1<<CS10);		//frequency=fcpu/1024 aprox 15Khz (motors operating frecuency)
}

//motor right direction&speed control
void motor_right(uint8_t dir, uint8_t speed){
	//direction
	if(dir==motor_stop){
		PORTC &= 0 << PC4;
		PORTC &= 0 << PC5;
	}
	else if(dir == motor_backward){
		PORTC &= 0 << PC4;
		PORTC |= 1 << PC5;
	}
	else if(dir == motor_forward){
		PORTC &= 0 << PC5;
		PORTC &= 1 << PC4;
	}
	//speed
	uint8_t sreg = SREG;//status register
	
	cli();
	OCR1B = (uint8_t)(((float)speed/255.0*robo_speed));
	SREG = sreg;
}

//motor left direction&speed control
void motor_left(uint8_t dir, uint8_t speed){
	//direction
	if(dir==motor_stop){
		PORTB &=0 << PB4;
		PORTB &=0 << PB3;
	}
	else if(dir == motor_backward){
		PORTB &= 0 << PB4;
		PORTB |= 1 << PB3;
	}
	else if(dir == motor_forward){
		PORTB &= 0 << PB3;
		PORTB |= 1 << PB4;
	}
	//speed
	uint8_t sreg = SREG;//status register
	
	cli();
	OCR1B = (uint8_t)(((float)speed/255.0*robo_speed));
	SREG = sreg;
}