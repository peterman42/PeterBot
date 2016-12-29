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
#endif
