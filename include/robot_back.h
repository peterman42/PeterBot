#ifndef ROBOT_BACK_H
#define ROBOT_BACK_H

#include "move.h"

class RobotBack : public Move
{
public:

	RobotBack()
	{};
	RobotBack(float speed, Wheel** wheels) 
		: Move(speed, wheels){};
	virtual	~RobotBack()
	{};

	//////////////////////////////////////////////////////////
	void begin(int num);
	//////////////////////////////////////////////////////////
	void stop(int num);
};

//////////////////////////////////////////////////////////////////
void RobotBack::begin(int num)
{
	Wheel** whs = getWheels();
	for (int i = 0; i < num; i++)
	{
		int s = (int)getSpeed();
		// First parameter is directionA. Second parameter is directionB.
		whs[i]->setDirections(0, 1);
		whs[i]->start(s);
	}
}

//////////////////////////////////////////////////////////////////
void RobotBack::stop(int num)
{
	Wheel** whs = getWheels();
	for (int i = 0; i < num; i++)
	{
		whs[i]->stop();
	}
}
#endif
