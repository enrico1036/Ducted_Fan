/*
 * WatchDogTimer.h
 *
 *  Created on: 19/apr/2016
 *      Author: Enrico Gambini
 */

#ifndef SRC_DUCTED_DRIVERS_WATCHDOGTIMER_H_
#define SRC_DUCTED_DRIVERS_WATCHDOGTIMER_H_

#define WDT_MAX_MS 500

typedef void (*callback_function)();
typedef struct {
	int enabled;
	int max_ms;
	int current_value;
	callback_function failsafe;
}WDT_struct;

WDT_struct WDT_Init(int max_ms, callback_function failsafe);
void WDT_Increase(WDT_struct* data);
void WDT_Reset(WDT_struct* data);
void WDT_Start(WDT_struct* data);


#endif /* SRC_DUCTED_DRIVERS_WATCHDOGTIMER_H_ */
