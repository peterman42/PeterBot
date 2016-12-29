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
#endif
