import sys
from ctypes import sizeof, c_double
import struct
import matplotlib.pyplot as plt
from math import pi

double_size = sizeof(c_double)

inp = open('output.bin', 'rb')

def getDouble():
	a = inp.read(double_size)
	if len(a) < double_size: raise EOFError
	a = struct.unpack('d', a)[0]
	return a

x, y = [], []

while True:
	try:
		x.append(getDouble())
		y.append(getDouble())
	except EOFError:
		break

inp.close()

plt.plot(x, y)
#plt.set_title('Distribution')
#plt.set_xlabel('x, m')
#plt.set_ylabel('y, m')
plt.savefig('output.png', transparent=True)
