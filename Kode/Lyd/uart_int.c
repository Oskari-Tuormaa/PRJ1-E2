#include <avr/io.h>
#include "uart_int.h"


#define XTAL 16000000  //Ekstern hardware frekvens


void InitUART0(unsigned long BaudRate, unsigned char DataBit, char Parity, unsigned char Rx_Int)
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

void SendInteger(int Tal)
{ 
   while((UCSR0A & 0b00100000) != 0b00100000)  //Venter på at UDR er klar til at modtage ny del af command
   {}
   
   UDR0 = Tal; //Send command til SOMO II
}