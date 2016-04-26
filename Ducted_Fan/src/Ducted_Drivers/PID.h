/*
 * PID.h
 *
 *  Created on: 21/dic/2015
 *      Author: Enrico Gambini
 */

#ifndef SRC_DUCTED_DRIVERS_PID_H_
#define SRC_DUCTED_DRIVERS_PID_H_

typedef struct {
	float kp, kd, ki;
	float dt;
	float lastError;
	float ITerm;
	float outMax;
	float outMin;
} PID_config;

void PID_Init(PID_config* conf, float kp, float kd, float ki, float dt, float outMin, float outMax);
float PID_Compute(float input, float setPoint, PID_config* conf);

#endif /* SRC_DUCTED_DRIVERS_PID_H_ */
