#include <stdio.h>
#include <stdlib.h>
#include "distance_object.h"

///////////////////////////////////////////////////////////////////////
void DistanceObject::initialize()
{
    // Initialize the modes of trigger and echo pins.
    pinMode(triggerPin,OUTPUT);
    pinMode(echoPin,INPUT);


    // Initialize to LOW the trigger pin.
    digitalWrite(triggerPin,LOW);
    delay(100);
}
///////////////////////////////////////////////////////////////////////
int DistanceObject::senseObject()
{
    // Send beacon signal.
    digitalWrite(tiggerPin,HIGH);
    delayMicroSeconds(20);
    digitalWrite(tiggerPin,LOW);

    //Wait for echo start.
    while(digitalRead(echoPin) == LOW);

    long startTime = micros();
    //Wait for echo end.
    while(digitalRead(echoPin) == HIGH);
    long durationTime = micros() - startTime;

    latestDistance = 17150 * durationTime;
    return latestDistance;
}

///////////////////////////////////////////////////////////////////////
/// This function will run up on a separate thread.
///
void watchForObjects()
{
    while(1)
    {
        try
        {
            delay(1000);
            // Sense any object.
            senseObject();
        }
        catch(...)
        {
            break;
        }
    }

}
