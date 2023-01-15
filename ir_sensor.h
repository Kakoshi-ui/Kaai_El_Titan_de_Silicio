/*
 * ir_sensor.h
 *
 * Created: 06/01/2023 03:14:34 p. m.
 *  Author: axel9
 */ 


#ifndef IR_SENSOR_H_
#define IR_SENSOR_H_

//Map Sensor Number to ADC Channel
#define SENSOR1 2	//Sensor1 connected to channel A2
#define SENSOR4 3	//Sensor4 connected to channel A3

//threshold
//Value = ((4.5v*1023)/5v)=920; where 4.5 is the voltage value returned from the collector
#define SENSOR_THRESH 920 //Sensor threshold

int read_rightSensor(void);
int read_leftSensor(void);

#endif /* IR_SENSOR_H_ */