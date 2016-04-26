/*
 * AHRS.h
 *
 *  Created on: 29/feb/2016
 *      Author: pc asus
 */

#ifndef SRC_DUCTED_DRIVERS_AHRS_H_
#define SRC_DUCTED_DRIVERS_AHRS_H_

#define sampleFreq 		20.0f		// sample frequency in Hz
#define betaDef			0.1f		// 2 * proportional gain
#define PI 				3,141592653 // Pi Constant

// Quaternion of sensor frame relative to auxiliary frame
static float q0 = 1.0f;
static float q1 = 0.0f;
static float q2 = 0.0f;
static float q3 = 0.0f;

float invSqrt(float x);
void MadgwickAHRSupdateIMU(float gx, float gy, float gz, float ax, float ay, float az);
void MadgwickAHRSupdate(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz);
void get_Angle_AHRS (float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz, float* Roll, float* Pitch, float* Jaw);

#endif /* SRC_DUCTED_DRIVERS_AHRS_H_ */
