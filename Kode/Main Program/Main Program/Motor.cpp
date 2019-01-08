/*
 * Motor.cpp
 *
 * Created: 07/12/2018 22:41:03
 *  Author: oskar
 */ 

#include <avr/io.h>
#include "Motor.h"

Motor::Motor()
{
	desPWM_ = 0x00;
	currPWM_ = 0x01;
	
	setTimerIndex(1, 'B');
	setSwitchPort('B', 7);
	
	setAcc(10000.0);
	
	stopTimer();
	setPWM(0);
}

Motor::Motor(char timerIndex, char OCRIndex, 
	char switchPort, char switchPortPin, float acc)
{
	desPWM_ = 0x00;
	currPWM_ = 0x01;
	
	setTimerIndex(timerIndex, OCRIndex);
	setSwitchPort(switchPort, switchPortPin);
	
	setAcc(acc);
	
	stopTimer();
	setPWM(0);
}

/******************************

Does acceleration calculations

******************************/
void Motor::tick()
{
	if (currPWM_ > -40 && currPWM_ < 40)
	{
		stopTimer();
	}
	else
	{
		startTimer();
		if (currPWM_ > 0)
		{
			setSwitch(0);
			setPWM(currPWM_);
		}
		else
		{
			setSwitch(1);
			setPWM(-currPWM_);
		}
	}
	
	lerpPWM();
}

/******************************
---------VALID VALUES----------

	newSpeed
		-100 -> 100

******************************/
void Motor::newSpeed(int newSpeed)
{
	if (newSpeed >= -100 && newSpeed <= 100)
		desPWM_ = 0xFF * newSpeed / 100;
}

void Motor::setSwitch(char state)
{
	if (state == 0)
		switch(switchPort_)
		{
			case 'A':PORTA &= !(1<<switchPortPin_);
			break;
			case 'B':PORTB &= !(1<<switchPortPin_);
			break;
			case 'C':PORTC &= !(1<<switchPortPin_);
			break;
			case 'D':PORTD &= !(1<<switchPortPin_);
			break;
			case 'E':PORTE &= !(1<<switchPortPin_);
			break;
			case 'F':PORTF &= !(1<<switchPortPin_);
			break;
			case 'G':PORTG &= !(1<<switchPortPin_);
			break;
			case 'H':PORTH &= !(1<<switchPortPin_);
			break;
			case 'J':PORTJ &= !(1<<switchPortPin_);
			break;
			case 'K':PORTK &= !(1<<switchPortPin_);
			break;
			case 'L':PORTL &= !(1<<switchPortPin_);
			break;
		}
	else
		switch(switchPort_)
		{
			case 'A':PORTA |= (1<<switchPortPin_);
				   	 break;
			case 'B':PORTB |= (1<<switchPortPin_);
					 break;
			case 'C':PORTC |= (1<<switchPortPin_);
					 break;
			case 'D':PORTD |= (1<<switchPortPin_);
					 break;
			case 'E':PORTE |= (1<<switchPortPin_);
					 break;
			case 'F':PORTF |= (1<<switchPortPin_);
					 break;
			case 'G':PORTG |= (1<<switchPortPin_);
					 break;
			case 'H':PORTH |= (1<<switchPortPin_);
					 break;
			case 'J':PORTJ |= (1<<switchPortPin_);
					 break;
			case 'K':PORTK |= (1<<switchPortPin_);
					 break;
			case 'L':PORTL |= (1<<switchPortPin_);
					 break;
		}
}

void Motor::stopTimer()
{
	setSwitch(0);
	switch (timerIndex_)
	{
		case 1: TCCR1B &= 0b11111010; break;
		case 3: TCCR3B &= 0b11111010; break;
		case 4: TCCR4B &= 0b11111010; break;
		case 5: TCCR5B &= 0b11111010; break;
	}
}

void Motor::startTimer()
{
	switch (timerIndex_)
	{
		case 1: TCCR1B |= 0b00000101; break;
		case 3: TCCR3B |= 0b00000101; break;
		case 4: TCCR4B |= 0b00000101; break;
		case 5: TCCR5B |= 0b00000101; break;
	}
}

void Motor::lerpPWM()
{
	int isDesPos = (int)desPWM_ & (1<<15);
	int isCurrPos = (int)currPWM_ & (1<<15);
	if (isDesPos == isCurrPos || (currPWM_ < 30 && currPWM_ > -30) || desPWM_ != 0)
	{
		currPWM_ += (desPWM_ - currPWM_) / acc_;
	}
	else
	{
		currPWM_ += -currPWM_ / (acc_ * 0.25);
	}
}

void Motor::setAcc(float newAcc)
{
	acc_ = newAcc;
}

float Motor::getAcc()
{
	return acc_;
}

float Motor::getPWM()
{
	return desPWM_;
}

