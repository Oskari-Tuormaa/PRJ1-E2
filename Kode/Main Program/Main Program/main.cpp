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
#include "Sound.h"


Motor motor(4, 'C', 'H', 6, 700.0);
Sound sound;
Sensor sensor;
Light light;
unsigned int checkpoint = 0;


ISR (INT0_vect)
{
	sensor.disableInterrupt0();
	sensor.enableTimer3();
	
	checkpoint++;
	switch(checkpoint)
	{
		case 11:
		case 7:
		case 9: 
		case 10: break;
		default:sound.playSound(1);
	}
	
	PORTB = checkpoint;
	switch(checkpoint + 1)
	{
		case 2: 
		case 3: motor.setAcc(700.0);
				motor.newSpeed(100);
		break;
		
		case 4: motor.setAcc(5000.0);
				motor.newSpeed(20); // På bakken
		break;
		
		case 5:
		case 6: motor.setAcc(10000.0);
				motor.newSpeed(100);
		break;
		
		case 7: // Bak tilbage
		case 8: motor.setAcc(700.0);
				motor.newSpeed(-100);
		break;
		
		case 9: // Kør fremad
		case 10:
		case 11: motor.newSpeed(100);
		break;
		
		case 12: motor.setAcc(5000.0);
				 motor.newSpeed(0);
				 sound.playSound(2);
				 break;
		
		default:motor.newSpeed(0);
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
	
	sound.InitUART0(9600, 8, 'N', 0);
	sound.InitSOMO();
	
	DDRA = 0x00;
	while ((~PINA & 0b00000001) == 0)
	{}
	
	sound.playSound(0);
	
	_delay_ms(3000);
	motor.newSpeed(100);
	
	DDRB = 0xFF;
	
    while (1) 
    {
		motor.tick();
    }
}

