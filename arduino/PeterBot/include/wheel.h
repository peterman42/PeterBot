#ifndef WHEEL_H
#define WHEEL_H

#include "robot_commons.h"
#include "component.h"

class Wheel: public Component
{
public:
    Wheel()
		: Component(3)
    {}
	Wheel(int PWM_pin, int directionA_pin, int directionB_pin) 
		: Component(3)
	{

        setPin(PWM_pin, 0);
        setPin(directionA_pin, 1);
        setPin(directionB_pin, 2);
    }
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
    void setDirections(int directionA_value, int directionB_value);
private:
	int position;
    int directionA_value;
    int directionB_value;

};
#endif
