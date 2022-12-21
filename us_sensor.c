/*
 * us_sensor.c
 *
 * Created: 19/12/2022 08:24:57 p. m.
 *  Author: axel9
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#define INSTR_PER_MS 16000
#define MAX_RESP_TIME_MS 50
#define DELAY_BETWEEN_TESTS_MS 50

volatile long result = 0;
volatile unsigned char up=0;
volatile unsigned char running = 0;
volatile uint32_t timerCounter = 0;

SIGNAL(TIMER0_OVF_vect){
	if(up){
		timerCounter++;
		uint32_t ticks = timerCounter*256+TCNT0;
		uint32_t max_ticks = (uint32_t)MAX_RESP_TIME_MS*INSTR_PER_MS;
		if(ticks>max_ticks){
			up=0;
			running=0;
			result = -1;
		}
		
	}
}

ISR(INT0_vect){
	if (running){
		if(up==0){
			up=1;
			timerCounter=0;
			TCNT0=0;
		}
		else{
			up=0;
			result =(timerCounter*256+TCNT0)/258;
			running=0;
		}
	}
}

void send_trigger(void){
	PORTB &= (0<<PB0);
	_delay_us(4);
	PORTB |= (1<<PB0);
	running = 1;
	_delay_us(10);
	PORTB &= (0<<PB0);
}

void init_ext_int0(void){
	EICRA |= (1<<ISC00);
	EIMSK |= (1<<INT0);
}

void init_timer0(void){
	TCCR0B |= (1<<CS00)
	TCNT0 = 0;
	TIMSK0 |= (1<<TOIE0);
	sei();
}

void example_sonar(void){
	for(;;){
		if(running==0){
			_delay_ms(DELAY_BETWEEN_TESTS_MS);
			send_trigger();
		}
	}
}