/*******************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only 
* intended for use with Renesas products. No other uses are authorized. This 
* software is owned by Renesas Electronics Corporation and is protected under
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE 
* AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS 
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE 
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software
* and to discontinue the availability of this software. By using this software,
* you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer *
* Copyright (C) 2012 Renesas Electronics Corporation. All rights reserved.    
*******************************************************************************/
/*******************************************************************************
* File Name     : adc_oneshot_demo_main.c
* Version       : 1.1
* Device(s)     : RX63N
* Tool-Chain    : Renesas RX Standard Toolchain 1.2.0
* OS            : None
* H/W Platform  : YRDKRX63N
* Description   : This sample demonstrates use of the 12-bit A/D converter (S12ADC).
*                 The S12ADC is set up for one-shot reading of channel AN002.
*                 AN002 is connected to the potentiometer VR1 on the YRDKRX63N board.  
*                 Each time SW1 is pressed the S12ADC is started and the ADC reading
*                 is recorded and displayed on the LCD.
* Operation     : 1. Build the sample code (CTRL+B) and connect to the YRDK.
*
* 						Select the Project by clicking on it in
* 						the Project Explorer panel.
*
* 						Run > Debug As > Renesas GDB Hardware Launch
*
*                 2. Click 'Restart' to start the software.
*         
*                 3. The debug LCD will show the name of the sample along with
*                    instructions directing you to adjust pot VR1 and then 
*                    press SW1.
*
*                 4. The current ADC value, in decimal format, and the voltage that
*                    represents are displayed.
*                      
*******************************************************************************/         
/*******************************************************************************
* History : DD.MM.YYYY     Version     Description
*         : 15.02.2012     1.00        First release
*         : 31.05.2013     1.10        Updated For e2studio DH
*******************************************************************************/

/*******************************************************************************
Includes   <System Includes> , "Project Includes"
*******************************************************************************/
#include <stdint.h>
#include <stdio.h>
#include <machine.h>
#include "platform.h"
#include "s12adc.h"
#include "Ducted_Drivers/Motor.h"
#include "Ducted_Drivers/Servo.h"
#include "Ducted_Drivers/map.h"
#include "Ducted_Drivers/PID.h"
#include "Ducted_Drivers/Sonar.h"
#include "LowLevelDrivers/CMT.h"
#include "I2C.h"
#include "Ducted_Drivers/lcd_buffer.h"
#include "Ducted_Drivers/Kalman.h"
#include "Ducted_Drivers/MPU6050.h"
#include "Ducted_Drivers/HMC5883L.h"
#include "Ducted_Drivers/AHRS.h"
#include "Ducted_Drivers/WatchDogTimer.h"
#include "Ducted_Drivers/AverageFilter.h"

/*******************************************************************************
 Prototypes for local functions
 *******************************************************************************/
void Setup();
void Callback_1ms();
void Callback_5ms();
void Callback_10ms();
void Callback_20ms();
void Callback_50ms();
void Callback_100ms();
void Callback_500ms();
void Callback_1000ms();
void Fallback();
void Sonar_Fallback();

/*******************************************************************************
 Global variables
 *******************************************************************************/
struct axis {
	float x;
	float y;
	float z;
};
struct dynamic {
	struct axis acc;
	struct axis vel;
	struct axis pos;
};

struct physicalState {
	struct dynamic accel;
	struct dynamic gyro;
	struct dynamic magn;
	struct dynamic abs;
	struct dynamic Kalman;
	float avg_motor_us;
	float motor_diff_us;
	float x_servo_deg;
	float y_servo_deg;
};
union {
	struct physicalState key;
	float index[sizeof(struct physicalState)];
} desiredState;

union {
	struct physicalState key;
	float index[sizeof(struct physicalState)];
} currentState;

/* puntatori alle strutture di filtraggio di Kalman */
extern KALMAN *pitchKalman;
extern KALMAN *rollKalman;

extern struct timerClocks timers;

/* Create PID structure used for PID properties */
PID_config z_axis_PID;
PID_config Pitch_PID;
PID_config Roll_PID;

AVG_Filter_struct pitchAVG;
AVG_Filter_struct rollAVG;

float outValue;

/*Stores the value read from analog input  */
uint16_t analogRead;

float altitudeValue;

float dt = 0.05;

WDT_struct sonarWDT;
WDT_struct mainWDT;


/*******************************************************************************
 * Function name: main
 * Description  : Main program function. Initializes the peripherals used in the
 *                demo and executes a loop that reads the ADC and updates the
 *                display once for each press of switch 1.
 * Arguments    : none
 * Return value : none
 *******************************************************************************/
