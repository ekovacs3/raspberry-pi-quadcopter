#include "motor.h"

Motor::Motor(int p)
{
	pin = p;
	softPwmCreate(p, 0, 100);
}

void Motor::set(int s)
{
	speed = s;
	softPwmWrite(pin, speed);
}

int Motor::get()
{
	return speed;
}