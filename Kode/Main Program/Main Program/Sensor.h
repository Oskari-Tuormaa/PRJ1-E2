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
	void initInterrupt0();
	void initTimer3();
	void disableInterrupt0();
	void disableTimer3();
	void enableInterrupt0();
	void enableTimer3();
};

#endif //__SENSOR_H__
