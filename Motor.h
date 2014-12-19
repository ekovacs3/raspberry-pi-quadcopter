#ifndef MOTOR_H
#define MOTOR_H

class Motor
{
public:
    Motor(int pini);
    Motor(int pini, float pi, bool positivein);
    Motor(int pini, float pi, float di, bool positivein);
    void set(int s);
    void pSet(int s, float current, float target);
    void pdSet(int s, float current, float target);
    int getSpeed();
    int error(float current, float target);
protected:
	float pVal;
    float dVal;
    int pin;
    int speed;
    int previousError;
    bool positive;
};

#endif
