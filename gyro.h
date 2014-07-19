#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"

#ifndef GYRO_H
#define GYRO_H

class Gyro{
public:

    
    Gyro();
    
    void setup();
    void getYPR();
    float getYaw();
    float getPitch();
    float getRoll();   
protected:
   MPU6050 mpu;
   // orientation/motion vars
   Quaternion q;           // [w, x, y, z]         quaternion container     
   VectorFloat gravity;    // [x, y, z]            gravity vector
   float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector
    // MPU control/status vars
    bool dmpReady;  // set true if DMP init was successful
    uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
    uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
    uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
    uint16_t fifoCount;     // count of all bytes currently in FIFO
    uint8_t fifoBuffer[64]; // FIFO storage buffer
};    
#endif
