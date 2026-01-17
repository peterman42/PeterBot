#include "robot_front.h"

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
