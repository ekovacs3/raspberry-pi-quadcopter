#ifndef MOTOR_H
#define MOTOR_H

class Motor
{
public:
    Motor(int p);
    void set(int s);
protected:
    int pin;
    int speed;
};

#endif
