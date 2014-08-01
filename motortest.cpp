#include <iostream>
#include <pigpio.h>
#include <unistd.h>
#include "Motor.h"

using namespace std;

int main ()
{
    gpioInitialise();
    Motor front (18);
	Motor left (23);
	Motor right (24);
	Motor back(25);
    sleep(3);
    
    int i = 0;
    while(i < 50)
    {
        front.set(i);
        left.set(i);
        right.set(i);
        back.set(i);
        cout << "speed:" << i << "\n";
        sleep(2);
        i+=5;
    }
    front.set(0);
    left.set(0);
    right.set(0);
    back.set(0);
    gpioTerminate();
}
