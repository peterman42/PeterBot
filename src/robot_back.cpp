#include "robot_back.h"

//////////////////////////////////////////////////////////////////
void RobotBack::begin(int num)
{
    Wheel** whs = getWheels();
    for (int i = 0; i < num; i++)
    {
        int s = (int)getSpeed();
        // First parameter is directionA. Second parameter is directionB.
        whs[i]->setDirections(0, 1);
        whs[i]->start(s);
    }
}

//////////////////////////////////////////////////////////////////
void RobotBack::stop(int num)
{
    Wheel** whs = getWheels();
    for (int i = 0; i < num; i++)
    {
        whs[i]->stop();
    }
}
