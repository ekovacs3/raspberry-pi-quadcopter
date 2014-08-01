#include "Motor.h"
#include <pigpio.h>

Motor::Motor(int p)
{
    pin = p;
    gpioServo(pin, 1000);
}

//input speed 0 to 100 and convert to 1000usec to 2000usec
void Motor::set(int s)
{
    speed = (s+100)*10;
    gpioServo(pin, speed);
}
