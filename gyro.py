import math
import smbus
import thread
import time


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
        return 0

def get_y_angular_velocity():
    try:
        gyro_yout = read_word_2c(0x45)
        return (gyro_yout / 131)
    except IOError:
        print "There was an IOError"
        return 0
    
def get_z_angular_velocity():
    try:
        gyro_zout = read_word_2c(0x47)
        return (gyro_zout / 131)
    except IOError:
        print "There was an IOError"
        return 0
    
#all acceleration values are in g's
def get_x_accel():
    try:
        accel_xout = read_word_2c(0x3b)
        return (accel_xout / 16384.0)
    except IOError:
        print "There was an IOError"
        return 0
    
def get_y_accel():
    try:
        accel_yout = read_word_2c(0x3d)
        return (accel_yout / 16384.0)
    except IOError:
        print "There was an IOError"
        return 0
    
def get_z_accel():
    try:
        accel_yout = read_word_2c(0x3f)
        return (accel_yout / 16384.0)
    except IOError:
        print "There was an IOError"
        return 0
    
def dist(a,b):
    return math.sqrt((a*a)+(b*b))

def initialize_gyro():
    ready = False
    while ready != True:
        try:
            bus.write_byte_data(address, power_mgmt_1, 0)
            ready = True
        except IOError:
            print "there was an IOError"
            
def refresh_values():
    #x_angle += get_x_angular_velocity() * (time.time() - self.lasttime
    #y_angle += get_y_angular_velocity() * (time.time() - self.lasttime
    #z_angle += get_z_angular_velocity() * (time.time() - self.lasttime
    lasttime = time.time()
     
def reset():
    global x_angle
    global y_angle
    global z_angle
    x_angle = get_x_rotation()
    y_angle = get_y_rotation()
    z_angle = 0

def print_values():
    print "x_angle:", x_angle
    print "y_angle:", y_angle
    print "z_angle:", z_angle


bus = smbus.SMBus(1) # or bus = smbus.SMBus(1) for Revision 2 boards
address = 0x68       # This is the address value read via the i2cdetect command

power_mgmt_1 = 0x6b
power_mgmt_2 = 0x6c

initialize_gyro()

x_angle = 0
y_angle = 0
z_angle = 0

