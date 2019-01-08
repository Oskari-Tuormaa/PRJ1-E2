#include <avr/io.h>
#include <avr\interrupt.h>

void initInt(void);
void initPWM(void);
void initTimer1(void);

int main(void)
{
	initInt();
	initPWM();
	initTimer1();
	
	while(1) 
	{}
}

initInt() {
	sei();
}

//Initierer timer 3 til PWM phase correct 10-bit (TOP = 1023)
initPWM() {
	DDRE = 0xFF;  //Port E er udgang (OCR3A ligger på PE3)
	PORTE = 0x00;
	
	TCCR3A = 0b10000011;
	TCCR3B = 0b00000011;
	OCR3A = 205;  //default svagt baglys (20% duty-cycle)
}

//En eller anden timer interrupt
ISR (TIMER1_COMPA_vect) {
	//if(bremser) {
		//OCR3A = 1023;  //ved nedbremsning 100% duty-cycle
	//} else {
		//OCR3A = 205;  //ellers tilbage til default
	//}
	
	if (OCR3A != 1023) {
		OCR3A = 1023;
	} else {
		OCR3A = 205;
	}
	
}

void initTimer1()
{
	// Timer1: CTC mode (mode=4), no waveforms, PS = 256
	TCCR1A = 0b00000000;
	TCCR1B = 0b00001100;
	// Match frekvens = 1Hz
	OCR1A = 62500;
	// Enable Timer1 Compare Match interrupt (A-system)
	TIMSK1 |= 0b00000010;
}