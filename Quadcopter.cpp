#include "Quadcopter.h"
//#include <iostream>

Quadcopter::Quadcopter
{
    fMotor = new Motor(FRONTMOTOR, MOTORP, false);
    rMotor = new Motor(RIGHTMOTOR, MOTORP, false);
    lMotor = new Motor(LEFTMOTOR, MOTORP, true);
    bMotor = new Motor(BACKMOTOR, MOTORP, true);
    dmp = new DMP();
    motorPower = 0;
}

void Quadcopter::refreshGyroValues()
{
    dmp->refreshGyro();
    ypr[0] = dmp->getY();
    ypr[1] = dmp->getP();
    ypr[2] = dmp->getR();
}

void Quadcopter::applyMotorPowers()
{
    fMotor->pdSet(motorPower, ypr[1], 0);
    rMotor->pdSet(motorPower, ypr[2], 0);
    lMotor->pdSet(motorPower, ypr[2], 0);
    bMotor->pdSet(motorPower, ypr[1], 0);
    //std::cout << "\nFront:" << fMotor->getSpeed() << "\nRight:" << rMotor->getSpeed();
    //std::cout << "\nLeft:" << lMotor->getSpeed() << "\nBack:" << bMotor->getSpeed() << endl;;
}

void Quadcopter::setMotorPower(float power)
{
    motorPower = p;
}

~Quadcopter()
{
    delete fMotor;
    delete rMotor;
    delete lMotor;
    delete bMotor;
    delete dmp;
}
