#include "robot_left.h"

//////////////////////////////////////////////////////////////////
void RobotLeft::begin(int num)
{
    Wheel** whs = getWheels();
    for (int i = 0; i < num; i++)
    {
        if (whs[i]->getPosition() == POSITIONS::BACK_LEFT || whs[i]->getPosition() == POSITIONS::FRONT_LEFT)
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
void RobotLeft::stop(int num)
{
    Wheel** whs = getWheels();
    for (int i = 0; i < num; i++)
    {
        whs[i]->stop();
    }
}

