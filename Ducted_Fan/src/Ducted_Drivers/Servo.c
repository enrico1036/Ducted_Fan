/*
 * Servo.c
 *
 *  Created on: 22/nov/2015
 *      Author: Enrico Gambini
 */

#include "Servo.h"
#include <stdio.h>

void Servos_Init()
{
	//Set all parameter needed by MTU4 unit and start count
	Set_MTU_U0_C4();
	StartCount_MTU_U0_C4();
	Servo_Write_deg(SERVO_PITCH, (SERVO_MAX_BOUND_DEG+SERVO_MIN_BOUND_DEG)/2);
	Servo_Write_deg(SERVO_ROLL, (SERVO_MAX_BOUND_DEG+SERVO_MIN_BOUND_DEG)/2);
}

void Servos_Off() {
	HaltCount_MTU_U0_C4();
}

void Servo_Write_PWM(int channel, float value)
{
	//channel value must be 1 or 2
	if(channel < 1 || channel > 2)	return;

	//check if value is a percentage, if not in range 1-99 return
	if(value<=1 || value>=99)	return;

	uint16_t tgr_a_val, tgr_b_val, tgr_d_val;
	tgr_a_val = GetTGR_A_MTU_U0_C4();

	switch(channel){
	case 1:
		tgr_b_val = (tgr_a_val*value)/100.0;
		SetTGR_B_MTU_U0_C4(tgr_b_val);
		break;
	case 2:
		tgr_d_val = (tgr_a_val*value)/100.0;
		SetTGR_D_MTU_U0_C4(tgr_d_val);
		break;
	}

}

void Servo_Write_us(int channel, float us)
{
	//channel value must be 1 or 2
	if(channel < 1 || channel > 2)	return;

	Servo_Write_PWM(channel, (us*100)/SERVO_PWM_SIGNAL_PERIOD_US);
}

void Servo_Write_deg(int channel, float deg)
{
	//channel value must be 1 or 2
	if(channel < 1 || channel > 2)	return;

	if(deg < SERVO_MIN_BOUND_DEG) deg = SERVO_MIN_BOUND_DEG;
	else if(deg > SERVO_MAX_BOUND_DEG) deg = SERVO_MAX_BOUND_DEG;

	switch(channel){
	case SERVO_PITCH:
		deg += SERVO_PITCH_TRIM;
		break;
	case SERVO_ROLL:
		deg += SERVO_ROLL_TRIM;
		break;
	}

	Servo_Write_us(channel, map(deg, SERVO_MIN_DEG, SERVO_MAX_DEG, SERVO_MIN_US, SERVO_MAX_US));
}



