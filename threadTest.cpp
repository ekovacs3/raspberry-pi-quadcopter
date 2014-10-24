#include <iostream>
#include <thread>
#include <unistd.h>
#include <stdlib.h>
#include <mutex>

int speed = 0;

using namespace std;

mutex mtx;

void getInput()
{
	while(true)
	{
		cout << "Please input the speed:";
		cin >> speed;
	}
}
int main()
{

	thread input (getInput);

	while(true)
	{
		//motor.Set(speed);
		cout << speed << endl;

		usleep(1000);
	}
}