#include "robot.h"

//////////////////////////////////////////////////////////////////
void  Robot::init(int num)
{
    //wheels = (Wheel*)malloc(sizeof(Wheel)*num);
    wheels = (Wheel**)malloc(num*sizeof(Wheel*));
    numberOfWheels = num;
}

void Robot::addWheel(int position, int wheelIndex, int PWM_pin,int directionA_pin,int directionB_pin)
{
    Wheel* new_wheel = new Wheel(PWM_pin,directionA_pin,directionB_pin);
    new_wheel->setPosition(position);
    wheels[wheelIndex] = new_wheel;
}
//////////////////////////////////////////////////////////////////
void Robot::makeMove(int m, float speed){

  if (m == ((int)MOVE::FRONT))
  {
    stopMove(); // stop the previous move if already there is one.

    RobotFront* r = new RobotFront(speed, wheels);
    move = r;
    move->begin(numberOfWheels);
    return;
  }
  else if (m == ((int)MOVE::BACK))
  {
      stopMove(); // stop the previous move if already there is one.
      RobotBack* b = new RobotBack(speed, wheels);
      move = b;
      move->begin(numberOfWheels);
      return;
  }
  else if (m == ((int)MOVE::RIGHT))
  {

    stopMove(); // stop the previous move if already there is one.
    RobotRight* r = new RobotRight(speed, wheels);
    move = r;
    move->begin(numberOfWheels);
    return;
  }
  else if (m == ((int)MOVE::LEFT))
  {

    stopMove(); // stop the previous move if already there is one.
    RobotLeft* r = new RobotLeft(speed, wheels);
    move = r;
    move->begin(numberOfWheels);
    return;
  }
  else if (m == ((int)MOVE::STOP))
  {
      stopMove(); // stop the previous move if already there is one.
      return;
  }
}

//////////////////////////////////////////////////////////////////
void Robot::stopMove()
{
    if (move != nullptr)
    {
        move->stop(numberOfWheels);
        delete move;
        move = nullptr;
    }
}

//////////////////////////////////////////////////////////////////
bool Robot::isMoving()
{
    return (move != nullptr);
}


//////////////////////////////////////////////////////////////////
//void Robot::executeRoute(std::string routeName){
//	for (int i = 0; i < currentRoute->subroutesInCentiM.size();i++){
//		makeMove(0, currentRoute->subroutesInCentiM[i]);
//	}
//}
//
////////////////////////////////////////////////////////////////////
//void loadRoutes(){
//
//}
