#include <functional>
#include <string>
#include <thread>
#include <vector>
#include "robot.h"
#include "serverBot.h"
#include "distance_object.h"
#include "move_watchdog.h"

#define SERVER_PORT 8888
#define ULTRA_SENSORS_NUM 4

struct PinConfiguration
{
	int enablePin_motor1;
        int in1Pin_motor1;
        int in2Pin_motor1;
        int enablePin_motor2;
        int in1Pin_motor2;
        int in2Pin_motor2;

	PinConfiguration ()
		: enablePin_motor1(0)
		, in1Pin_motor1(0)
		, in2Pin_motor1(0)
		, enablePin_motor2(0)
		, in1Pin_motor2(0)
		, in2Pin_motor2(0)
	{}

	PinConfiguration(int motor1, int in1Motor1, int in2Motor1, int motor2, 
		int in1Motor2, int in2Motor2)
                : enablePin_motor1(motor1) 
                , in1Pin_motor1(in1Motor1) 
                , in2Pin_motor1(in2Motor1)
                , enablePin_motor2(motor2)
                , in1Pin_motor2(in1Motor2)
                , in2Pin_motor2(in2Motor2)
	{

		pinMode(enablePin_motor1,INPUT);
		pinMode(in1Pin_motor1,INPUT);
		pinMode(in2Pin_motor1,INPUT);
		pinMode(enablePin_motor2,INPUT);
		pinMode(in1Pin_motor2,INPUT);
		pinMode(in2Pin_motor2,INPUT);

		digitalWrite(enablePin_motor1,0);
		digitalWrite(in1Pin_motor1,0);
		digitalWrite(in2Pin_motor1,0);
		digitalWrite(enablePin_motor2,0);
		digitalWrite(in1Pin_motor2,0);
		digitalWrite(in2Pin_motor2,0);
	}
};


void RobotConfiguration(Robot& robot, PinConfiguration& pinConfig)
{
	robot.init(2);

	pinMode(pinConfig.enablePin_motor1,PWM_OUTPUT);
	pinMode(pinConfig.in1Pin_motor1,OUTPUT);
	pinMode(pinConfig.in2Pin_motor1,OUTPUT);
    robot.addWheel(POSITIONS::FRONT_LEFT
		,0
		,pinConfig.enablePin_motor1
		,pinConfig.in1Pin_motor1
		,pinConfig.in2Pin_motor1);


	pinMode(pinConfig.enablePin_motor2,PWM_OUTPUT);
     	pinMode(pinConfig.in1Pin_motor2,OUTPUT);
       	pinMode(pinConfig.in2Pin_motor2,OUTPUT);
        robot.addWheel(POSITIONS::FRONT_RIGHT
		,1
		,pinConfig.enablePin_motor2
		,pinConfig.in1Pin_motor2
		,pinConfig.in2Pin_motor2);	

}

void InitUltraSensors(std::vector<DistanceObject*>& sensors)
{
    // Initialize the ultrasonic sensors and store them into a vector.

    DistanceObject* UltraSensor1 = new DistanceObject;
    sensors.emplace_back(UltraSensor1);

    DistanceObject* UltraSensor2 = new DistanceObject;
    sensors.emplace_back(UltraSensor2);

    DistanceObject* UltraSensor3 = new DistanceObject;
    sensors.emplace_back(UltraSensor3);

    DistanceObject* UltraSensor4 = new DistanceObject;
    sensors.emplace_back(UltraSensor4);
}

int main()
{
	Robot robot;
	Robot* _robot = &robot;
	ServerBot server(SERVER_PORT);
    float speed = 1023;
    std::vector<DistanceObject*> UltraSensors;
    UltraSensors.reserve(ULTRA_SENSORS_NUM);
    Move_Watchdog move_watchdog(UltraSensors);

    wiringPiSetup();

    // Initialize the pins for the motors.
    PinConfiguration pinConfig(1,4,5,23,27,28);
    RobotConfiguration(robot,pinConfig);

    // Initialize the distance sensors.
    InitUltraSensors(UltraSensors);
    move_watchdog.StartUltraSensors();

    //move_watchdog.start();

	server.Start();
	server.Listen([_robot,speed](int data)
	{
		try
		{	MOVE move = MOVE::STOP;
			switch(data)
			{
				case 0:
				{
					move = MOVE::FRONT;
					break;	
				}
                                case 1:
                                {
                         		move = MOVE::BACK;
					break;
                                }
                                case 2:
                                {
                         		move = MOVE::RIGHT;
					break;
                                }
                                case 3:
                                {	
                         		move = MOVE::LEFT;
					break;
                                }
                                case 4:
                                {
                         		move = MOVE::STOP;
					break;
                                }
			}
			_robot->makeMove(move,speed);
		
		}
		catch(std::exception& e)
		{

		}
		catch(...)
		{
		}
	});

}

