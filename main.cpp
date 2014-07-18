#include "motor.h"
#include <iostream>
#include <unistd.h>

int main(){

    wiringPiSetup();    

    Motor front (1);

	front.set(100);
	std::cout << "set to 100 \n";
	sleep(4);

	front.set(0);
    std::cout << "set to 0 \n";
	sleep(4);

	front.set(30);
	std::cout << "set to 30 \n";
	sleep(4);

	front.set(0);
	std::cout << "set to 0 \n";
}


