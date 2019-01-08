#pragma once

void InitUART0(unsigned long BaudRate, unsigned char DataBit, char Parity, unsigned char Rx_Int);
void SendInteger(int Tal);