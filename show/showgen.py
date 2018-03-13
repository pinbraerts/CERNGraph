import struct
from ctypes import c_double, sizeof
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

inp = open('genoutput.bin', 'rb')

double_size = sizeof(c_double)

def getDouble():
	a = inp.read(double_size)
	if len(a) < double_size: raise EOFError
	a = struct.unpack('d', a)[0]
	return a

x, y, z = [], [], []

while True:
    try:
        x.append(getDouble())
        y.append(getDouble())
        z.append(getDouble())
    except EOFError:
        break

inp.close()

fig = plt.figure()
ax = fig.add_subplot(111, projection = '3d')
ax.set_xlabel("Phi")
ax.set_ylabel("Cos Theta")
ax.set_title("Efficiency")
ax.scatter(x, y, z, marker=',', c=z, cmap='jet')
plt.savefig('genpic.png', transparent=True, dpi=500)
