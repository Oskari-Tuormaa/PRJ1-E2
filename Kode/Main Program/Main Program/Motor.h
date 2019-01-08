/*
 * Motor.h
 *
 * Created: 07/12/2018 22:41:10
 *  Author: oskar
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_

class Motor
{
public:
	Motor();
	Motor(char timerIndex, char OCRIndex,
		char switchPort, char switchPortPin, float acc);
	void tick();
	void newSpeed(int);
	void setSwitch(char);
	void stopTimer();
	void startTimer();
	void lerpPWM();
	
	float getAcc();
	void setAcc(float);
	float getPWM();
	void setPWM(int);
	void setTimerIndex(char, char);
	void setSwitchPort(char, char);
	char getSwitchPort();
private:
	float acc_;
	int desPWM_;
	float currPWM_;
	char timerIndex_;
	char OCRIndex_;
	char switchPort_;
	char switchPortPin_;
};


#endif /* MOTOR_H_ */