/*
 * motors.h
 *
 * Created: 21/12/2022 12:04:35 p. m.
 *  Author: axel9
 */ 


#ifndef MOTORS_H_
#define MOTORS_H_

#define motor_stop		0
#define motor_backward	1
#define motor_forward	2
#define robo_speed		255

void init_timer1();
void motor_right(uint8_t dir,uint8_t speed);
void motor_left(uint8_t dir,uint8_t speed);

#endif /* MOTORS_H_ */