/*******************************
This implementations is based on the  the Ultrasonic Sensor HC-SR04

*******************************
*/

#ifndef DISTANCE_OBJECT_H
#define DISTANCE_OBJECT_H

#include "robot_commons.h"

class DistanceObject
{
public:
    int echoPin;
    int triggerPin;
    POSITIONS position;
    int latestDistance;

    DistanceObject()
    {}

    DistanceObject(int echo, int trigger, POSITIONS pos)
        : echoPin(echo)
        , triggerPin(trigger)
        , position(pos)
    {}

    ~DistanceObject()
    {}

    ///////////////////////////////////////////////////////////////////////
    void initialize();
    ///////////////////////////////////////////////////////////////////////
    int senseObject();
    ///////////////////////////////////////////////////////////////////////
    void watchForObjects();
};
#endif /* DISTANCE_OBJECT_H */
