#ifndef ROBOT_LEFT_H
#define ROBOT_LEFT_H

#include "move.h"

class RobotLeft : public Move
{
public:

	RobotLeft()
	{};
	RobotLeft(float speed, Wheel** wheels) 
		: Move(speed, wheels)
	{};
	virtual ~RobotLeft()
	{};
	
	//////////////////////////////////////////////////////////
	void begin(int num);
	//////////////////////////////////////////////////////////
	void stop(int num);
};

//////////////////////////////////////////////////////////////////
void RobotLeft::begin(int num)
{
	Wheel** whs = getWheels();
	for (int i = 0; i < num; i++)
	{
		if (whs[i]->getPosition() == WHEEL_POSITIONS::BACK_LEFT || whs[i]->getPosition() == WHEEL_POSITIONS::FRONT_LEFT)
		{
			int s = (int)getSpeed();
			whs[i]->setDirections(1, 0);
			whs[i]->start(s);
		}
		else
		{
			whs[i]->stop();
		}
	}

}

///////////////////////////////////////////////////////////////////
void RobotLeft::stop(int num)
{
	Wheel** whs = getWheels();
	for (int i = 0; i < num; i++)
	{
		whs[i]->stop();
	}
}

#endif
