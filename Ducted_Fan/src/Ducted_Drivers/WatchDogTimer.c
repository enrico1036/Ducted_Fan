/*
 * WatchDogTimer.c
 *
 *  Created on: 19/apr/2016
 *      Author: Enrico Gambini
 */

#include "WatchDogTimer.h"
#include "Motor.h"
#include "Servo.h"
#include "platform.h"

WDT_struct WDT_Init(int max_ms, callback_function failsafe) {
	WDT_struct data;
	data.current_value = 0;
	data.enabled = 0;
	data.failsafe = failsafe;
	data.max_ms = max_ms;
	return data;
}

void WDT_Increase(WDT_struct* data) {
	if (data->enabled && ++data->current_value > data->max_ms) {
		data->failsafe();
	}
}

void WDT_Reset(WDT_struct* data) {
	data->current_value = 0;
}

void WDT_Start(WDT_struct* data) {
	data->enabled = 1;
}
