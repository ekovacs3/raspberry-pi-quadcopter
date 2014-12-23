#include "Motor.h"
#include <pigpio.h>

Motor::Motor(int pini)
{
    gpioInitialise();
    pin = pini;
    gpioServo(pin, 1000);
    pVal = 0;
    dVal = 0;
    positive = true;
    previousError = 0;
}

Motor::Motor(int pini, float pi, bool positivein)
{
    gpioInitialise();
    pin = pini;
    gpioServo(pin, 1000);
    pVal = pi;
    dVal = 0;
    positive = positivein;
    previousError = 0;
}

Motor::Motor(int pini, float pi, float di, bool positivein)
{
    gpioInitialise();
    pin = pini;
    gpioServo(pin, 1000);
    pVal = pi;
    dVal = di;
    positive = positivein;
    previousError = 0;
}

//input speed 0 to 100 and convert to 1000usec to 2000usec
void Motor::set(int s)
{
    if(s >= 100)
    {
        speed = 99;
    }
    else if(s <= 0)
    {
        speed = 1;
    }
    else
    {
        speed = s;
    }
    gpioSpeed = (static_cast<int>(speed) + 100) * 10;
    gpioServo(pin, gpioSpeed);
}

void Motor::pSet(float s, float current, float target)
{
    float currentError = error(current, target);
    float pOut = currentError * pVal;
	if(positive)
	{
		speed = s + pOut;
	}
	else
	{
		speed = s - pOut;
	}
    set(speed);
}

void Motor::pdSet(float s, float current, float target)
{
    float pOut = 0;
    float dOut = 0;
    float currentError = error(current, target);
    pOut = currentError * pVal;
    dOut = (previousError - currentError) * dVal;
    if(positive)
    {
        speed = s + pOut + dOut;
    }
    else
    {
        speed = s - (pOut+dOut);
    }
    set(speed);
    previousError = currentError;
}

int Motor::getSpeed()
{
    return speed;
}

float Motor::error(float current, float target)
{
	return current - target;
}
