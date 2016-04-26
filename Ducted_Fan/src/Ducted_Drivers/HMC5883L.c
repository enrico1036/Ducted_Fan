#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include "r_riic_rx600.h"
#include "r_riic_rx600_master.h"
#include "IMU_write_read.h"
#include "CMT.h"
#include "I2C.h"
#include "support_functions.h"
#include "HMC5883L.h"
#include "MPU6050.h"

uint8_t ENABLE_REG = 0x00;
uint8_t DISABLE_REG = 0x00;
uint8_t CONFIG_6A = 0x20;
uint8_t CONFIG_MST_CTR = 0x0D;
uint8_t CONFIG_SLV0_ADDR_R = 0x80 | 0x1E;
uint8_t CONFIG_SLV0_ADDR_W = 0x1E;
uint8_t CONFIG_SLV0_REG_DATA = 0x00;
uint8_t CONFIG_SLV0_CTRL_1 = 0x01;//len=1
uint8_t CONFIG_SLV0_CTRL_2 = 0x8D;//len=13
uint8_t CONFIG_SLV0_CTRL_Enable = 0x81;
uint8_t CONFIG_INT_PIN_CFG = 0x02;

uint8_t CONFIG_REG_A = 0x38; //CRA7 = 0, MA1 to MA0 = 01 (two samples averaged), DO2 to DO0 = 110 (Data Output Rate = 75 Hz), MS1 to MS0 = 00 (Measurement Mode)
uint8_t CONFIG_REG_B = 0x20;
uint8_t CONFIG_MODE_REG = 0x00;

void Get_Mag_Value(uint16_t* MAG_XOUT, uint16_t* MAG_YOUT, uint16_t* MAG_ZOUT)
{
	uint8_t MAG_XOUT_H = 0, MAG_XOUT_L = 0;
	uint8_t MAG_YOUT_H = 0, MAG_YOUT_L = 0;
	uint8_t MAG_ZOUT_H = 0, MAG_ZOUT_L = 0;

	IMU_read(CHANNEL, MPU6050_ADDRESS, HMC5883L_DO_X_MSB_REG, &MAG_XOUT_H, NUM_BYTES);
	IMU_read(CHANNEL, MPU6050_ADDRESS, HMC5883L_DO_X_LSB_REG, &MAG_XOUT_L, NUM_BYTES);
	IMU_read(CHANNEL, MPU6050_ADDRESS, HMC5883L_DO_Y_MSB_REG, &MAG_YOUT_H, NUM_BYTES);
	IMU_read(CHANNEL, MPU6050_ADDRESS, HMC5883L_DO_Y_LSB_REG, &MAG_YOUT_L, NUM_BYTES);
	IMU_read(CHANNEL, MPU6050_ADDRESS, HMC5883L_DO_Z_MSB_REG, &MAG_ZOUT_H, NUM_BYTES);
	IMU_read(CHANNEL, MPU6050_ADDRESS, HMC5883L_DO_Z_LSB_REG, &MAG_ZOUT_L, NUM_BYTES);

	*MAG_XOUT = ((MAG_XOUT_H<<8)|MAG_XOUT_L);
	*MAG_YOUT = ((MAG_YOUT_H<<8)|MAG_YOUT_L);
	*MAG_ZOUT = ((MAG_ZOUT_H<<8)|MAG_ZOUT_L);

}

void Get_Mag_Value_Normalized(float* MAG_X_NORM, float* MAG_Y_NORM, float* MAG_Z_NORM)
{
	uint16_t MAG_X_OUT;
	uint16_t MAG_Y_OUT;
	uint16_t MAG_Z_OUT;

	Get_Mag_Value(&MAG_X_OUT, &MAG_Y_OUT, &MAG_Z_OUT);

	*MAG_X_NORM = (float)C2toD(MAG_X_OUT)*HMC5883L_MG_PER_DIGIT - MAG_XOUT_OFFSET;
	*MAG_Y_NORM = (float)C2toD(MAG_Y_OUT)*HMC5883L_MG_PER_DIGIT - MAG_YOUT_OFFSET;
	*MAG_Z_NORM = (float)C2toD(MAG_Z_OUT)*HMC5883L_MG_PER_DIGIT - MAG_ZOUT_OFFSET;

}

void Get_Mag_Heading (float* Heading)
{
	float MAGX_OUT;
	float MAGY_OUT;
	float MAGZ_OUT;

	Get_Mag_Value_Normalized(&MAGX_OUT, &MAGY_OUT, &MAGZ_OUT);

	*Heading = atan2(MAGY_OUT,MAGX_OUT);
//	float declinationAngle = (4.0 + (26.0 / 60.0)) / (180 / PI);
//	*Heading += declinationAngle;
	// Correct for heading < 0deg and heading > 360deg
	if (*Heading < 0)
	{
		*Heading += 2 * PI;
	}

	if (*Heading > 2 * PI)
	{
		*Heading -= 2 * PI;
	}
	*Heading *= 180/PI;

}

