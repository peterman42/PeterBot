#ifndef COMPONENT_H
#define COMPONENT_H

#include <stdlib.h>

class Component
{
public:
	Component() :pin(nullptr){};
    explicit Component(int numberOfpins) :pin(nullptr)
	{
		init(numberOfpins);
	}
	
	virtual ~Component()
	{
		//free(pin);
	}

	virtual void setPin(int currentpin, int index)
	{
		//Serial.println("PIN IS : " + String(currentpin));
		Component::pin[index] = currentpin;
	}

	//////////////////////////////////////////////////////////////////
	virtual void addPin(int &currentpin)
	{
		Component::pin = &currentpin;
		Component::pin++;
	}

	//////////////////////////////////////////////////////////////////
	virtual int* getPin()
	{
		return Component::pin;
	}
	
	int* pin;
	int numberOfPins;
private :
    //////////////////////////////////////////////////////////////////
    void init(int num);
};
#endif
