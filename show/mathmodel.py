import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from math import pi, sin, cos, tan, fabs
import numpy as np

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

for phi in myirange(0, 2 * pi, 0.01):
    for theta in myirange(0, pi / 2 - 0.2, 0.01):
        x.append(phi)
        y.append(cos(theta))
        t = (w - D * tan(theta) * fabs(cos(phi)))
        if t <= 0: t = 0
        else: t *= (h - D * tan(theta) * fabs(sin(phi)))
        if t <= 0: t = 0

        # print(phi, theta, t)
        z.append(t / S)

ax.set_xlabel('Phi')
ax.set_ylabel('Cos Theta')
ax.set_title('Efficiency')
#ax.set_zlim(0, 1)
ax.scatter(x, y, z, marker=',', c=z, cmap='jet')
plt.savefig('math.png', transparent=True, dpi=500)
