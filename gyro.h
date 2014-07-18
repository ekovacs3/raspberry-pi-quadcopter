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
    float getPitch()
    float getRoll();   
protected:
   mpu6050 mpu;
   // orientation/motion vars
   Quaternion q;           // [w, x, y, z]         quaternion container     
   VectorFloat gravity;    // [x, y, z]            gravity vector
   float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector
    
   void setup();
   
}    
#endif
