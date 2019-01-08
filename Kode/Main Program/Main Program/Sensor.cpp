/* 
* Sensor.cpp
*
* Created: 08/01/2019 15:32:59
* Author: oskar
*/


#include "Sensor.h"


Sensor::Sensor()
{
}

void Sensor::initInterrupt()
{
	EICRA=0b00000011;
	EICRB=0b00000000;
	EIMSK=0b00000001;
}

void Sensor::initTimer()
{
	TCCR3A=0b00000000;
	TCCR3B=0b00001101;
	TIMSK3=0b00000011;
	OCR3A=11718;
}

void Sensor::disableInterrupt()
{
	EIMSK=0b00000000;
}

void Sensor::disableTimer()
{
	TIMSK3=0b00000000;
}