#include <Arduino.h>
#include "robot_commons.h"
#include "robot.h"
#include <SoftwareSerial.h>

SoftwareSerial mySerial(3, 4); // RX, TX
PinConfiguration pinConfig(1,4,5,23,27,28);
Robot robot;
float speed = 100;

void setup() {

  robot.distanceThreshold = DISTANCE_THRESHOLD;
}

void loop() {
  while (mySerial.available()) {
    int data = mySerial.read();
    MOVE move = MOVE::STOP;
    switch(data)
    {
        case 0:
        {
            move = MOVE::FRONT;
            break;
        }
        case 1:
        {
            move = MOVE::BACK;
            break;
        }
        case 2:
        {
            move = MOVE::RIGHT;
            break;
        }
        case 3:
        {
            move = MOVE::LEFT;
            break;
        }
        case 4:
        {
            move = MOVE::STOP;
            break;
        }
    }
    robot.makeMove(move,speed);
    }
 
}