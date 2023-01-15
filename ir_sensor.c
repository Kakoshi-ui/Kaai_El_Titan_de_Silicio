/*
 * ir_sensor.c
 *
 * Created: 06/01/2023 03:14:50 p. m.
 *  Author: axel9
 */ 
#include <avr/io.h>
#include "adc.h"
#include "ir_sensor.h"
uint16_t ir_sensor1, ir_sensor4; // using two ir_sensors to detect border line
uint8_t sensor1, sensor4;		 // where sensor1 is the right side sensor & sensor4 is the left side sensor
								 // from H bridge side view
int read_rightSensor(void){
	
	ir_sensor1 = read_adc(SENSOR1);
	if (ir_sensor1 > SENSOR_THRESH){
		sensor1 = 0;
	}
	else if(ir_sensor1 < SENSOR_THRESH){
		sensor1 = 1;
	}
	return sensor1;

}

int read_leftSensor(void){
	ir_sensor4 = read_adc(SENSOR4);
	if (ir_sensor4 > SENSOR_THRESH){
		sensor4 = 0;
	}
	else if(ir_sensor4 < SENSOR_THRESH){
		sensor4 = 1;
	}
	return sensor4;
}
