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
    void pdvals(float yppi, float ypdi, float rpi, float rdi);
    int getSpeed();
    float error(float current, float target);
    float setData(float s, float ypCurrenti, float ypTargeti, float rCurrenti, rTargeti);
protected:
	float ypp; //yaw/pitch p
    float ypd; //yaw/pitch d
    float rp; //roll p
    float rd; //roll d

    int pin;
    float speed;
    int gpioSpeed;
    bool positive;

    float yppOut;
    float ypdOut;
    float ypCurrentError;
    float ypPreviousError;

    float rpOut;
    float rdOut;
    float rCurrentError;
    float rpreviousError;

    float ypCurrent; //Yaw/Pitch Current Position
    float ypTarget; //Yaw/Pitch Target Position
    float rCurrent; //Roll Current Position
    float rTarget; //Roll Target Posision
};

#endif
