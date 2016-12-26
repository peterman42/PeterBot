/*******************************
This implementations is based on the  the Ultrasonic Sensor HC-SR04

*******************************
*/

#ifndef DISTANCE_OBJECT_H
#define DISTANCE_OBJECT_H

#include <stdlib.h>
#include "robot_commons.h"

class DistanceObject
{
public:
    int echoPin;
    int triggerPin;

    DistanceObject()
    {}

    ~DistanceObject()
    {}

    void initialize();
    void senseObject();
};

#endif /* DISTANCE_OBJECT_H */
