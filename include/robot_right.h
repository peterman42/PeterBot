#ifndef ROBOT_RIGHT_H
#define ROBOT_RIGHT_H

#include "move.h"

class RobotRight: public Move
{
public:

    RobotRight() = default;
	RobotRight(float speed, Wheel** wheels) 
		: Move(speed, wheels)
	{};
    virtual ~RobotRight() = default;

	///////////////////////////////////////////////////////////
	void begin(int num);
	///////////////////////////////////////////////////////////
	void stop(int num);
};
#endif
