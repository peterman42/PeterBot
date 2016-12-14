#ifndef WHEEL_H
#define WHEEL_H

#include "robot_commons.h"

#ifdef ARDUINO_UNO
#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif
#ifndef Arduino_h
#include <Arduino.h>
#endif
#else
#include <wiringPi.h>
#endif
#include "component.h"

class Wheel: public Component
{
public:
	int directionA;
	int directionB;
	Wheel()
	{};	
	Wheel(int pin)
		: Component(3)
	{};
	Wheel(int PWM_pin, int directionA_pin, int directionB_pin) 
		: Component(3)
	{
		//addPin(PWM_pin);
		//addPin(directionA_pin);
		//addPin(directionB_pin);

		Wheel::setPin(PWM_pin, 0);
		Wheel::setPin(directionA_pin, 1);
		Wheel::setPin(directionB_pin, 2);
	};
	virtual ~Wheel(){};

	///////////////////////////////////////////////////////////////////////
	void start(int speed);
	///////////////////////////////////////////////////////////////////////
	void stop();
	///////////////////////////////////////////////////////////////////////
	void setPosition(int pos);
	///////////////////////////////////////////////////////////////////////
	int & getPosition();
	///////////////////////////////////////////////////////////////////////
	void setDirections(int directionA, int directionB);
private:
	int position;
};

//////////////////////////////////////////////////////////////////
void Wheel::start(int speed){
	int* pin = Wheel::getPin();
#ifdef ARDUINO_UNO
	analogWrite(pin[0],speed);
#else
	pwmWrite(pin[0],speed);
#endif
	digitalWrite(pin[1], directionA);
	digitalWrite(pin[2], directionB);
	//analogWrite(11, 255);
	//digitalWrite(12, 1);
	//digitalWrite(13, 0);
}

//////////////////////////////////////////////////////////////////
void Wheel::stop(){
	int* pin = Wheel::getPin();
#ifdef ARDUINO_UNO
        analogWrite(pin[0],0);
#else
        pwmWrite(pin[0],0);
#endif

        digitalWrite(pin[1], 0);
        digitalWrite(pin[2], 0);
}

//////////////////////////////////////////////////////////////////
void Wheel::setPosition(int pos){
	Wheel::position = pos;
}

//////////////////////////////////////////////////////////////////
int& Wheel::getPosition(){
	return Wheel::position;
}

//////////////////////////////////////////////////////////////////
void Wheel::setDirections(int directionA,int directionB){
	Wheel::directionA = directionA;
	Wheel::directionB = directionB;
}
#endif
