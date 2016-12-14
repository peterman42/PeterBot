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

//////////////////////////////////////////////////////////////////
void RobotRight::begin(int num){
	
	Wheel** whs = getWheels();
	for (int i = 0; i < num; i++)
	{	
		if (whs[i]->getPosition() == WHEEL_POSITIONS::BACK_RIGHT || whs[i]->getPosition() == WHEEL_POSITIONS::FRONT_RIGHT)
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
void RobotRight::stop(int num){
	Wheel** whs = getWheels();
	for (int i = 0; i < num;i++)
	{
		whs[i]->stop();
	}
}
#endif
