#include "Lyd.h"

Lyd::Lyd()
{}

void Lyd::InitUART0(unsigned long BaudRate, unsigned char DataBit, char Parity, unsigned char Rx_Int)
{
	if ((BaudRate >= 300) && (BaudRate <= 115200) && (DataBit >= 5) && (DataBit <= 8)) {
		UCSR0A = 0b00100000;  //Der må skrives til UDR
		UCSR0B = 0b00011000;  //Enabler sender og modtager
		UCSR0C = 0b00000000;  //Default async mode, no parity, 1 stopbit, 5 databits
		
		UBRR0 = (XTAL + (8 * BaudRate)) / (16 * BaudRate) - 1; // sætter baudrate
		
		//Sætter databit
		if (DataBit == 8) {
			UCSR0C |= 0b00000110;
		}
		else if (DataBit == 7) {
			UCSR0C |= 0b00000100;
		}
		else if (DataBit == 6) {
			UCSR0C |= 0b00000010;
		}
		else if (DataBit == 5) {
			UCSR0C |= 0b00000000;
		}
		
		//sætter paritet
		if (Parity == 'E') {
			UCSR0C |= 0b00100000;
			} else if (Parity == 'O') {
			UCSR0C |= 0b00110000;
			} else {
			UCSR0C |= 0b00000000;
		}
		
		//enabler/disabler RX(modtager) interrupt
		if (Rx_Int == 0) {
			UCSR0B |= 0b00000000;
			} else if (Rx_Int != 0) {
			UCSR0B |= 0b10000000;
		}
	}
}

void Lyd::SendInteger(int Tal)
{
	while((UCSR0A & 0b00100000) != 0b00100000)  //Venter på at UDR er klar til at modtage ny del af command
	{}
	
	UDR0 = Tal; //Send command til SOMO II
}

void Lyd::InitSOMO()
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

void Lyd::playSound(int lydNr)
{
	int command1[SIZE_COMMAND] = {0x7E, 0x03, 0x00, 0x00, 0x01, 0xFF, 0xFC, 0xEF};  //start første lyd
	int command2[SIZE_COMMAND] = {0x7E, 0x03, 0x00, 0x00, 0x02, 0xFF, 0xFB, 0xEF};  //start anden lyd
	int command3[SIZE_COMMAND] = {0x7E, 0x03, 0x00, 0x00, 0x03, 0xFF, 0xFB, 0xEF};  //start tredje lyd
	
	switch (sensorCounter)
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
	}
}