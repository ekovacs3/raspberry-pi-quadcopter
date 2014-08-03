# You need to "sudo apt-get install libgtkmm-3.0-dev" to build the demo_3d binary

all: demo_dmp

HDRS = helper_3dmath.h I2Cdev.h MPU6050_6Axis_MotionApps20.h MPU6050.h demo_3d.h Motor.h
CMN_OBJS = I2Cdev.o MPU6050.o Motor.o
DMP_OBJS = demo_dmp.o

# Set DMP FIFO rate to 20Hz to avoid overflows on 3d demo.  See comments in
# MPU6050_6Axis_MotionApps20.h for details.

CXXFLAGS = -DDMP_FIFO_RATE=9 -Wall -g -O2 `pkg-config gtkmm-3.0 --cflags --libs` -lpigpio -lpthread -lrt

$(CMN_OBJS) $(DMP_OBJS) $(RAW_OBJS) : $(HDRS)


demo_dmp: $(CMN_OBJS) $(DMP_OBJS)
	$(CXX) -o $@ $^ -lm -lpigpio -lpthread -lrt



clean:
	rm -f $(CMN_OBJS) $(DMP_OBJS) demo_dmp 

