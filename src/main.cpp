#include "robot.h"
#include "serverBot.h"
#include <functional>
#include <string>
//#include "../amalgamate/crow_all.h"

#define SERVER_PORT 8888

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
//	wiringPiSetup();
	robot.init(2);

	pinMode(pinConfig.enablePin_motor1,PWM_OUTPUT);
	pinMode(pinConfig.in1Pin_motor1,OUTPUT);
	pinMode(pinConfig.in2Pin_motor1,OUTPUT);
	robot.addWheel(WHEEL_POSITIONS::FRONT_LEFT
		,0
		,pinConfig.enablePin_motor1
		,pinConfig.in1Pin_motor1
		,pinConfig.in2Pin_motor1);


	pinMode(pinConfig.enablePin_motor2,PWM_OUTPUT);
     	pinMode(pinConfig.in1Pin_motor2,OUTPUT);
       	pinMode(pinConfig.in2Pin_motor2,OUTPUT);
       	robot.addWheel(WHEEL_POSITIONS::FRONT_RIGHT
		,1
		,pinConfig.enablePin_motor2
		,pinConfig.in1Pin_motor2
		,pinConfig.in2Pin_motor2);	

}


int main()
{
	Robot robot;
	Robot* _robot = &robot;
	ServerBot server(SERVER_PORT);
	
	wiringPiSetup();
	PinConfiguration pinConfig(1,4,5,23,27,28);

	float speed = 1023;

	RobotConfiguration(robot,pinConfig);
	//robot.makeMove(MOVE::FRONT,speed);

/*	crow::SimpleApp app;
	CROW_ROUTE(app,"/<int>")
	([_robot,speed](int data)
        {
		int success = 1;
                try
                {       MOVE move = MOVE::STOP;
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
			success = 0;
                }
                catch(...)
                {
			success = 0;
                }

		return crow::response(std::to_string(success));
        });

	app.port(SERVER_PORT).run();

*/
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

