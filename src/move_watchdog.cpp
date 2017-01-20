#include "move_watchdog.h"

bool Move_Watchdog::alive = true;

//////////////////////////////////////////////////////////
void Move_Watchdog::monitorMove(const std::vector<DistanceObject*>& sensors,  Robot* const robot)
{
    try
    {
        while(Move_Watchdog::alive)
        {
            delay(500);
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
void Move_Watchdog::StartUltraSensors()
{
    // Start the sensors to trigger waves and receive echoes.
    for(auto sensor : sensors)
    {
        if(sensor)
            std::thread t(DistanceObject::watchForObjects,sensor);
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
}

//////////////////////////////////////////////////////////
void Move_Watchdog::stopMonitor()
{
    // Stop the DistanceObject threads.
    StopUltraSensors();

    // Stop the monitoring of Move_Watchdog
    Move_Watchdog::alive = false;
}
