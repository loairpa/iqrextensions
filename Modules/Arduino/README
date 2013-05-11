iqr module for the arduino board.

This folder hosts the iqr source code for communicating with the arduino.
it is based on the project iqr-duino https://github.com/debiatan/iqr-duino with analog read/write addons.


Included files:moduleArduinoAnalog.cpp, moduleArduinoAnalog.h,arduino.cc, arduino.h, SerialStream.h SerialStream.cc, SerialStreamBuf.h SerialStreamBuf.cc, SerialInterfaceThreading.ino (including code for HaViMo)



Accessing the arduino I/O ports from iqr:
=========================================

Ports 0 and 1 are busy because they are used as part of the USB serial link.
12 ports are left (2 to 13) to work with.

Open the file 'AnalogArduinotest.iqr' from inside iqr once you have correctly installed the 'moduleArduinoAnalog.so' file under ~/iqr/lib/Modules. You will see four groups inside
the 'ArduinoAnalog' process:

- Comm. digit. read. (Command digital reading).(size 10)- Send a value different than 0
to each of its 10 cells in order to command a digital reading of its assigned
pin (first cell belongs to pin 4; last one to pin 13, pins 2 and 3 are reserved for the camera).
- Digit. read. (Digital reading).- Once you command a reading, the input value
will be presented as activity in this group. If you command readings on
unconnected pins, expect to see random blinking, since the pull-up resistors
are not active by default.
- Comm. digit writ. (Command digital writing)(size 10).- Send a value different than 0 to
the cell assigned to the pin which you want to access.
- Digit. writ. (Digital writing)(size 10).- Once you command a writing, you use this 
group to manipulate the output value.
-Comm.PWM (Command Analog Writing)(size 6). -Once you command a writing, you use this 
group to manipulate the output value.
- PWM write (Analog Write)(size 6)- Once writing is commanded, this group manipulates the
-Comm. An. Read. (Command Analog Reading)- Send a value different than 0 to each of its 2 cells in order
to command an analog reading of its assigned pin output value.
-An.. Read. (Analog Reading). Once analog reading is commanded, the input values over threshold defined by the
light sensitivity parameterwill be presented as activity in this group 


- License
    See COPYING
