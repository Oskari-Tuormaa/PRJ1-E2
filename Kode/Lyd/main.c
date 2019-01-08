#include <avr\interrupt.h>
#include <avr/io.h>
#include "uart_int.h"
#define SIZE_COMMAND 8


void InitInt(void);
void InitSOMO(void);

int sensorCounter = 0;

int main()
{
	InitUART0(9600, 8, 'N', 1);  //initiering af UART0
	
	InitInt();  //initiering af global interrupt
	
	
	while (1)
	{}
}

InitInt() {
	sei();
}

InitSOMO() {
	int command1[SIZE_COMMAND] = {0x7E, 0x04, 0x00, 0x00, 0x00, 0xFF, 0xFC, 0xEF}; //skru volumen op på 28
	
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < SIZE_COMMAND; j++)
		{
			SendInteger(command1[j]);
		}
	}
	
}

//En eller timer starter interrupt
ISR(USART0_RX_vect) {
	int command1[SIZE_COMMAND] = {0x7E, 0x03, 0x00, 0x00, 0x01, 0xFF, 0xFC, 0xEF};  //start første lyd
	int command2[SIZE_COMMAND] = {0x7E, 0x03, 0x00, 0x00, 0x02, 0xFF, 0xFB, 0xEF};  //start anden lyd
	int command3[SIZE_COMMAND] = {0x7E, 0x03, 0x00, 0x00, 0x02, 0xFF, 0xFB, 0xEF};  //start tredje lyd
	
	switch (sensorCounter)
	{
		case 0:
		for (int i = 0; i < SIZE_COMMAND; i++)
		{
			SendInteger(command1[i]);  //I am speed spiller i starten
		}
		break;
		case 1:  //case 1-hvor mange reflekser der nu er
		for (int i = 0; i < SIZE_COMMAND; i++)
		{
			SendInteger(command2[i]);  //Katchow! spiller når en refleks er passeret
		}
		break;
		case 8:  //eller hvad sidste refleksbrik nu er af nummer
		for (int i = 0; i < SIZE_COMMAND; i++)
		{
			SendInteger(command3[i]);  //Spiller en slutlyd når banen er færdig
		}
	}
}