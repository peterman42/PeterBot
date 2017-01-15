#ifndef WHEEL_H
#define WHEEL_H

#include "robot_commons.h"
#include "component.h"

class Wheel: public Component
{
public:
	int directionA;
	int directionB;

    Wheel()
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
    virtual ~Wheel() = default;

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
#endif