void main(void) {
	/* One time initialize instructions */
	Setup();

	/* Endless loop*/
	while (1) {
		if (timers.timer_1mS) {
			timers.timer_1mS = 0;
			Callback_1ms();					//Operations to do every 1ms
			if (timers.timer_5mS) {
				timers.timer_5mS = 0;
				Callback_5ms();				// Operations to do every 5ms
				if (timers.timer_10mS) {
					timers.timer_10mS = 0;
					Callback_10ms();		// Operations to do every 10ms
					if (timers.timer_20mS) {
						timers.timer_20mS = 0;
						Callback_20ms();	// Operations to do every 20ms
					}
					if (timers.timer_50mS) {
						timers.timer_50mS = 0;
						Callback_50ms();
						if (timers.timer_100mS) {
							timers.timer_100mS = 0;
							Callback_100ms();
							if (timers.timer_500mS) {
								timers.timer_500mS = 0;
								Callback_500ms();
								if (timers.timer_1000mS) {
									timers.timer_1000mS = 0;
									Callback_1000ms();
								}
							}
						}

					}
				}
			}
		}
		WDT_Reset(&mainWDT);

//		//result = map(analogRead, 0, 4095, 1000, 2200);
//		Motor_Write_us(MOTOR_UPPER, desiredState.key.avg_motor_us + desiredState.key.motor_diff_us);
//		Motor_Write_us(MOTOR_BOTTOM, desiredState.key.avg_motor_us - desiredState.key.motor_diff_us);
//
//		//result = map(analogRead, 0, 4095, 60, 120);
//		Servo_Write_deg(1, desiredState.key.x_servo_deg + 18); //18° is the trim of the servo
//		Servo_Write_deg(2, desiredState.key.y_servo_deg);
	}
	Fallback();

} /* End function main() */

void Setup() {
	/* Initialize LCD */
	lcd_initialize();

	/* Clear LCD */
	lcd_clear();

	/* Display message on LCD */

	lcd_buffer_print(LCD_LINE2, "    TEST   ");

	/* Initialize motors */
	Motors_Init();
	/* Turn on motors relay */
	Motors_On();
	/* Send arm signal to motors */
	Motor_Arm(MOTOR_UPPER);
	Motor_Arm(MOTOR_BOTTOM);

	/* Initialize servos */
	Servos_Init();

	/* Initialize sonar */
	sonarInitialize(); //must be initialized before IIC, otherwise it will not work
	/* Setup the 12-bit A/D converter */
	S12ADC_init();


	/* Initialize I2C with control */
	riic_ret_t iic_ret = RIIC_OK;
	iic_ret |= riic_master_init();
	while (RIIC_OK != iic_ret) {
		nop(); /* Failure to initialize here means demo can not proceed. */
	}


	/* Setup Compare Match Timer */
	CMT_init();

	/* Initialize PID structure used for PID properties */
	PID_Init(&z_axis_PID, 0.7, 0.05, 0.30, dt, 0, 0.5);	//0.7 0.05 0.15
	PID_Init(&Pitch_PID, 1, 0, 0.01, dt, -30, 30);
	PID_Init(&Roll_PID, 1, 0, 0.01, dt, -30, 30);

	Init_AVG(0, &pitchAVG);
	Init_AVG(0, &rollAVG);

	/* Make the port connected to SW1 an input */
	PORT4.PDR.BIT.B0 = 0;

	/*MPU6050 Initialization*/
	MPU6050_Test_I2C();
	Setup_MPU6050();
	Calibrate_Gyros();
//	Calibrate_Accel();

	/*Kalman Initialization*/
	init_Kalman();

	//MS5611-01BA01 init
//    MS5611_Init();

	desiredState.key.motor_diff_us = 0;
	desiredState.key.abs.pos.z = 0.20;
	altitudeValue = 200;
	mainWDT = WDT_Init(500, Fallback);
	WDT_Start(&mainWDT);
	sonarWDT = WDT_Init(60, Sonar_Fallback);
	WDT_Start(&sonarWDT);
}
void Callback_1ms() {
	/* Start the A/D converter */
	S12ADC_start();

	/*!!Safe check: stop timer count if sonar doesn't answer anymore */
	if (sonarGetState() == SONAR_ECHO){
		WDT_Increase(&sonarWDT);
	}

	/* Wait for the conversion to complete */
	while (false == S12ADC_conversion_complete()) {
	}
	/* Fetch the results from the ADC */
	analogRead = S12ADC_read();

}
void Callback_5ms() {
	if (sonarGetState() == SONAR_TRIGGER) {
			sonarTriggerStop();
			sonarEchoCountStart();
			WDT_Reset(&sonarWDT);
		}

}

static double sonarDistance = 0;
void Callback_10ms() {
	sonarDistance = sonarGetDistance();
}


