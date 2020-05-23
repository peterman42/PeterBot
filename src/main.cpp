#include <functional>
#include <string>
#include <vector>
#include "robot.h"
#include "serverBot.h"
#include "distance_object.h"
#include "move_watchdog.h"

int main()
{
    wiringPiSetup();

    Robot robot;
    robot.distanceThreshold = DISTANCE_THRESHOLD;

    ServerBot server(DEFAULT_SERVER_PORT);
    float speed = 100;

    // Initialize the pins for the motors.
    PinConfiguration pinConfig(1,4,5,23,27,28);
    robot.configure(pinConfig);

    Move_Watchdog move_watchdog(ULTRA_SENSORS_NUM);
    move_watchdog.initializeUltraSensors();
    move_watchdog.StartUltraSensors();
    move_watchdog.startMonitor(&robot);

    server.Start();
    server.Listen([&robot,speed](int data)
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
            robot.makeMove(move,speed);
        }
        catch(std::exception& e)
        {

        }
        catch(...)
        {
        }
    });

}

