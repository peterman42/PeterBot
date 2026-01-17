#ifndef ROBOT_BACK_H
#define ROBOT_BACK_H

#include "move.h"

class RobotBack : public Move
{
public:

    RobotBack() = default;
    RobotBack(float speed, Wheel** wheels, int numberOfWheels)
        : Move(speed, wheels, numberOfWheels){};
    virtual	~RobotBack() = default;

	//////////////////////////////////////////////////////////
	void begin(int num);
	//////////////////////////////////////////////////////////
	void stop(int num);
};
#endif
