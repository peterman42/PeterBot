#ifndef ROBOT_RIGHT_H
#define ROBOT_RIGHT_H

#include "move.h"

class RobotRight: public Move
{
public:

	RobotRight()
	{};
	RobotRight(float speed, Wheel** wheels) 
		: Move(speed, wheels)
	{};
	virtual ~RobotRight()
	{};

	///////////////////////////////////////////////////////////
	void begin(int num);
	///////////////////////////////////////////////////////////
	void stop(int num);
};
#endif
