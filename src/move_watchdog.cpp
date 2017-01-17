#include "move_watchdog.h"

//////////////////////////////////////////////////////////
void Move_Watchdog::monitorMove(const std::vector<DistanceObject*>& sensors,  Robot* const robot)
{
    try
    {
        while(1)
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
void Move_Watchdog::startMonitor(Robot* robot)
{
    std::thread t(Move_Watchdog::monitorMove, sensors, robot);
}
