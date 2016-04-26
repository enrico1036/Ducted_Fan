/*
 * AHRS_Mahony.h
 *
 *  Created on: 23/mar/2016
 *      Author: Chiara
 */

#ifndef SRC_DUCTED_DRIVERS_AHRS_MAHONY_H_
#define SRC_DUCTED_DRIVERS_AHRS_MAHONY_H_

//----------------------------------------------------------------------------------------------------
// Variable declaration

#define PI 						3,141592653

#define sampleFreq	50.0f			// sample frequency in Hz
#define twoKpDef	(2.0f * 0.5f)	// 2 * proportional gain
#define twoKiDef	(2.0f * 0.0f)	// 2 * integral gain

extern volatile float twoKp;			// 2 * proportional gain (Kp)
extern volatile float twoKi;			// 2 * integral gain (Ki)

// quaternion of sensor frame relative to auxiliary frame
extern volatile float q0 = 1.0f;
extern volatile float q1 = 0.0f;
extern volatile float q2 = 0.0f;
extern volatile float q3 = 0.0f;


float inversSqrt(float x);
void MahonyAHRSupdate(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz);
void MahonyAHRSupdateIMU(float gx, float gy, float gz, float ax, float ay, float az);
void get_Angle_AHRS_Mahony (float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz, float* Roll, float* Pitch, float* Jaw);

#endif /* SRC_DUCTED_DRIVERS_AHRS_MAHONY_H_ */
