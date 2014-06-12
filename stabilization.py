import gyro
import motor
import time

rolldif = .01
pitchdif = .01


#left to right(y)
def roll(power, angle):
    global rolldif
    powerdif = angle/2 * rolldif
    r.set(power - powerdif)
    l.set(power + powerdif)
    
#front to back(x)
def pitch(power, angle):
    global pitchdif
    powerdif = angle/2 * pitchdif
    f.set(power - powerdif)
    b.set(power + powerdif)

#around the center(z)  

print "starting gyro"

print "gyro started"
print "resetting values"
gyro.reset()

l = motor.Motor(18)
f = motor.Motor(23)
b = motor.Motor(24)
r = motor.Motor(25)

l.high()
f.high()
b.high()
r.high()
time.sleep(4)

l.low()
f.low()
b.low()
r.low()
time.sleep(4)

n = 0
while n <= .2:
	f.set(n)
	r.set(n)
	b.set(n)
	r.set(n)	
	print(n)
	n += .1
	time.sleep(.5)

while True:    
    gyro.reset()
    gyro.print_values()
    #r.set(.4)
    #l.set(.4)
    #f.set(.4)
    #b.set(.4)
    roll(.5, gyro.y_angle)
    pitch(.5, gyro.x_angle)
    time.sleep(.1)
