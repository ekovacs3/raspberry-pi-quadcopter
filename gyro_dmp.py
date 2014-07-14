#
#
#This code is a combination of code found on
#http://www.raspberrypi.org/forums/viewtopic.php?t=22266
#and
#http://blog.bitify.co.uk/2013/11/reading-data-from-mpu-6050-on-raspberry.html
#

import smbus
import math
import time

power_mgmt_1 = 0x6b
power_mgmt_2 = 0x6c

bus = smbus.SMBus(1) # or bus = smbus.SMBus(1) for Revision 2 boards
address = 0x68       # This is the address value read via the i2cdetect command

def read_byte(adr):
        try:
                return bus.read_byte_data(address, adr)
        except IOError:
                print "there was an IOError"
                return 0

def read_word(adr):
        try:
            high = bus.read_byte_data(address, adr)
            low = bus.read_byte_data(address, adr+1)
            val = (high << 8) + low
            return val
        except IOError:
                print "There was an IO Error"
                return 0 

def read_word_2c(adr):
    val = read_word(adr)
    if (val >= 0x8000):
        return -((65535 - val) + 1)
    else:
        return val


def initialize():
    write(address,MPU6050_RA_PWR_MGMT_1, 0x03)
    #power and clock values
    write(address, MPU6050_RA_GYRO_CONFIG, 0x18)
    #gyroscope range settings
    write(address, MPU6050_RA_ACCEL_CONFIG, 0x00)
    #accel range settings
    