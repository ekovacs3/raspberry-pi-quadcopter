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
    void pdSet(float s);
    void pdvals(float rppi, float rpdi, float ypi, float ydi);
    int getSpeed();
    float error(float current, float target);
    float setData(float s, float rpCurrenti, float rpTargeti, float yCurrenti, yTargeti);
protected:
	  float rpp; //yaw/pitch p
    float rpd; //yaw/pitch d
    float yp; //roll p
    float yd; //roll d

    int pin;
    float speed;
    int gpioSpeed;
    bool positive;

    float rppOut;
    float rpdOut;
    float rpCurrentError;
    float rpPreviousError;

    float ypOut;
    float ydOut;
    float yCurrentError;
    float ypreviousError;

    float rpCurrent; //Roll/Pitch Current Position
    float rpTarget; //Roll/Pitch Target Position
    float yCurrent; //yaw Current Position
    float yTarget; //yaw Target Posision
};

#endif
