#ifndef MOVE_WATCHDOG_H
#define MOVE_WATCHDOG_H

#include <thread>
#include <vector>
#include "robot.h"
#include "distance_object.h"

class Move_Watchdog
{
public:
    std::vector<DistanceObject*> sensors;

    Move_Watchdog() = default;

    explicit Move_Watchdog(std::vector<DistanceObject*> sensors)
        : sensors(sensors)
    {}

    ~Move_Watchdog() = default;

    //////////////////////////////////////////////////////////
    void StartUltraSensors();

    //////////////////////////////////////////////////////////
    void startMonitor(Robot* robot);

private:
    //////////////////////////////////////////////////////////
    static void monitorMove(const std::vector<DistanceObject*>& sensors, Robot* const robot);
};
#endif
