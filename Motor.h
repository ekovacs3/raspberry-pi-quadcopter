#ifndef MOTOR_H
#define MOTOR_H

class Motor
{
public:
    Motor(int pini);
    Motor(int pini, float pi, bool positivein);
    Motor(int pini, float pi, float di, bool positivein);
    void set(int s);
    void pSet(float s, float current, float target);
    void pdSet(float s, float current, float target);
    void pdvals(float pi, float pd);
    int getSpeed();
    float error(float current, float target);
protected:
	float pVal;
    float dVal;
    int pin;
    float speed;
    int gpioSpeed;
    float previousError;
    bool positive;
};

#endif
