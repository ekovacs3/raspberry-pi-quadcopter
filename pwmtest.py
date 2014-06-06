import motor
import time

fl = motor.Motor(18)
fr = motor.Motor(23)
bl = motor.Motor(24)
br = motor.Motor(25)

fl.high()
fr.high()
bl.high()
br.high()

time.sleep(4)
fl.low()
fr.low()
bl.low()
br.low()

time.sleep(4)

print("please enter a number between 1000 and 2000")

n = 0
while n <= .12:
	fl.set(n)
	fr.set(n)
	bl.set(n)
	br.set(n)	
	print(n)
	n += .10
	time.sleep(.5)
	
while True:
	while n <= .50:
		fl.set(n)
		fr.set(n)
		bl.set(n)
		br.set(n)	
		print(n)
		n += .03
		time.sleep(.3)
	
	while n >= .2:
		fl.set(n)
		fr.set(n)
		bl.set(n)
		br.set(n)
		print(n)
		n -= .02
		time.sleep(.3)

	while n <= 1:
		fl.set(n)
		fr.set(n)
		bl.set(n)
		br.set(n)	
		print(n)
		n += .03
		time.sleep(.3)
	
	while n >= .2:
		fl.set(n)
		fr.set(n)
		bl.set(n)
		br.set(n)
		print(n)
		n -= .02
		time.sleep(.3)


fl.stop()
fr.stop()
bl.stop()
br.stop()
