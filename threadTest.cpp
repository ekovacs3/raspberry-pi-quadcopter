#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

int speed = 0;

using namespace std;

void* getInput(void*)
{
	while(true)
	{
		cout << "Please input the speed:";
		cin >> speed;
	}
}
int main()
{
	pthread_t inputThread;

	int test;
	test = pthread_create(&inputThread , NULL, getInput, NULL);

	if(test)
	{
		cout << "Unable to create thread\n";
		exit(1);
	}

	while(true)
	{
		//motor.Set(speed);
		cout << speed << endl;

		usleep(1000000);
	}
}