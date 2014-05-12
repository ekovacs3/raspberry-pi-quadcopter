from RPIO import PWM
import time

fl = PWM.Servo()
fr = PWM.Servo()
bl = PWM.Servo()
br = PWM.Servo()

fl.set_servo(17, 2000)
fr.set_servo(18, 2000)
bl.set_servo(23, 2000)
br.set_servo(24, 2000)

time.sleep(4)

fl.set_servo(17, 1000)
fr.set_servo(18, 1000)
bl.set_servo(23, 1000)
br.set_servo(24, 1000)

time.sleep(4)

print("please enter a number between 1000 and 2000")

n = 1000

while n <= 1200:
	fl.set_servo(17,n)
	fr.set_servo(18,n)
	bl.set_servo(23,n)
	br.set_servo(24,n)
	print(n)
	n += 10
	time.sleep(.5)

while n >= 1000:
	fl.set_servo(17,n)
	fr.set_servo(18,n)
	bl.set_servo(23,n)
	br.set_servo(24,n)
	print(n)
	n -= 10
	time.sleep(.5)

fl.stop_servo(17)
fr.stop_servo(18)
bl.stop_servo(23)
br.stop_servo(24)
