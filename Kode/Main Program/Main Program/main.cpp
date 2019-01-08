/*
 * Main Program.cpp
 *
 * Created: 08/01/2019 15:29:06
 * Author : oskar
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "Motor.h"
#include "Sensor.h"


Motor motor(1, 'B', 'B', 7, 10000.0);
Sensor sensor;
unsigned int checkpoint = 0;


ISR (INT0_vect)
{
	sensor.disableInterrupt();
	sensor.initTimer();
	checkpoint++;
	switch(checkpoint)
	{
		case 1: motor.newSpeed(100);
				break;
				
		case 2: motor.newSpeed(-100);
				break;
				
		default:motor.newSpeed(0);
				break;
	}
}

ISR (TIMER3_COMPA_vect)
{
	sensor.disableTimer();
	sensor.initInterrupt();
}


int main(void)
{
	sei();
	
    while (1) 
    {
		motor.tick();
    }
}

