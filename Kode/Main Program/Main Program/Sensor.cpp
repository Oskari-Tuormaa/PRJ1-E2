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

void Sensor::initInterrupt0()
{
	EICRA=0b00000011;
	EICRB=0b00000000;
	EIMSK=0b00000001;
	DDRD = 0x00;
}

void Sensor::initTimer3()
{
	TCCR3A=0b00000000;
	TCCR3B=0b00001101;
	TIMSK3=0b00000011;
	TCNT3 = 0;
	OCR3A=8000;
}

void Sensor::disableInterrupt0()
{
	EIMSK=0b00000000;
}

void Sensor::disableTimer3()
{
	TCCR3B=0b00001000;
	TIMSK3=0b00000000;
}

void Sensor::enableInterrupt0()
{
	EIMSK=0b00000001;
}

void Sensor::enableTimer3()
{
	TCCR3B=0b00001101;
	TIMSK3=0b00000011;
}
