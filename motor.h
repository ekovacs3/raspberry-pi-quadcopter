#include <wiringPi.h>
#include <softServo.h>

#ifndef MOTOR_H
#define MOTOR_H

class Motor{
public:

    Motor(int p);
	
	void set(int s);
	int get();

protected:
	int pin;
	int speed;
};

#endif
