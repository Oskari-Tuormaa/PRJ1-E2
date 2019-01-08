/* 
* Sensor.h
*
* Created: 08/01/2019 15:32:59
* Author: oskar
*/


#ifndef __SENSOR_H__
#define __SENSOR_H__

#include <avr/io.h>

class Sensor
{
public:
	Sensor();
	void initInterrupt();
	void initTimer();
	void disableInterrupt();
	void disableTimer();
};

#endif //__SENSOR_H__
