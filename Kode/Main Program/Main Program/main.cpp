/*
 * Main Program.cpp
 *
 * Created: 08/01/2019 15:29:06
 * Author : oskar
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util\delay.h>
#include "Motor.h"
#include "Sensor.h"


Motor motor(4, 'C', 'H', 6, 700.0);
Sensor sensor;
unsigned int checkpoint = 0;


ISR (INT0_vect)
{
	sensor.disableInterrupt0();
	sensor.enableTimer3();
	checkpoint++;
	PORTB &= 0b00000000;
	switch(checkpoint)
	{		
		case 1: motor.newSpeed(70);
		PORTB |= 1;
		break;
		
		case 2: motor.newSpeed(70);
		PORTB |= 2;
		break;
		
		case 3: motor.newSpeed(100);
		PORTB |= 3;
		break;
		
		case 4: motor.newSpeed(20);// På bakken
		PORTB |= 4;
		break;
		
		case 5: motor.newSpeed(100);
		PORTB |= 5;
		break;
		
		case 6: motor.newSpeed(100);
		PORTB |= 6;
		break;
		
		case 7: motor.newSpeed(-100);
		PORTB |= 7;
		break;
		
		case 8: motor.newSpeed(-100);
		PORTB |= 7;
		break;
		
		case 9: motor.newSpeed(100);
		PORTB |= 8;
		break;
		
		case 10: motor.newSpeed(100);
		PORTB |= 8;
		break;
		
		case 11: motor.newSpeed(100);
		PORTB |= 9;
		break;
		
		case 12: _delay_ms(500);
				motor.newSpeed(0);
				break;
		
		default:motor.newSpeed(0);
		PORTB |= 0;
		break;
	}
}

ISR (TIMER3_COMPA_vect)
{
	EIFR = 0xFF;
	sensor.disableTimer3();
	sensor.enableInterrupt0();
}


int main(void)
{
	sei();
	sensor.initInterrupt0();
	sensor.initTimer3();
	sensor.disableTimer3();
	
	DDRB = 0xFF;
	
    while (1) 
    {
		motor.tick();
    }
}

