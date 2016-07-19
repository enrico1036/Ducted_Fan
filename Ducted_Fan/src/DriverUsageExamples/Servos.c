/*
 * Servos.c
 *
 *  Created on: 19/lug/2016
 *      Author: Enrico Gambini
 */
#include "Ducted_Drivers/Servo.h"

#define SERVO_ONE 1
#define SERVO_TWO 2

void main(void) {
	/* Initialize servos */
	Servos_Init();

	/*Set servo position to deg */
	float deg = 90;
	Servo_Write_deg(SERVO_ONE, deg);

	/* alternatively you can send signal choosing wave up time in microseconds */
	int us = 1000;
	Servo_Write_us(SERVO_TWO, us);

	/* or even choose signal duty cycle */
	float duty = 50; //50% duty
	Servo_Write_PWM(SERVO_TWO, duty);
}
