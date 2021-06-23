import serial

# XBee setting
serdev = '/dev/ttyUSB0'
s = serial.Serial(serdev, 9600)

import serial

line = s.read(5)
print('0:', line.decode())
line = s.read(10)
print('1:', line.decode())

line = s.read(4)
print('2:', line.decode())

line = s.read(9)
print('3:', line.decode())
line = s.read(4)
print('4:', line.decode())

s.close()