#include "move_watchdog.h"

bool Move_Watchdog::alive = true;

//////////////////////////////////////////////////////////
void Move_Watchdog::monitorMove(std::vector<DistanceObject*> sensors,  Robot* const robot)
{
    try
    {
        while(Move_Watchdog::alive)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            for(auto sensor : sensors)
            {
                if (sensor->latestDistance < robot->distanceThreshold)
                    if (robot) robot->stopMove();
            }
        }
    }
    catch(...)
    {

    }
}

//////////////////////////////////////////////////////////
void Move_Watchdog::initializeUltraSensors()
{
    // Initialize the ultrasonic sensors and store them into a vector.

    DistanceObject* UltraSensor1 = new DistanceObject(0,7,POSITIONS::FRONT_RIGHT);
    UltraSensor1->initialize();
    sensors.emplace_back(UltraSensor1);

    //DistanceObject* UltraSensor2 = new DistanceObject;
    //sensors.emplace_back(UltraSensor2);
    //
    //DistanceObject* UltraSensor3 = new DistanceObject;
    //sensors.emplace_back(UltraSensor3);
    //
    //DistanceObject* UltraSensor4 = new DistanceObject;
    //sensors.emplace_back(UltraSensor4);
}

//////////////////////////////////////////////////////////
void Move_Watchdog::StartUltraSensors()
{
    // Start the sensors to trigger waves and receive echoes.
    for(auto sensor : sensors)
    {
        if(sensor)
        {
                std::thread t(DistanceObject::watchForObjects,sensor);
                t.detach();
        }

    }
}

//////////////////////////////////////////////////////////
void Move_Watchdog::StopUltraSensors()
{
    DistanceObject::alive = false;
}

//////////////////////////////////////////////////////////
void Move_Watchdog::startMonitor(Robot* robot)
{
    std::thread t(Move_Watchdog::monitorMove, sensors, robot);
    t.detach();
}

//////////////////////////////////////////////////////////
void Move_Watchdog::stopMonitor()
{
    // Stop the DistanceObject threads.
    StopUltraSensors();

    // Stop the monitoring of Move_Watchdog
    Move_Watchdog::alive = false;
}
