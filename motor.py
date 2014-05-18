from RPIO import PWM

class Motor(PWM.Servo):

	def __init__(self, number):
		super(Motor, self).__init__()
		
		self.pin = number

	def scale(self, speed):
		#inputs speed from 0 to 1 and converts it to the 1000 to 2000 scale for speed
		if speed<0:
			speed = 0
		elif speed>1:
			speed = 1
		speed += 1
		speed *= 1000
                print(int(speed))
		return int(speed)

	def set(self, speed):
		self.set_servo(self.pin, self.scale(speed))

	def stop(self):
		self.stop_servo(self.pin)
