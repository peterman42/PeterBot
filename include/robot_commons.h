#ifndef ROBOT_COMMONS_H
#define ROBOT_COMMONS_H

#define RASPBERRY_PI_3
//#define ARDUINO_UNO
#define WHEELS 4

enum WHEEL_POSITIONS
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