void Motor::setPWM(int newPWM)
{
	switch(OCRIndex_)
	{
		case 'A':	switch(timerIndex_)
					{
						case 1:	OCR1A = newPWM; break;
						case 3:	OCR3A = newPWM; break;
						case 4:	OCR4A = newPWM; break;
						case 5:	OCR5A = newPWM; break;
					}
		break;
		case 'B':	switch(timerIndex_)
					{
						case 1:	OCR1B = newPWM; break;
						case 3:	OCR3B = newPWM; break;
						case 4:	OCR4B = newPWM; break;
						case 5:	OCR5B = newPWM; break;
					}
		break;
		case 'C':	switch(timerIndex_)
					{
						case 1:	OCR1C = newPWM; break;
						case 3:	OCR3C = newPWM; break;
						case 4:	OCR4C = newPWM; break;
						case 5:	OCR5C = newPWM; break;
		}
		break;
	}
}

/******************************
---------VALID VALUES----------

	timerIndex
		1, 3, 4, 5

	OCRIndex
		'A', 'B', 'C'

******************************/
void Motor::setTimerIndex(char timerIndex, char OCRIndex)
{
	timerIndex_ = timerIndex;
	OCRIndex_ = OCRIndex;
	
	switch(OCRIndex)
	{
		default:	OCRIndex_ = 'A';
		case 'A':	switch(timerIndex_)
					{
						default:timerIndex_ = 1;
						case 1: TCCR1A |= 0b10000001;
								TCCR1B |= 0b00001101;
								DDRB |= (1<<5);
								break;
						case 3: TCCR3A |= 0b10000001;
								TCCR3B |= 0b00001101;
								DDRE |= (1<<3);
								break;
						case 4:	TCCR4A |= 0b10000001;
								TCCR4B |= 0b00001101;
								DDRH = (1<<3);
								break;
						case 5:	TCCR5A |= 0b10000001;
								TCCR5B |= 0b00001101;
								DDRL = (1<<3);
								break;
					}
					break;
		case 'B':	switch(timerIndex_)
					{
						default:timerIndex_ = 1;
						case 1: TCCR1A |= 0b00100001;
								TCCR1B |= 0b00001101;
								DDRB |= (1<<6);
								break;
						case 3: TCCR3A |= 0b00100001;
								TCCR3B |= 0b00001101;
								DDRE |= (1<<4);
								break;
						case 4:	TCCR4A |= 0b00100001;
								TCCR4B |= 0b00001101;
								DDRH |= (1<<4);
								break;
						case 5:	TCCR5A |= 0b00100001;
								TCCR5B |= 0b00001101;
								DDRL |= (1<<4);
								break;
					}
					break;
		case 'C':	switch(timerIndex_)
					{
						default:timerIndex_ = 1;
						case 1: TCCR1A |= 0b00001001;
								TCCR1B |= 0b00001101;
								DDRB |= (1<<7);
								break;
						case 3: TCCR3A |= 0b00001001;
								TCCR3B |= 0b00001101;
								DDRE = (1<<5);
								break;
						case 4:	TCCR4A |= 0b00001001;
								TCCR4B |= 0b00001101;
								DDRH |= (1<<5);
								break;
						case 5:	TCCR5A |= 0b00001001;
								TCCR5B |= 0b00001101;
								DDRL |= (1<<5);
								break;
					}
					break;
	}
}

/******************************
---------VALID VALUES----------

	switchPort
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'J', 'K', 'L'
		
	switchPortPin
		0 -> 7

******************************/
void Motor::setSwitchPort(char switchPort, char switchPortPin)
{
	switchPort_ = switchPort;
	switchPortPin_ = switchPortPin;
	
	if (switchPortPin < 0 || switchPortPin > 7 ||
		(switchPort == 'G' && switchPortPin > 5))
		switchPortPin_ = 0;
	
	switch(switchPort)
	{
		default: switchPort = 'A';
		case 'A':DDRA |= (1<<switchPortPin_);
				 break;
		case 'B':DDRB |= (1<<switchPortPin_);
				 break;
		case 'C':DDRC |= (1<<switchPortPin_);
				 break;
		case 'D':DDRD |= (1<<switchPortPin_);
				 break;
		case 'E':DDRE |= (1<<switchPortPin_);
				 break;
		case 'F':DDRF |= (1<<switchPortPin_);
				 break;
		case 'G':DDRG |= (1<<switchPortPin_);
				 break;
		case 'H':DDRH |= (1<<switchPortPin_);
				 break;
		case 'J':DDRJ |= (1<<switchPortPin_);
				 break;
		case 'K':DDRK |= (1<<switchPortPin_);
				 break;
		case 'L':DDRL |= (1<<switchPortPin_);
				 break;
	}
}

char Motor::getSwitchPort()
{
	return switchPort_;
}
