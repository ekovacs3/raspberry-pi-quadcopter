import motor
import time

fl = motor.Motor(18)
fr = motor.Motor(23)
bl = motor.Motor(24)
br = motor.Motor(25)

fl.set(1)
fr.set(1)
bl.set(1)
br.set(1)

time.sleep(4)
fl.set(0)
fr.set(0)
bl.set(0)
br.set(0)

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
	while n <= .15:
		fl.set(n)
		fr.set(n)
		bl.set(n)
		br.set(n)	
		print(n)
		n += .03
		time.sleep(.08)
	
	while n >= .11:
		fl.set(n)
		fr.set(n)
		bl.set(n)
		br.set(n)
		print(n)
		n -= .02
		time.sleep(.08)

	while n <= .15:
		fl.set(n)
		fr.set(n)
		bl.set(n)
		br.set(n)	
		print(n)
		n += .03
		time.sleep(.08)
	
	while n >= .11:
		fl.set(n)
		fr.set(n)
		bl.set(n)
		br.set(n)
		print(n)
		n -= .02
		time.sleep(.08)


fl.stop()
fr.stop()
bl.stop()
br.stop()
