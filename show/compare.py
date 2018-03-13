import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from math import pi, sin, cos, tan, fabs
import struct
from ctypes import c_double, sizeof

double_size = sizeof(c_double)

fig = plt.figure()
ax = fig.add_subplot(111, projection = '3d')
h = 1.0
w = 1.7
mar = 0.1
D = 0.9
S = (h + 2 * mar) * (w + 2 * mar)

def myirange(s, e, d):
    if d > 0:
        while s < e:
            yield s
            s += d
    elif d < 0:
        while s > e:
            yield s
            s += d

x, y, z = [], [], []

inp = open('..\\data\\genoutput.bin', 'rb')

def getDouble():
	a = inp.read(double_size)
	if len(a) < double_size: raise EOFError
	a = struct.unpack('d', a)[0]
	return a

while True:
    try:
        phi = getDouble()
        ct = getDouble() - 0.1
        tt = 1 / ct / ct - 1
        x.append(phi)
        y.append(ct)
        t = (w - D * tt * fabs(cos(phi)))
        if t <= 0: t = 0
        else: t *= (h - D * tt * fabs(sin(phi)))
        if t <= 0: t = 0

        # print(phi, theta, t)
        z.append(t / S - getDouble())
    except EOFError:
        break

inp.close()

ax.set_xlabel('Phi')
ax.set_ylabel('Cos Theta')
ax.set_title('Efficiency')
#ax.set_zlim(0, 1)
ax.scatter(x, y, z, marker=',', c=z, cmap='jet')
plt.savefig('compa.png', transparent=True, dpi=500)
