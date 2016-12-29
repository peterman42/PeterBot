#include "robot_right.h"

//////////////////////////////////////////////////////////////////
void RobotRight::begin(int num){

    Wheel** whs = getWheels();
    for (int i = 0; i < num; i++)
    {
        if (whs[i]->getPosition() == POSITIONS::BACK_RIGHT || whs[i]->getPosition() == POSITIONS::FRONT_RIGHT)
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
