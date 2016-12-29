#ifndef ROBOT_FRONT_H
#define ROBOT_FRONT_H

#include "move.h"


class RobotFront : public Move
{
public:

	RobotFront()
	{};
	RobotFront(float speed, Wheel** wheels) 
		: Move(speed, wheels)
	{};
	virtual ~RobotFront()
	{};
	
	//////////////////////////////////////////////////////////
	void begin(int num);
	//////////////////////////////////////////////////////////
	void stop(int num);
};
#endif
