import sys
from ctypes import sizeof, c_double, c_size_t
import struct
import matplotlib.pyplot as plt

double_size = sizeof(c_double)
size_t_size = sizeof(c_size_t)

inputf = open('imoutput.bin', 'rb')

def getDouble():
    a = inputf.read(double_size)
    if len(a) < double_size: raise EOFError
    a = struct.unpack('d', a)[0]
    return a

def getSizeT():
    a = inputf.read(size_t_size)
    if len(a) < size_t_size: raise EOFError
    a = struct.unpack('N', a)[0]
    return a

x, y, z = [], [], []

c = 0
while True:
    try:
        x.append(getDouble())
        y.append(getDouble())
        z.append(getSizeT())
        #if c >= 10: raise EOFError
        #c += 1
    except EOFError:
        break

inputf.close()

#print(x, y, z, file=sys.stderr)

plt.scatter(x, y, marker=',', c=z, cmap='YlOrBr')
plt.savefig('image.png', transparent=True) # plt.show()
