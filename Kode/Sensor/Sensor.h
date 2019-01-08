/*
 * Sensor.h
 *
 * Created: 12/14/2018 11:29:55 AM
 *  Author: frede
 */ 


#ifndef SENSOR_H_
#define SENSOR_H_
#include <avr/interrupt.h>

void initInterrupt0();
void initTimer3();
void disableInterrupt();
void disableTimer3();
	

#endif /* SENSOR_H_ */
