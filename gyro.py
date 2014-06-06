import math
import smbus
import thread
import time

power_mgmt_1 = 0x6b
power_mgmt_2 = 0x6c
x_rotation_register = 0x43
y_rotation_retister = 0x45
z_rotation_register = 0x47
x_accel_register = 0x3b
y_accel_register = 0x3d
z_accel_register = 0x3f

def read_byte(adr):
    return bus.read_byte_data(address, adr)

def read_word(adr):
    high = bus.read_byte_data(address, adr)
    low = bus.read_byte_data(address, adr+1)
    val = (high << 8) + low
    return val

def read_word_2c(adr):
    val = read_word(adr)
    if (val >= 0x8000):
        return -((65535 - val) + 1)
    else:
        return val

#These two funcitons use accelerometer data to approximate rotation
def get_y_rotation():
	x = get_x_accel()
	y = get_y_accel()
	z = get_z_accel()
	radians = math.atan2(x, dist(y,z))
	return -math.degrees(radians)

def get_x_rotation():
	x = get_x_accel()
	y = get_y_accel()
	z = get_z_accel()
	radians = math.atan2(y, dist(x,z))
	return math.degrees(radians)
	#All gyro angular velocity is in deg/s
    
def get_x_angular_velocity():
    try:
        gyro_xout = read_word_2c(0x43)
        return (gyro_xout / 131)
    except IOError:
        print "There was an IOError"

def get_y_angular_velocity():
    try:
        gyro_yout = read_word_2c(0x45)
        return (gyro_yout / 131)
    except IOError:
        print "There was an IOError"

def get_z_angular_velocity():
    try:
        gyro_zout = read_word_2c(0x47)
        return (gyro_zout / 131)
    except IOError:
        print "There was an IOError"

#all acceleration values are in g's
def get_x_accel():
    try:
        accel_xout = read_word_2c(0x3b)
        return (accel_xout / 16384.0)
    except IOError:
        print "There was an IOError"

def get_y_accel():
    try:
        accel_yout = read_word_2c(0x3d)
        return (accel_yout / 16384.0)
    except IOError:
        print "There was an IOError"

def get_z_accel():
    try:
        accel_yout = read_word_2c(0x3d)
        return (accel_yout / 16384.0)
    except IOError:
        print "There was an IOError"


class Gyro:
    bus = smbus.SMBus(1) # or bus = smbus.SMBus(1) for Revision 2 boards
    address = 0x68       # This is the address value read via the i2cdetect command

 
    def __init__(self):
        self.ready = False
        while self.ready != True:
            try:
                self.bus.write_byte_data(self.address, 0x6b, 0)
                startprogram = True
            except IOError:
                print "there was an IOError"
            self.lasttime = time.time()


    def refresh_values(self):
        self.x_angle += get_x_angular_velocity() * (time.time() - self.lasttime)
        self.y_angle += get_y_angular_velocity() * (time.time() - self.lasttime)
        self.z_angle += get_z_angular_velocity() * (time.time() - self.lasttime)

        self.lasttime = time.time()
        
    def reset_gyro(self):
        self.x_angle = get_x_rotation()
        self.y_angle = get_y_rotation()
        self.z_angle = 0

    def print_values(self):
        print "X angle:", self.x_angle
        print "Y angle:", self.y_angle
        print "Z angle:", self.z_angle

