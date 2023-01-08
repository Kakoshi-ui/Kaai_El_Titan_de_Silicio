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
	init_irSensor();//Initialize all ports needed in the system
	power_on();				//Turn on the L led, it will count to five until the fights starts 
	init_ext_int0();		// initialize the external interrupts in the ports INT0 & INT1
	init_timer0();			//initialize the timer 0
	init_timer1();			//initialize the timer 1
	example_sonar();		//initialize the trigger signal for the us sensor
	
		if(get_distance() > 0.30){
		motor_right(motor_forward,50);
		motor_left(motor_stop,0);
		_delay_ms(2000);
		
		motor_right(motor_backward,50);
		_delay_ms(2000);
		
		motor_left(motor_forward,50);
		motor_right(motor_stop,0);
		_delay_ms(2000);
		
		motor_left(motor_backward,0);
		_delay_ms(2000);
	}
	no_bline: while(det_bline() != 1){					//detect that the robo are not in the border line so it can go
		 if(get_distance() < 0.05){						//detects the distance between the robo an de object in front, depends on the distance the robo will
			 motor_right(motor_forward,255);			// run to a different velocity
			 motor_left(motor_forward,255);
		 }else if(get_distance() < 0.10){
			 motor_right(motor_forward,155);
			 motor_left(motor_forward,155);
		 }else if (get_distance() < 0.15){
			 motor_right(motor_forward,100);
			 motor_left(motor_forward,100);
		 }else if(get_distance() > 0.28){
			 motor_right(motor_stop,0);
			 motor_left(motor_stop,0);
		 }else if(get_distance() < 0.28){
			 motor_right(motor_forward,50);
			 motor_left(motor_forward,50);
		}
	}
	
	if (det_bline() == 1 && right_border_out() == 1){
		motor_right(motor_backward,100);
		motor_left(motor_backward,100);
		_delay_ms(1000);
		
		motor_left(motor_stop,0);
		motor_right(motor_backward,100);
		goto no_bline;
		}else if (det_bline() ==1 && left_border_out()==1){
		motor_right(motor_backward,100);
		motor_left(motor_backward,100);
		_delay_ms(1000);
		
		motor_right(motor_stop,0);
		motor_left(motor_backward,100);
		goto no_bline;
		}else if (det_bline() == 1){
		motor_right(motor_backward,100);
		motor_left(motor_backward,100);
		_delay_ms(1000);
		
		motor_left(motor_stop,0);
		motor_right(motor_backward,100);
		goto no_bline;
	}
}

