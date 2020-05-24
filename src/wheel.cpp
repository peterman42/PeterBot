#include "wheel.h"

//////////////////////////////////////////////////////////////////
void Wheel::start(int speed){
    int* pin = Wheel::getPin();
#ifdef ARDUINO_UNO
    analogWrite(pin[0],speed);
#else
    softPwmWrite(pin[0],speed);
#endif
    digitalWrite(pin[1], directionA_value);
    digitalWrite(pin[2], directionB_value);
}

//////////////////////////////////////////////////////////////////
void Wheel::stop(){
    int* pin = Wheel::getPin();
#ifdef ARDUINO_UNO
        analogWrite(pin[0],0);
#else
        softPwmWrite(pin[0],0);
#endif
        digitalWrite(pin[1], 0);
        digitalWrite(pin[2], 0);
}

//////////////////////////////////////////////////////////////////
void Wheel::setPosition(int pos){
    Wheel::position = pos;
}

//////////////////////////////////////////////////////////////////
int& Wheel::getPosition(){
    return Wheel::position;
}

//////////////////////////////////////////////////////////////////
void Wheel::setDirections(int directionA,int directionB){
    Wheel::directionA_value = directionA;
    Wheel::directionB_value = directionB;
}
