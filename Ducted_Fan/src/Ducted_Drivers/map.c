/*
 * map.c
 *
 *  Created on: 24/nov/2015
 *      Author: Enrico Gambini
 */
#include "map.h"

inline float map(float val, float from_src, float to_src, float from_dst, float to_dst)
{
	return (((to_dst-from_dst)/(to_src-from_src))*(val-from_src)) + from_dst;
}
