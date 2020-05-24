#ifndef ROBOT_LEFT_H
#define ROBOT_LEFT_H

#include "move.h"

class RobotLeft : public Move
{
public:

    RobotLeft() = default;
    RobotLeft(float speed, Wheel** wheels, int numberOfWheels)
        : Move(speed, wheels, numberOfWheels)
	{};
    virtual ~RobotLeft() = default;
	
	//////////////////////////////////////////////////////////
	void begin(int num);
	//////////////////////////////////////////////////////////
	void stop(int num);
};
#endif
