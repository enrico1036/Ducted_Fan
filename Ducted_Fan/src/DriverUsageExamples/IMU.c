/*
 * IMU.c
 *
 *  Created on: 19/lug/2016
 *      Author: Enrico Gambini
 */
#include "I2C.h"
#include "Ducted_Drivers/MPU6050.h"

void main(void) {
	/* Initialize I2C with control */
	riic_ret_t iic_ret = RIIC_OK;
	iic_ret |= riic_master_init();
	while (RIIC_OK != iic_ret) {
		nop(); /* Failure to initialize here means demo can not proceed. */
	}

	/*MPU6050 Initialization*/
	MPU6050_Test_I2C();
	Setup_MPU6050();
	Calibrate_Gyros();

	float gyro_x, gyro_y, gyro_z;
	float accel_x, accel_y, accel_z;
	/* Obtain accelerometer an gyro values */
	Get_Gyro_Rates(&gyro_x, &gyro_y, &gyro_z);
	Get_Accel_Gravity_Power(&accel_x, &accel_y, &accel_z);
}

