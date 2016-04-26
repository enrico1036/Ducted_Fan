/*
 * Servo.h
 *
 *  Created on: 22/nov/2015
 *      Author: Enrico Gambini
 */

#ifndef DUCTED_DRIVERS_SERVO_H_
#define DUCTED_DRIVERS_SERVO_H_

#include "LowLevelDrivers/MTU2a/MTU_C4.h"
#include "support_functions.h"

/* -----------------------------------------------------------------------------------------------------
 * Description:	2 channels servo driver.
 * 				Default used timer channel is MTU4 with a PWM period of 20ms
 *
 * Usage: 	-Servos are assigned to the port PE2 (channel 1) and PE1 (channel 2)
 * 				respectively on board pin JN2-23 and JN2-22
 *  ----------------------------------------------------------------------------------------------------- */

#define SERVO_PITCH 1
#define SERVO_ROLL 2
#define SERVO_PWM_SIGNAL_PERIOD_US 20000.00	//20ms
#define SERVO_MIN_US 700	//TODO: look for the right value
#define SERVO_MAX_US 2400	//TODO: look for the right value
#define SERVO_MIN_DEG 0
#define SERVO_MAX_DEG 180
#define SERVO_MIN_BOUND_DEG 60 	// servo minimum physical limit
#define SERVO_MAX_BOUND_DEG 120	// servo maximum physical limit

#define SERVO_PITCH_TRIM 10;	// pitch servo offset in deg
#define SERVO_ROLL_TRIM 0;	// roll servo offset in deg

void Servos_Init();
void Servos_Off();
void Servo_Write_PWM(int channel, float value);
void Servo_Write_us(int channel, float us);
void Servo_Write_deg(int channel, float deg);

#endif /* DUCTED_DRIVERS_SERVO_H_ */
