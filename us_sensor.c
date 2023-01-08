/*
 * us_sensor.c
 *
 * Created: 19/12/2022 08:24:57 p. m.
 *  Author: josel
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#define INSTR_PER_MS 16000
#define MAX_RESP_TIME_MS 50				//instructions per milliseconds (depends on MCU clock, 16Mhz current)
#define DELAY_BETWEEN_TESTS_MS 50		//timeout - max time to wait for low voltage drop

volatile long result = 0;				//echo canceling time between sampling
volatile unsigned char up=0;			
volatile unsigned char running = 0;
volatile uint32_t timerCounter = 0;
volatile int us_presence = 0;
volatile float distance = 0;

//timer overflow interrupt, each time when timer value passes 255 value
SIGNAL(TIMER0_OVF_vect){
	if(up){				//voltage rise was detected previously
		timerCounter++;		//count the number of overflows
		//don t wait too long for the sonar end response, stop if time for measuring the distance exceed the limits
		uint32_t ticks = timerCounter*256+TCNT0;
		uint32_t max_ticks = (uint32_t)MAX_RESP_TIME_MS*INSTR_PER_MS;
		if(ticks>max_ticks){
			up=0;			//stop counting timer values
			running=0;		//ultrasound scan done
			result = -1;	//show that measurement failed with a timeout (could return max distance here if needed)
		}
		
	}
}

//interrupt on INT0 pin, to detect high/low voltage changes
ISR(INT0_vect){
	if (running){		//accept interrupts only when sonar was started
		if(up==0){		//voltage rise, start time measurement 
			up=1;
			timerCounter=0;
			TCNT0=0;	//reset timer counter
		}
		else{
			//voltage drop, stop time measurement
			up=0;
			//d = [time_s*340m/s]/2=time_us/58
			result =(timerCounter*256+TCNT0)/58;
			distance = result/58;
			running=0;
		}
	}
}

void send_trigger(void){	
	PORTB &= (0<<PB0);	//clear to zero for 1us
	_delay_us(4);
	PORTB |= (1<<PB0);	//set high for 10us
	running = 1;		//sonar launched
	_delay_us(10);
	PORTB &= (0<<PB0);	//clear
}

//initialize external interrupt
void init_ext_int0(void){
	EICRA |= (1<<ISC00);	//Interrupt on any logical change 
	EIMSK |= (1<<INT0);		//enable INT0
}

//initialize timer to count up
void init_timer0(void){
	TCCR0B |= (1 << CS00);		//select internal clock with no prescaling
	TCNT0 = 0;				// reset counter to zero
	TIMSK0 |= (1<<TOIE0);	//enable timer interrupt
	sei();					//enable all(global)interrupts
}

void example_sonar(void){
	for(;;){		
		if(running==0){		//launch only when next iteration can happen
			//create a delay between tests, to compensate for old echoes
			_delay_ms(DELAY_BETWEEN_TESTS_MS);
			send_trigger();
		}
	}
}

float get_distance(void){
	distance=result;
	return distance;
}

