#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <chrono>
#include <iostream>
#include "distance_object.h"

bool DistanceObject::alive = true;

///////////////////////////////////////////////////////////////////////
void DistanceObject::initialize()
{
    // Initialize the modes of trigger and echo pins.
    pinMode(triggerPin,OUTPUT);
    pinMode(echoPin,INPUT);


    // Initialize to LOW the trigger pin.
    digitalWrite(triggerPin,LOW);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}
///////////////////////////////////////////////////////////////////////
int DistanceObject::senseObject()
{
    // Send beacon signal.
    digitalWrite(triggerPin,HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin,LOW);

    //Wait for echo start.
    while(digitalRead(echoPin) == LOW);

    std::chrono::time_point<std::chrono::system_clock> start, end;

    start = std::chrono::system_clock::now();

    //Wait for echo end.
    while(digitalRead(echoPin) == HIGH);

    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;

    latestDistance = elapsed_seconds.count() * 17150;

    return latestDistance;
}

///////////////////////////////////////////////////////////////////////
/// This function will run up on a separate thread.
///
void DistanceObject::watchForObjects(DistanceObject* obj)
{
    while(DistanceObject::alive)
    {
        try
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            // Sense any object.
            if(obj)
                obj->senseObject();
        }
        catch(...)
        {
            break;
        }
    }
}
