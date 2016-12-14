#ifndef MOVE_H
#define MOVE_H

#include "wheel.h"

class Move
{
public:

	Move()
	{};
	Move(float speed,Wheel** wheels)
	{
		setSpeed(speed);
		setWheels(wheels);
	};
	virtual ~Move()
	{};

	virtual void begin(int num)=0;
	virtual void stop(int num) = 0;
	void setWheels(Wheel** wheels);
	Wheel** getWheels();
	void setSpeed(float speed);
	float& getSpeed();

	float speed;
	Wheel** wheels;
	
};

//////////////////////////////////////////////////////////////////
void Move::setWheels(Wheel** wheels)
{
	Move::wheels = wheels;
}

//////////////////////////////////////////////////////////////////
Wheel** Move::getWheels()
{
	return Move::wheels;
}

//////////////////////////////////////////////////////////////////
void Move::setSpeed(float speed)
{
	Move::speed = speed;
}

//////////////////////////////////////////////////////////////////
float& Move::getSpeed()
{
	return Move::speed;
}
#endif
