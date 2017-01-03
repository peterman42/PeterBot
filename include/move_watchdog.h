#ifndef MOVE_WATCHDOG_H
#define MOVE_WATCHDOG_H

#include <thread>
#include <vector>
#include "robot.h"
#include "distance_object.h"

class Move_Watchdog : public std::thread
{
public:
    std::vector<DistanceObject*> sensors;
    int obstacleDistanceThreshold;
    Robot* robot;

    Move_Watchdog()
    {}

    Move_Watchdog(std::vector<DistanceObject*> sensors)
        : sensors(sensors)
    {}

    ~Move_Watchdog()
    {}

    //////////////////////////////////////////////////////////
    void monitorMove();

    //////////////////////////////////////////////////////////
    void StartUltraSensors();
};
#endif
