#ifndef MOVE_H
#define MOVE_H

#include "wheel.h"

class Move
{
public:

    Move() = default;
    Move(float speed,Wheel** wheels);

    virtual ~Move()
    {
        // TODO :: Free the Wheel** double pointer
    }

	virtual void begin(int num)=0;
	virtual void stop(int num) = 0;
	void setWheels(Wheel** wheels);
	Wheel** getWheels();
	void setSpeed(float speed);
	float& getSpeed();

	float speed;
	Wheel** wheels;
	
};
#endif
