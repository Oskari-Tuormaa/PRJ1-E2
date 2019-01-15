/* 
* Light.h
*
* Created: 14-01-2019 10:42:09
* Author: oskar
*/


#ifndef __LIGHT_H__
#define __LIGHT_H__

#include <avr/io.h>

class Light
{
public:
	Light();
	void initPWM(void);
	void lysStyrke(char);
	void forLys(char);
}; //Light

#endif //__LIGHT_H__
