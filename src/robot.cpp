#include "robot.h"

//////////////////////////////////////////////////////////////////
void Robot::init(int num)
{
    //wheels = (Wheel*)malloc(sizeof(Wheel)*num);
    wheels = (Wheel**)malloc(num*sizeof(Wheel*));
    numberOfWheels = num;
}

//////////////////////////////////////////////////////////////////
void Robot::configure(PinConfiguration& pinConfig)
{
    init(2);

    //pinMode(pinConfig.enablePin_motor1,PWM_OUTPUT);
    pinMode(pinConfig.in1Pin_motor1,OUTPUT);
    pinMode(pinConfig.in2Pin_motor1,OUTPUT);
    addWheel( POSITIONS::FRONT_LEFT
            , 0
            , pinConfig.enablePin_motor1
            , pinConfig.in1Pin_motor1
            , pinConfig.in2Pin_motor1);


    //pinMode(pinConfig.enablePin_motor2,PWM_OUTPUT);
    pinMode(pinConfig.in1Pin_motor2,OUTPUT);
    pinMode(pinConfig.in2Pin_motor2,OUTPUT);
    addWheel( POSITIONS::FRONT_RIGHT
            , 1
            , pinConfig.enablePin_motor2
            , pinConfig.in1Pin_motor2
            , pinConfig.in2Pin_motor2);

}

//////////////////////////////////////////////////////////////////
void Robot::addWheel(int position, int wheelIndex, int PWM_pin,int directionA_pin,int directionB_pin)
{
    Wheel* new_wheel = new Wheel(PWM_pin,directionA_pin,directionB_pin);
    new_wheel->setPosition(position);
    wheels[wheelIndex] = new_wheel;
}

//////////////////////////////////////////////////////////////////
void Robot::makeMove(MOVE m, float speed)
{
    stopMove(); // stop the previous move if already there is one.
    move = getMove(m, speed);
    if(move) move->begin(numberOfWheels);
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
Move* Robot::getMove(MOVE m, float speed)
{
    switch(m)
    {
      case MOVE::FRONT:
        return new RobotFront(speed, wheels);
      case MOVE::BACK:
        return new RobotBack(speed, wheels);
      case MOVE::RIGHT:
        return new RobotRight(speed, wheels);
      case MOVE::LEFT:
        return new RobotLeft(speed, wheels);
      case MOVE::STOP:
      default:
        stopMove(); // stop the previous move if already there is one.
        return nullptr;
    }
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
