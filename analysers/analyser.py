import matplotlib.pyplot as plt
from matplotlib.collections import LineCollection
from matplotlib.colors import ListedColormap, BoundaryNorm
import numpy as np


X = []
Y = []
T = []

KINETIC = []
POTENTIAL = []
ENERGY = []
with open("./output/verlet.txt", "r") as file:
    for line in file.readlines():
        # (
        #     ind,
        #     t,
        #     x1,
        #     x2,
        #     x3,
        #     *other
        # ) = line
        # 
        (index, t, r, v, a) = line.split(", ")
        (x, y, z) = map(lambda x: float(x), r.replace("(", "").replace(")", "").split(";") )

        (rx, ry, rz) = map(lambda x: float(x), r.replace("(", "").replace(")", "").split(";") )
        (vx, vy, vz) = map(lambda x: float(x), v.replace("(", "").replace(")", "").split(";") )
        (ax, ay, az) = map(lambda x: float(x), a.replace("(", "").replace(")", "").split(";") )

        
        X.append(x)
        Y.append(y)
        T.append(float(t))

        k = (vx**2 + vy**2 + vz**2) / 2
        KINETIC.append(k)

        p = float(np.sqrt((ax**2 + ay**2 + az**2) * (rx**2 + ry**2 + rz**2)))
        POTENTIAL.append(p)

        ENERGY.append(KINETIC[-1] + POTENTIAL[-1])
        #points.append((x, y))

fig, ax = plt.subplots(sharex=True, sharey=True)
# plt.scatter(X, Y, c = np.tan(np.linspace(-1, 1, len(X))) ,marker=".")
norm = plt.Normalize(0, max(T))

points = np.array([X, Y]).T.reshape(-1, 1, 2)
segments = np.concatenate([points[:-1], points[1:]], axis=1)
lc = LineCollection(segments, cmap='viridis', norm=norm)
# Set the values used for colormapping
lc.set_array(np.array(T))
lc.set_linewidth(1)

line = ax.add_collection(lc)
# fig.colorbar(line, ax=axs[0])
ax.set_xlim(min(X)+0.2*min(X), 1.1*max(X))
ax.set_ylim(min(Y)+0.2*min(X), 1.1*max(Y))
fig.colorbar(line, ax=ax)


efig, eax = plt.subplots(sharex=True, sharey=True)
eax.plot(T, ENERGY, label="full energy")
eax.plot(T, KINETIC, label="kinetic energy")
eax.plot(T, POTENTIAL, label="potential energy")
eax.set_xlabel("t (s)")
eax.set_ylabel("E/m J/kg")

eax.legend()
plt.show()