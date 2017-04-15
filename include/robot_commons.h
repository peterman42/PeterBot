#ifndef ROBOT_COMMONS_H
#define ROBOT_COMMONS_H

#define RASPBERRY_PI_3
//#define ARDUINO_UNO

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

enum POSITIONS
{
	FRONT_RIGHT=0,
	FRONT_LEFT,
	BACK_RIGHT,
	BACK_LEFT
};

enum PINS
{
	A0=0,
	A1,
	A2,
	A3,
	D1,
	D2,
	D3,
	D4,
	D5,
	D6,
	D7,
	D8,
	D9,
	D10,
	D11,
	D12
};

enum MOVE
{
	FRONT=0,
	BACK,
	RIGHT,
	LEFT,
	STOP
};
#endif
