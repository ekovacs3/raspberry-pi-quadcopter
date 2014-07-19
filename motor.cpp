#include "motor.h"

Motor::Motor(int p)
{
	pin = p;
	softServoSetup(p);
}

void Motor::set(int s)
{
	speed = s*15 - 250;
	softServoWrite(pin, speed);
}

int Motor::get()
{
	return speed;
}
