#include "component.h"

//////////////////////////////////////////////////////////////////
void Component::init(int num)
{
    pin = (int*)malloc(sizeof(int)*num);
    numberOfPins = num;
}
