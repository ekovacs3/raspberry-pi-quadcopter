#include "Quadcopter.h"
#include <thread>
#include <iostream>
#include <unistd.h>

void getInput();
float motorPower;
int main(){
    std::thread input (getInput);
    Quadcopter quad;

    while(motorPower != -1)
    {
        quad.setMotorPower(motorPower);
        quad.refreshGyroValues();
        quad.applyMotorPowers();
        usleep(20000);
    }
    quad.setMotorPower(0);

}

void getInput()
{
    while(true)
    {
        std::cout << "Please input the speed:";
        std::cin >> motorPower;
    }
}
