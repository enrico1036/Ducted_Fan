#include "MPU6050.h"

#ifndef HMC5883L_H_
#define HMC5883L_H_

// Define Costants/Registers
#define HMC5883L_ADDRESS 		 	0x1E
#define HMC5883L_REG_A				0x00
#define HMC5883L_REG_B				0x01
#define HMC5883L_MODE_REG			0x02

#ifdef MPU6050_I2C_AUX_MASTER

//This registers are referred to MPU6050 (use the MPU6050_address)
#define HMC5883L_REG_A_AUX				0x49
#define HMC5883L_REG_B_AUX				0x4A
#define HMC5883L_MODE_REG_AUX			0x4B
#define HMC5883L_DO_X_MSB_REG			0x4C
#define HMC5883L_DO_X_LSB_REG			0x4D
#define HMC5883L_DO_Z_MSB_REG			0x4E
#define HMC5883L_DO_Z_LSB_REG			0x4F
#define HMC5883L_DO_Y_MSB_REG			0x50
#define HMC5883L_DO_Y_LSB_REG			0x51

#else

#define HMC5883L_DO_X_MSB_REG			0x03
#define HMC5883L_DO_X_LSB_REG			0x04
#define HMC5883L_DO_Z_MSB_REG			0x05
#define HMC5883L_DO_Z_LSB_REG			0x06
#define HMC5883L_DO_Y_MSB_REG			0x07
#define HMC5883L_DO_Y_LSB_REG			0x08
#define HMC5883L_STATUS_REG				0x09
#define HMC5883L_ID_REG_A				0x0A
#define HMC5883L_ID_REG_B				0x0B
#define HMC5883L_ID_REG_C				0x0C
#endif /*MPU6050_I2C_AUXMASTER*/

#define PI								3,141592653
#define HMC5883L_FULL_SCALE_RANGE		8 //gauss


// Define Offsets Magnetometer
static float MAG_XOUT_OFFSET = (276-300)/2;
static float MAG_YOUT_OFFSET = (150-405)/2;
static float MAG_ZOUT_OFFSET = (375-207)/2;

static float HMC5883L_MG_PER_DIGIT = 0.92f;

// Define Prototype
void Setup_HMC5883L();
void IMU_write_AUXMASTER(uint8_t CONFIG_SLV0_REG, uint8_t CONFIG_SLV0_DO);

void Get_Mag_Value(uint16_t* MAG_XOUT, uint16_t* MAG_YOUT, uint16_t* MAG_ZOUT);
void Get_Mag_Value_Normalized(float* MAG_X_NORM, float* MAG_Y_NORM, float* MAG_Z_NORM);
void Get_Mag_Heading (float* Heading);
void Get_Mag_Heading_Compensated (float* Heading, float RollAngle, float PitchAngle);
#endif /* HMC5883L_H_ */
