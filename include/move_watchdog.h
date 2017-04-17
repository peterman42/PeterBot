#ifndef MOVE_WATCHDOG_H
#define MOVE_WATCHDOG_H

#include <thread>
#include <chrono>
#include <vector>
#include "robot.h"
#include "distance_object.h"

class Move_Watchdog
{
public:
    std::vector<DistanceObject*>* sensors;
    static bool alive;
    Move_Watchdog() = default;

    explicit Move_Watchdog(std::vector<DistanceObject*>* sensors)
        : sensors(sensors)
    {}

    ~Move_Watchdog() = default;

    //////////////////////////////////////////////////////////
    void StartUltraSensors();

    //////////////////////////////////////////////////////////
    void StopUltraSensors();

    //////////////////////////////////////////////////////////
    void startMonitor(Robot* robot);

    //////////////////////////////////////////////////////////
    void stopMonitor();

private:
    //////////////////////////////////////////////////////////
    static void monitorMove(std::vector<DistanceObject*>* sensors, Robot* const robot);
};
#endif
