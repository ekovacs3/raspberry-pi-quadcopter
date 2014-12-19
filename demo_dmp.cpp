#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "Motor.h"
#include "map.h"
#include <pigpio.h>
#include <thread>
#include <iostream>
using namespace std;

// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for SparkFun breakout and InvenSense evaluation board)
// AD0 high = 0x69
MPU6050 mpu;

float motorPower = 10;

Motor fMotor (FRONTMOTOR, MOTORP, false);
int f = 0;
Motor rMotor (RIGHTMOTOR, MOTORP, false);
int r = 0;
Motor lMotor (LEFTMOTOR, MOTORP, true);
int l = 0;
Motor bMotor (BACKMOTOR, MOTORP, true);
int b = 0;


// MPU control/status vars
bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

// orientation/motion vars
Quaternion q;           // [w, x, y, z]         quaternion container
VectorFloat gravity;    // [x, y, z]            gravity vector
float euler[3];         // [psi, theta, phi]    Euler angle container
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector


// ================================================================
// ===                      INITIAL SETUP                       ===
// ================================================================

void setup() {
    // initialize device
    printf("Initializing I2C devices...\n");
    mpu.initialize();

    // verify connection
    printf("Testing device connections...\n");
    printf(mpu.testConnection() ? "MPU6050 connection successful\n" : "MPU6050 connection failed\n");

    // load and configure the DMP
    printf("Initializing DMP...\n");
    devStatus = mpu.dmpInitialize();
    
    // make sure it worked (returns 0 if so)
    if (devStatus == 0) {
        // turn on the DMP, now that it's ready
        printf("Enabling DMP...\n");
        mpu.setDMPEnabled(true);

        // enable Arduino interrupt detection
        //Serial.println(F("Enabling interrupt detection (Arduino external interrupt 0)..."));
        //attachInterrupt(0, dmpDataReady, RISING);
        mpuIntStatus = mpu.getIntStatus();

        // set our DMP Ready flag so the main loop() function knows it's okay to use it
        printf("DMP ready!\n");
        dmpReady = true;

        // get expected DMP packet size for later comparison
        packetSize = mpu.dmpGetFIFOPacketSize();
    } else {
        // ERROR!
        // 1 = initial memory load failed
        // 2 = DMP configuration updates failed
        // (if it's going to break, usually the code will be 1)
        printf("DMP Initialization failed (code %d)\n", devStatus);
    }
}


// ================================================================
// ===                     MAIN Gyro Loop                       ===
// ================================================================

void refreshGyro() {
    // if programming failed, don't try to do anything
    if (!dmpReady) return;
    // get current FIFO count
    fifoCount = mpu.getFIFOCount();
    cout << "fifoCount: " << fifoCount << endl;
    if (fifoCount == 1024) {
        // reset so we can continue cleanly
        mpu.resetFIFO();
        printf("FIFO overflow!\n");
// otherwise, check for DMP data ready interrupt (this should happen frequently)
	} else if (fifoCount >= 42) {
	    // read a packet from FIFO
	    mpu.getFIFOBytes(fifoBuffer, packetSize);

	    mpu.dmpGetQuaternion(&q, fifoBuffer);
	    mpu.dmpGetGravity(&gravity, &q);
	    mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
	    printf("ypr  %7.2f %7.2f %7.2f    ", ypr[0] * 180/M_PI, ypr[1] * 180/M_PI, ypr[2] * 180/M_PI);
	    printf("\n");
            mpu.resetFIFO();
	}
    usleep(10000);
}

void rollP(int target, int power)
{
    int roll = ypr[2] * 180/M_PI;
    int powerdif = (target - roll) * 1;
    r = (int) power + powerdif;
    l = (int) power - powerdif;
}

void pitchP(int target, int power)
{
    int pitch = ypr[1] * 180/M_PI;
    int powerdif = (target - pitch) * 1;
    f = (int) power + powerdif;
    b = (int) power - powerdif;
}

void setMotorPower()
{
    fMotor.pset(motorPower, ypr[1], 0);
    rMotor.pset(motorPower, ypr[2], 0);
    lMotor.pset(motorPower, ypr[2], 0);
    bMotor.pset(motorPower, ypr[1], 0);
    //cout << "\nFront:" << f << "\nRight:" << r << "\nLeft:" << l << "\nBack:" << b;
}

void getInput()
{
    while(true)
    {
        cout << "Please input the speed:";
        cin >> motorPower;
    }
}

int main() 
{
    gpioInitialise();

    setup();
    usleep(100000);

    thread input (getInput);

    while(true){
       	refreshGyro();
       	rollP(0, motorPower);
       	pitchP(0, motorPower);
       	usleep(15000);
	setMotorPower();
    }

}