void Setup_HMC5883L()
{
	//I2C_MST_EN = 1 	I2C master mode enabled (MPU6050 Register Map pag. 38)
	IMU_write(CHANNEL, MPU6050_ADDRESS, MPU6050_RA_USER_CTRL, &CONFIG_6A, NUM_BYTES);
	//Set the MPU6050 as the master I2C rate (400kHz)
	IMU_write(CHANNEL, MPU6050_ADDRESS, MPU6050_RA_I2C_MST_CTRL, &CONFIG_MST_CTR, NUM_BYTES);

	IMU_write_AUXMASTER(HMC5883L_REG_A,CONFIG_REG_A);
	IMU_write_AUXMASTER(HMC5883L_REG_B,CONFIG_REG_B);
	IMU_write_AUXMASTER(HMC5883L_MODE_REG,CONFIG_MODE_REG);

	//Set the read mode
	//Configure the address used to specify the I2C slave address of Slave 0 (magnetometer): read mode
	IMU_write(CHANNEL, MPU6050_ADDRESS, MPU6050_RA_I2C_SLV0_ADDR, &CONFIG_SLV0_ADDR_R, NUM_BYTES);
	//Data transfer starts from this register within Slave 0
	IMU_write(CHANNEL, MPU6050_ADDRESS, MPU6050_RA_I2C_SLV0_REG , &CONFIG_SLV0_REG_DATA, NUM_BYTES);
	//Enable sub equipment operation
	IMU_write(CHANNEL, MPU6050_ADDRESS, MPU6050_RA_I2C_SLV0_CTRL, &CONFIG_SLV0_CTRL_2, NUM_BYTES);
	//Enable data ready interrupt
	IMU_write(CHANNEL, MPU6050_ADDRESS, MPU6050_RA_INT_ENABLE, &ENABLE_REG, NUM_BYTES);



	//Stampo l'esito della scrittura sui registri di configurazione
	uint8_t rega,regb,regm;
	IMU_read(CHANNEL, MPU6050_ADDRESS, MPU6050_RA_EXT_SENS_DATA_00, &rega, NUM_BYTES);
	IMU_read(CHANNEL, MPU6050_ADDRESS, MPU6050_RA_EXT_SENS_DATA_01, &regb, NUM_BYTES);
	IMU_read(CHANNEL, MPU6050_ADDRESS, MPU6050_RA_EXT_SENS_DATA_02, &regm, NUM_BYTES);
	/*
	if (rega != (uint8_t)CONFIG_REG_A || regb != (uint8_t)CONFIG_REG_B || regm != (uint8_t)CONFIG_MODE_REG)
	{
		char a[20];
		sprintf(a, "%d %d %d", rega, regb, regm);
		lcd_display(LCD_LINE1, (uint8_t)a);
	}
	*/
}

void IMU_write_AUXMASTER(uint8_t CONFIG_SLV0_REG, uint8_t CONFIG_SLV0_DO)
{
	//Configure the address used to specify the I2C slave address of Slave 0 (magnetometer): write mode
    IMU_write(CHANNEL, MPU6050_ADDRESS, MPU6050_RA_I2C_SLV0_ADDR, &CONFIG_SLV0_ADDR_W, NUM_BYTES);
    //Data transfer starts from this register within Slave 0
    IMU_write(CHANNEL, MPU6050_ADDRESS, MPU6050_RA_I2C_SLV0_REG , &CONFIG_SLV0_REG, NUM_BYTES);
    //This register holds the output data written into Slave 0 when Slave 0 is set to write mode
    IMU_write(CHANNEL, MPU6050_ADDRESS, MPU6050_RA_I2C_SLV0_DO, &CONFIG_SLV0_DO, NUM_BYTES);
    //Set the data operation number
    IMU_write(CHANNEL, MPU6050_ADDRESS, MPU6050_RA_I2C_SLV0_CTRL, &CONFIG_SLV0_CTRL_1, NUM_BYTES);
    //Enable sub equipment operation
    IMU_write(CHANNEL, MPU6050_ADDRESS, MPU6050_RA_I2C_SLV0_CTRL, &CONFIG_SLV0_CTRL_Enable, NUM_BYTES);
}

void Get_Mag_Heading_Compensated (float* Heading, float RollAngle, float PitchAngle)
{
	float MAGX_OUT, MAGY_OUT, MAGZ_OUT;
	float cosRoll, sinRoll, cosPitch, sinPitch;
	float Xh, Yh;

	Get_Mag_Value_Normalized(&MAGX_OUT, &MAGY_OUT, &MAGZ_OUT);
	cosRoll = cos(RollAngle);
	sinRoll = sin(RollAngle);
	cosPitch = cos(PitchAngle);
	sinPitch = sin(PitchAngle);
	Xh = (MAGX_OUT * cosRoll) + (MAGY_OUT * sinPitch * sinRoll) - (MAGZ_OUT * cosPitch * sinRoll);
	Yh = (MAGY_OUT * cosPitch) - (MAGZ_OUT * sinPitch);


	*Heading = atan2(Yh, Xh);
//	float declinationAngle = (4.0 + (26.0 / 60.0)) / (180 / PI);
//	*Heading += declinationAngle;
	// Correct for heading < 0deg and heading > 360deg
	if (*Heading < 0)
	{
		*Heading += 2 * PI;
	}

	if (*Heading > 2 * PI)
	{
		*Heading -= 2 * PI;
	}
	*Heading *= 180/PI;

}
