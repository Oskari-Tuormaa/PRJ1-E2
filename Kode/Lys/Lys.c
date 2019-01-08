#include "Lys.h"

Lys::Lys() 
{}
	
void Lys::initPWM()
{
	//Initierer timer 3 til PWM phase correct 10-bit (TOP = 1023)
	DDRE = 0xFF;  //Port E er udgang (OCR3A ligger på PE3)
	PORTE = 0x00;
	
	TCCR3A = 0b10000011;
	TCCR3B = 0b00000011;
	OCR3A = 205;  //default svagt baglys (20% duty-cycle)
}