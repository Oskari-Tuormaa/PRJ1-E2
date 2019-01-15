/* 
* Sound.h
*
* Created: 14-01-2019 09:50:43
* Author: oskar
*/


#include <avr/io.h>
#define XTAL 16000000
#define SIZE_COMMAND 8

#ifndef __SOUND_H__
#define __SOUND_H__


class Sound
{
public:
	Sound();
	void InitUART0(unsigned long BaudRate, unsigned char DataBit, char Parity, unsigned char Rx_Int);
	void SendInteger(int tal);
	void InitSOMO();
	void playSound(char lydNr);
}; //Sound

#endif //__SOUND_H__
