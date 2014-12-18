#include "Motor.h"
#include <pigpio.h>
#include <iostream>

Motor::Motor(int pini)
{
    gpioInitialise();
    pin = pini;
    gpioServo(pin, 1000);
}

Motor::Motor(int pini, float pi, bool positivei)
{
    gpioInitialise();
    pin = pini;
    gpioServo(pin, 1000);
    pv = pi;
    positive = positivei;
}

//input speed 0 to 100 and convert to 1000usec to 2000usec
void Motor::set(int s)
{
    if(speed >= 100)
    {
        speed = 99;
    }
    else if(speed <= 0)
    {
        speed = 1;
    }
    speed = (s+100)*10;
    gpioServo(pin, speed);
    std::cout << speed << std::endl;
}

void Motor::pset(int s, float current, float target)
{
	if(positive)
	{
		speed = s + pf(current, target);
        set(speed);
	}
	else
	{
		speed = s - pf(current, target);
        set(speed);
	}
}

int Motor::pf(float current, float target)
{
	float error = current - target;
	return static_cast<int>(error * pv);
}
