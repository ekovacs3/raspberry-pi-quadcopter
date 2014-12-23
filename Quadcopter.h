#include "DMP.h"
#include "Motor.h"
#include "map.h"

class Quadcopter
{
public:
    Quadcopter();
    void refreshGyroValues();
    void applyMotorPowers();
    void setMotorPower(float power);
    ~Quadcopter();
protected:
    float motorPower;
    float ypr[3];
    DMP* dmp;
    Motor* fMotor;
    Motor* rMotor;
    Motor* lMotor;
    Motor* bMotor;
}
