#ifndef MOTOR_H
#define MOTOR_H

class Motor
{
public:
    Motor(int pini);
    Motor(int pini, float pi, bool positivei);
    void set(int s);
    void pset(int s, float current, float target);
    int pf(float current, float target);
protected:
	float pv;
    int pin;
    int speed;
    bool positive;
};

#endif
