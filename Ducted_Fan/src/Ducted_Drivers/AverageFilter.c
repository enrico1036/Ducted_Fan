/*
 * AverageFilter.c
 *
 *  Created on: 22/apr/2016
 *      Author: Enrico Gambini
 */
#include "AverageFilter.h"

void Init_AVG(float start_value, AVG_Filter_struct* data){
	for(int i=0; i<BUFFER_SIZE; i++) {
		data->buffer[i] = start_value;
	}
	data->index = 0;
}

float Compute_AVG(float new_sample, AVG_Filter_struct* data){
	float value = 0;
	data->buffer[data->index] = new_sample;
	for(int i=0; i<BUFFER_SIZE; i++) {
		value += data->buffer[i];
	}
	data->index = (data->index+1) % BUFFER_SIZE;
	return value / (float)BUFFER_SIZE;
}
