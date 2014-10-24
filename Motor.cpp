#include "Motor.h"
#include <pigpio.h>

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
    speed = (s+100)*10;
    gpioServo(pin, speed);
}

void Motopset(int s, float current, float target)
{
	if(positive)
	{
		set(s + pf(current, target));
	}
	else
	{
		set(s - pf(current, target));
	}
}

int Motor::pf(float current, float target)
{
	float error = current - target;
	return static_cast<int>(error * pv);
}