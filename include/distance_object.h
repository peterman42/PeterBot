/*******************************
This implementations is based on the  the Ultrasonic Sensor HC-SR04

*******************************
*/

#ifndef DISTANCE_OBJECT_H
#define DISTANCE_OBJECT_H

#include <stdint.h>
#include "robot_commons.h"

class DistanceObject
{
public:
    int echoPin;
    int triggerPin;
    POSITIONS position;
    uint32_t latestDistance;
    static bool alive;

    DistanceObject() = default;

    DistanceObject(int echo, int trigger, POSITIONS pos)
        : echoPin(echo)
        , triggerPin(trigger)
        , position(pos)
    {}

    ~DistanceObject() = default;

    ///////////////////////////////////////////////////////////////////////
    void initialize();
    ///////////////////////////////////////////////////////////////////////
    int senseObject();
    ///////////////////////////////////////////////////////////////////////
    static void watchForObjects(DistanceObject* obj);
};
#endif /* DISTANCE_OBJECT_H */
