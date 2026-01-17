#ifndef ROBOT_COMMONS_H
#define ROBOT_COMMONS_H

//#define RASPBERRY_PI_3
#define ARDUINO_UNO

#ifdef ARDUINO_UNO
#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif
#ifndef Arduino_h
#include <Arduino.h>
#endif
#else
#include <wiringPi.h>
#include <softPwm.h>
#endif

#define WHEELS 4
#define DEFAULT_SERVER_PORT 8888
#define PWM_RANGE 100
#define ULTRA_SENSORS_NUM 1
#define DISTANCE_THRESHOLD 20

enum POSITIONS
{
	FRONT_RIGHT=0,
	FRONT_LEFT,
	BACK_RIGHT,
	BACK_LEFT
};

enum MOVE
{
	FRONT=0,
	BACK,
	RIGHT,
	LEFT,
	STOP
};

struct PinConfiguration
{
    int enablePin_motor1;
        int in1Pin_motor1;
        int in2Pin_motor1;
        int enablePin_motor2;
        int in1Pin_motor2;
        int in2Pin_motor2;

    PinConfiguration ()
        : enablePin_motor1(0)
        , in1Pin_motor1(0)
        , in2Pin_motor1(0)
        , enablePin_motor2(0)
        , in1Pin_motor2(0)
        , in2Pin_motor2(0)
    {}

    PinConfiguration(int motor1, int in1Motor1, int in2Motor1, int motor2,
        int in1Motor2, int in2Motor2)
                : enablePin_motor1(motor1)
                , in1Pin_motor1(in1Motor1)
                , in2Pin_motor1(in2Motor1)
                , enablePin_motor2(motor2)
                , in1Pin_motor2(in1Motor2)
                , in2Pin_motor2(in2Motor2)
    {

        softPwmCreate(enablePin_motor1,0,PWM_RANGE);
        //pinMode(enablePin_motor1,INPUT);
        pinMode(in1Pin_motor1,INPUT);
        pinMode(in2Pin_motor1,INPUT);

        softPwmCreate(enablePin_motor2,0,PWM_RANGE);
        //pinMode(enablePin_motor2,INPUT);
        pinMode(in1Pin_motor2,INPUT);
        pinMode(in2Pin_motor2,INPUT);

        digitalWrite(enablePin_motor1,0);
        digitalWrite(in1Pin_motor1,0);
        digitalWrite(in2Pin_motor1,0);
        digitalWrite(enablePin_motor2,0);
        digitalWrite(in1Pin_motor2,0);
        digitalWrite(in2Pin_motor2,0);
    }
};

struct ClientMessage
{
    int data;
    bool status;
    bool keepAlive;

    ClientMessage()
    : data(0)
    , status(false)
    , keepAlive(true)
    {}
};

#endif
