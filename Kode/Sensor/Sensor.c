/*
 * Sensor.c
 *
 * Created: 12/14/2018 11:30:48 AM
 *  Author: frede
 */ 
#include "Sensor.h"


void innitInterrupt0()
{
	EICRA=0b00000011;
	EICRB=0b00000000;
	EIMSK=0b00000001;
	
}


void innitTimer3()
{
	TCCR3A=0b00000000;
	TCCR3B=0b00001101;
	TIMSK3=0b00000011;
	OCR3A=11718;
	
}



void disableInterrupt()
{
	EIMSK=0b00000000;
}



void disableTimer3()
{
	TIMSK3=0b00000000;
}