void Callback_20ms() {
	desiredState.key.abs.pos.z = altitudeValue / 1000.0;

	/* Setting motor speed based on altitude */
	lcd_buffer_print(LCD_LINE4, "In: %1.3f", sonarDistance);
	outValue = PID_Compute(sonarDistance, desiredState.key.abs.pos.z, &z_axis_PID);
	desiredState.key.avg_motor_us = map(outValue * map(analogRead, 0, 4096, 0, 1), 0, 0.5, MOTOR_MIN_US, MOTOR_MAX_US);
	lcd_buffer_print(LCD_LINE5, "Mot: %4.0f", desiredState.key.avg_motor_us);
	//lcd_buffer_print(LCD_LINE7, "Diff: %3.0f", desiredState.key.motor_diff_us);

	/* Obtain accelerometer an gyro values */
	Get_Gyro_Rates(&currentState.key.gyro.vel.x, &currentState.key.gyro.vel.y, &currentState.key.gyro.vel.z);
	Get_Accel_Angles(&currentState.key.accel.pos.x, &currentState.key.accel.pos.y);
	//Get_Mag_Value_Normalized(&currentState.key.magn.pos.x, &currentState.key.magn.pos.y, &currentState.key.magn.pos.z);

	Get_Accel_Gravity_Power(&currentState.key.accel.vel.x, &currentState.key.accel.vel.y, &currentState.key.accel.vel.z);
	get_Angle_AHRS(currentState.key.gyro.vel.x, currentState.key.gyro.vel.y, currentState.key.gyro.vel.z, currentState.key.accel.vel.x, currentState.key.accel.vel.y, currentState.key.accel.vel.z, currentState.key.magn.pos.x, currentState.key.magn.pos.y, currentState.key.magn.pos.z, &currentState.key.Kalman.acc.x, &currentState.key.Kalman.acc.y, &currentState.key.Kalman.acc.z);
	// get_Angle_AHRS_Mahony(currentState.key.gyro.vel.x, currentState.key.gyro.vel.y, currentState.key.gyro.vel.z, currentState.key.accel.vel.x, currentState.key.accel.vel.y, currentState.key.accel.vel.z, currentState.key.magn.pos.x, currentState.key.magn.pos.y, currentState.key.magn.pos.z, &currentState.key.Kalman.vel.x, &currentState.key.Kalman.vel.y, &currentState.key.Kalman.vel.z);

	/* Calcolo Roll e Pitch con il filtro di Kalman */
	 currentState.key.Kalman.pos.x = Compute_AVG(getAngle(currentState.key.accel.pos.x, currentState.key.gyro.vel.x, dt, rollKalman), &rollAVG);
	 currentState.key.Kalman.pos.y = Compute_AVG(getAngle(currentState.key.accel.pos.y, currentState.key.gyro.vel.y, dt, pitchKalman), &pitchAVG);
	//currentState.key.Kalman.pos.z = currentState.key.Kalman.acc.z;

	// Angolo di Yaw mediante giroscopio
	// currentState.key.Kalman.pos.z = currentState.key.gyro.vel.z;

	// Get_Mag_Heading_Compensated (&currentState.key.Kalman.pos.z, currentState.key.Kalman.pos.x, currentState.key.Kalman.pos.y);
	// Get_Mag_Heading(&currentState.key.Kalman.acc.z);


	 desiredState.key.x_servo_deg = map(PID_Compute(-currentState.key.Kalman.pos.x, 0, &Roll_PID), -30, 30, 60, 120);
	 desiredState.key.y_servo_deg = map(PID_Compute(-currentState.key.Kalman.pos.y, 0, &Pitch_PID), -30, 30, 60, 120);

	 currentState.key.Kalman.pos.z += currentState.key.gyro.vel.z*dt;


	Motor_Write_us(MOTOR_UPPER, desiredState.key.avg_motor_us + desiredState.key.motor_diff_us);
	Motor_Write_us(MOTOR_BOTTOM, desiredState.key.avg_motor_us - desiredState.key.motor_diff_us);

	Servo_Write_deg(SERVO_ROLL, desiredState.key.x_servo_deg);
	Servo_Write_deg(SERVO_PITCH, desiredState.key.y_servo_deg); // pitch servo is trimmed 18°
}

void Callback_50ms() {
	if (sonarGetState() == SONAR_IDLE)
		sonarTriggerStart();
}

void Callback_100ms() {
}

void Callback_500ms() {
}

void Callback_1000ms() {
	lcd_buffer_flush();
}

void Fallback() {
	lcd_display(LCD_LINE2, "  Fallback  ");
	lcd_display(LCD_LINE3, " condition! ");
	/* Turno off motors */
	Motor_Write_us(MOTOR_UPPER, 0);
	Motor_Write_us(MOTOR_BOTTOM, 0);
	Motors_Off();
	/* Turn off servos */
	Servo_Write_deg(SERVO_PITCH, (SERVO_MAX_BOUND_DEG+SERVO_MIN_BOUND_DEG)/2);
	Servo_Write_deg(SERVO_ROLL, (SERVO_MAX_BOUND_DEG+SERVO_MIN_BOUND_DEG)/2);
	Servos_Off();
}

void Sonar_Fallback() {
	sonarEchoCountStop();
	Fallback();	//TODO: remove this call when barometer will be used
}
