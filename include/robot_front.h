#ifndef ROBOT_FRONT_H
#define ROBOT_FRONT_H

#include "move.h"


class RobotFront : public Move
{
public:

    RobotFront() = default;
    RobotFront(float speed, Wheel** wheels, int numberOfWheels)
        : Move(speed, wheels, numberOfWheels)
	{};
    virtual ~RobotFront() = default;
	
	//////////////////////////////////////////////////////////
	void begin(int num);
	//////////////////////////////////////////////////////////
	void stop(int num);
};
#endif
