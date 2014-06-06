import gyro
import time

print "starting gyro"
g = gyro.Gyro()
print "gyro started"
print "resetting values"
g.reset_gyro()

while true:
    g.refresh_values()
    g.print_values()
    time.sleep(.1)

