/* 
* Sound.cpp
*
* Created: 14-01-2019 09:50:43
* Author: oskar
*/


#include "Sound.h"

// default constructor
Sound::Sound()
{
}

void Sound::InitUART0(unsigned long BaudRate, unsigned char DataBit, char Parity, unsigned char Rx_Int)
{
	if ((BaudRate >= 300) && (BaudRate <= 115200) && (DataBit >= 5) && (DataBit <= 8)) {
		UCSR1A = 0b00100000;  //Der må skrives til UDR
		UCSR1B = 0b00011000;  //Enabler sender og modtager
		UCSR1C = 0b00000000;  //Default async mode, no parity, 1 stopbit, 5 databits
		
		UBRR1 = (XTAL + (8 * BaudRate)) / (16 * BaudRate) - 1; // sætter baudrate
		
		//Sætter databit
		if (DataBit == 8) {
			UCSR1C |= 0b00000110;
		}
		else if (DataBit == 7) {
			UCSR1C |= 0b00000100;
		}
		else if (DataBit == 6) {
			UCSR1C |= 0b00000010;
		}
		else if (DataBit == 5) {
			UCSR1C |= 0b00000000;
		}
		
		//sætter paritet
		if (Parity == 'E') {
			UCSR1C |= 0b00100000;
			} else if (Parity == 'O') {
			UCSR1C |= 0b00110000;
			} else {
			UCSR1C |= 0b00000000;
		}
		
		//enabler/disabler RX(modtager) interrupt
		if (Rx_Int == 0) {
			UCSR1B |= 0b00000000;
			} else if (Rx_Int != 0) {
			UCSR1B |= 0b10000000;
		}
	}
}

void Sound::SendInteger(int tal)
{
	while((UCSR1A & 0b00100000) != 0b00100000)  //Venter på at UDR er klar til at modtage ny del af command
	{}
	
	UDR1 = tal; //Send command til SOMO II
}

void Sound::InitSOMO()
{
	int command1[SIZE_COMMAND] = {0x7E, 0x04, 0x00, 0x00, 0x00, 0xFF, 0xFC, 0xEF}; //skru volumen op på 28
	
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < SIZE_COMMAND; j++)
		{
			SendInteger(command1[j]);
		}
	}
}

void Sound::playSound(char lydNr)
{
	int command1[SIZE_COMMAND] = {0x7E, 0x03, 0x00, 0x00, 0x01, 0xFF, 0xFC, 0xEF};  //start første lyd
	int command2[SIZE_COMMAND] = {0x7E, 0x03, 0x00, 0x00, 0x02, 0xFF, 0xFB, 0xEF};  //start anden lyd
	int command3[SIZE_COMMAND] = {0x7E, 0x03, 0x00, 0x00, 0x03, 0xFF, 0xFA, 0xEF};  //start tredje lyd
	
	switch (lydNr)
	{
		case 0:
		for (int i = 0; i < SIZE_COMMAND; i++)
		{
			SendInteger(command1[i]);  //I am speed spiller i starten
		}
		break;
		case 1:
		for (int i = 0; i < SIZE_COMMAND; i++)
		{
			SendInteger(command2[i]);  //Katchow! spiller når en refleks er passeret
		}
		break;
		case 2:  //eller hvad sidste refleksbrik nu er af nummer
		for (int i = 0; i < SIZE_COMMAND; i++)
		{
			SendInteger(command3[i]);  //Spiller en slutlyd når banen er færdig
		}
		break;
	}
}

