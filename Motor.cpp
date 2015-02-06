#include "Motor.h"
#include <pigpio.h>

Motor::Motor(int pini)
{
    gpioInitialise();
    pin = pini;
    gpioServo(pin, 1000);
    ypp = 0;
    ypd = 0;
    positive = true;
    previousError = 0;
}

Motor::Motor(int pini, float pi, bool positivein)
{
    gpioInitialise();
    pin = pini;
    gpioServo(pin, 1000);
    ypp = pi;
    ypd = 0;
    positive = positivein;
    previousError = 0;
}

Motor::Motor(int pini, float pi, float di, bool positivein)
{
    gpioInitialise();
    pin = pini;
    gpioServo(pin, 1000);
    ypp = pi;
    ypd = di;
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
    float pOut = currentError * ypp;
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

void Motor::pdSet(float s)
{
    //
    //Yaw/Pitch
    //
    ypCurrentError = error(ypCurrent, ypTarget);
    yppOut = ypCurrentError * ypp;
    ypdOut = (ypPreviousError - ypCurrentError) * ypd;



    //
    //Roll
    //

    rCurrentError = error(rCurrent, rTarget);
    rpOut = rCurrentError * rp;
    rdOut = (rPreviousError - rCurrentError) * rd;

    if(positive)
    {
        speed = s + yppOut + ypdOut + rpOut + rdOut;
    }
    else
    {
        speed = s - (yppOut + ypdOut + rpOut + rdOut);
    }

    set(speed);
    ypPreviousError = ypCurrentError;
    rPreviousError = rCurrentError
}

void Motor::pdvals(float yppi, float ypdi, float rpi, float rdi)
{
    ypp = yppi;
    ypd = yppd;
    rp = rpi;
    rd = rdi;
}

int Motor::getSpeed()
{
    return speed;
}

float Motor::error(float current, float target)
{
	return current - target;
}

float Motor::setData(float s, float ypCurrenti, float ypTargeti, float rCurrenti, rTargeti)
{
    ypCurrent = ypCurrenti;
    ypTarget = ypTargeti;
    rCurrent = rCurrenti;
    rTarget = rTargeti;
    pdSet(s);
}
