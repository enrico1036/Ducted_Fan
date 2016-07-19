/*
 * Motor.c
 *
 *  Created on: 21/nov/2015
 *      Author: Enrico Gambini
 */

#include "Motor.h"

void Motors_Init()
{
	//Set all parameter needed by MTU3 unit
	Set_MTU_U0_C3();
}

void Motors_On()
{
	//Start MTU3 count
	StartCount_MTU_U0_C3();
}

void Motor_Arm(int channel)
{
	//channel value must be 1 or 2
	if(channel < 1 || channel > 2)	return;

	Motor_Write_us(channel, MOTOR_ARM_US);
}

void Motor_Write_PWM(int channel, float value)
{
	//channel value must be 1 or 2
	if(channel < 1 || channel > 2)	return;

	//check if value is a percentage, if not in range 0-100 return
	if(value<=0 || value>=100)	return;

	uint16_t tgr_a_val, tgr_b_val, tgr_d_val;
	tgr_a_val = GetTGR_A_MTU_U0_C3();

	// calculate tgrb value from duty cycle
	switch(channel){
	case 1:
		tgr_b_val = (tgr_a_val*value)/100;
		SetTGR_B_MTU_U0_C3(tgr_b_val);
		break;
	case 2:
		tgr_d_val = (tgr_a_val*value)/100;
		SetTGR_D_MTU_U0_C3(tgr_d_val);
		break;
	}

}

void Motor_Write_us(int channel, float us)
{
	//channel value must be 1 or 2
	if(channel < 1 || channel > 2)	return;

	Motor_Write_PWM(channel, (us*100)/MOTOR_PWM_SIGNAL_PERIOD_US);
}

void Motors_Off()
{
	HaltCount_MTU_U0_C3();	//Stop MTU3 count
}
