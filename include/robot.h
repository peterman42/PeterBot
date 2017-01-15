#ifndef ROBOT_H
#define ROBOT_H

#include <stdlib.h>
#include <vector>
#include "robot_commons.h"
#include "distance_object.h"
#include "wheel.h"
#include "move.h"
#include "robot_right.h"
#include "robot_left.h"
#include "robot_front.h"
#include "robot_back.h"

//#include "route.h//

class Robot
{
public:

 	Wheel** wheels;
	int currentWheels;
	int analogPins[4]{A0, A1, A2, A3};
	int PWM[6]{3,5,6,9,10,11};
	int digitalPINS[8]{ 0, 1, 2, 4, 7, 8, 12, 13 };
    int positions[4]{POSITIONS::FRONT_RIGHT, POSITIONS::FRONT_LEFT, POSITIONS::BACK_RIGHT, POSITIONS::BACK_LEFT};
	int numberOfWheels;
	Move* move;
	//Route* currentRoute; // the route that is currently executed.
	//std::vector<Route> allRoutes;

	Robot() 
		: numberOfWheels(0) 
		, move(nullptr)
		/*, currentRoute(nullptr)*/{}
	~Robot()
	{
		
		for(int i=0;i<numberOfWheels;++i)
		{

			delete wheels;

			if(i != (numberOfWheels-1))
			{
				wheels++;	
			}
		}
		delete move;
	}

	void init(int num);
	void makeMove(int m, float speed);
	void stopMove();
	void addWheel(int position, int wheelIndex, int PWM_pin, int directionA_pin, int directionB_pin);
	bool isMoving();
	//void executeMove();
	//void loadRoutes();
};
#endif
