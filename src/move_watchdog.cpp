#include "move_watchdog.h"

//////////////////////////////////////////////////////////
void Move_Watchdog::monitorMove()
{
    try
    {
        while(1)
        {
            delay(500);
            for(auto sensor : sensors)
            {
                if (sensor->latestDistance < obstacleDistanceThreshold)
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
