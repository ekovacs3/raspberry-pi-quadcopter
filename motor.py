from RPIO import PWM

class Motor(Servo):

	def __init__(number):
		self.pin = number

	def scale(speed):
		#inputs speed from 0 to 1 and converts it to the 1000 to 2000 scale for speed
		if speed<0:
			speed = 0
		elif speed>1:
			speed = 1
		speed += 1
		speed *= 1000
		return int(speed)

	def set(speed):
		self.set_servo(self.pin, scale(speed))

	def stop():
		self.stop_servo(self.pin)