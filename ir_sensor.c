/*
 * ir_sensor.c
 *
 * Created: 06/01/2023 03:14:50 p. m.
 *  Author: axel9
 */ 
#include <avr/io.h>
#include <util/delay.h>

volatile int irs1 = 0;
volatile int irs2 = 0;
volatile int irs3 = 0;
volatile int irs4 = 0;
int ir_detect=0;

void init_irSensor(void){
	DDRD &= (0 << PD3) & (0 << PD4);
	DDRD &= (0 << PD5) & (0 << PD6);
}

int det_bline(void){
	irs1=PIND3;
	irs2=PIND4;
	irs3=PIND5;
	irs4=PIND6;
	if (irs1 == 0 || irs2 == 0 || irs3 == 0 || irs4==0){
		ir_detect=1;
	}
	else {
		ir_detect=0;
	}
	return ir_detect;
}