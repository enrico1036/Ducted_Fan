/*
 * AverageFilter.h
 *
 *  Created on: 22/apr/2016
 *      Author: Enrico Gambini
 */

#ifndef SRC_DUCTED_DRIVERS_AVERAGEFILTER_H_
#define SRC_DUCTED_DRIVERS_AVERAGEFILTER_H_

#define BUFFER_SIZE 30

typedef struct {
	float buffer[BUFFER_SIZE];
	int index;
} AVG_Filter_struct;

void Init_AVG(float start_value, AVG_Filter_struct* data);
float Compute_AVG(float new_sample, AVG_Filter_struct* data);

#endif /* SRC_DUCTED_DRIVERS_AVERAGEFILTER_H_ */
