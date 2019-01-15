#include "Lys.h"

Lys::Lys() 
{}
	
void Lys::initPWM()
{
	//Initierer timer 1 til PWM phase correct 10-bit (TOP = 1023)
	DDRH |= 1<<3;  //Port E er udgang (OCR3A ligger på PB5)
	PORTH &= ~(1<<3);
	
	TCCR4A = 0b10000011;
	TCCR4B = 0b00000011;
	OCR4B = 205;  //default svagt baglys (20% duty-cycle)
}

void Lys::lysStyrke(int styrke)
{
	switch(styrke)
	{
		default:
		case 0: OCR4B = 0;
				break;
		
		case 1: OCR4B = 205;
				break;
		
		case 2: OCR4B = 1023;
				break;
	}
}