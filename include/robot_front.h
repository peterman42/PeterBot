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

//////////////////////////////////////////////////////////////////
void RobotFront::begin(int num){

	Wheel** whs = getWheels();
	for (int i = 0; i < num; i++)
	{
		int s = (int)getSpeed();
		//Serial.println("SPEED: "+ String(s));
		whs[i]->setDirections(1,0);
		whs[i]->start(s);
	}
}

//////////////////////////////////////////////////////////////////
void RobotFront::stop(int num){
	Wheel** whs = getWheels();
	for (int i = 0; i < num; i++)
	{
		whs[i]->stop();
	}
}
#endif
