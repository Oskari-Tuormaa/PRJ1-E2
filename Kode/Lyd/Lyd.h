#ifndef LYD_H_
#define LYD_H_

const int SIZE_COMMAND = 8

using namespace std;

class Lyd
{
public:
	Lyd();
	void InitUART0(unsigned long BaudRate, unsigned char DataBit, char Parity, unsigned char Rx_Int);
	void SendInteger(int Tal);
	void InitSOMO();
	void playSound(int lydNr);
};

#endif /* LYD_H_ */