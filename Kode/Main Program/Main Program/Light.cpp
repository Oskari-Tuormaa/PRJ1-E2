/* 
* Light.cpp
*
* Created: 14-01-2019 10:42:09
* Author: oskar
*/


#include "Light.h"

Light::Light()
{}

void Light::initPWM()
{
	//Initierer timer 1 til PWM phase correct 10-bit (TOP = 1023)
	DDRL |= 1<<3;  //Port E er udgang (OCR3A ligger på PB5)
	PORTL &= ~(1<<3);
	DDRF |= 0b00000011;
	PORTF &= 0b11111100;
	
	TCCR5A |= 0b10000011;
	TCCR5B |= 0b00000011;
	OCR5A = 205;  //default svagt baglys (20% duty-cycle)
}

void Light::lysStyrke(char styrke)
{
	switch(styrke)
	{
		default:
		case 0: OCR5A = 0;
		break;
		
		case 1: OCR5A = 205;
		break;
		
		case 2: OCR5A = 1023;
		break;
	}
}

void Light::forLys(char strength)
{
	switch(strength)
	{
		case 0:	PORTF &= 0b11111100;
				break;
			
		case 1:	PORTF |= 0b00000011;
				break;
	}
}
