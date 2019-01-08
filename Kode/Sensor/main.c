/*
 * Sensor.c
 *
 * Created: 12/14/2018 11:29:27 AM
 * Author : frede
 */ 
#define F_CPU 16000000
#include <avr/io.h>
#include "Sensor.h"

volatile unsigned int checkpoint=0;


ISR(INT0_vect)
{
	++checkpoint;
	disableInterrupt();
	innitTimer3();
	switch (checkpoint)
	{
		case 0:
		{
			PORTB=0b10000000;
			break;
		}
		case 2:
		{
			PORTB=0b00010000;
			break;
		}
		case 4:
		{
			PORTB=0b00001000;
			break;
		}
		case 6:
		{
			PORTB=0b00000100;
			break;
		}
		case 8:
		{
			PORTB=0b00000010;
			break;
		}
		case 10:
		{
			PORTB=0b00000001;
			break;
		}
	}
}

ISR(TIMER3_COMPA_vect)
{
	innitInterrupt0();
	disableTimer3();
}


int main(void)
{
	sei();
	DDRD=0b00000000;
	DDRB=0b11111111;
	innitInterrupt0();
    while (1) 
    {
	}
}

