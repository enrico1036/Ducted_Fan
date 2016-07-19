/*
 * Motors.c
 *
 *  Created on: 19/lug/2016
 *      Author: Enrico Gambini
 */
#include "Ducted_Drivers/Motor.h"


#define MOTOR_ONE 1
#define MOTOR_TWO 2

void main(void) {
	/* Initialize motors */
	Motors_Init();

	/* Send arm signal to motors */
	Motor_Arm(MOTOR_ONE);
	Motor_Arm(MOTOR_TWO);

	/* Send signal to motors, choosing wave up time in microseconds */
	int us = 1000;
	Motor_Write_us(MOTOR_ONE, us);
	/* alternatively you can set the PWM duty in percentage */
	float perc = 50; // 50% duty
	Motor_Write_PWM(MOTOR_TWO, perc);
}
