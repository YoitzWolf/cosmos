import matplotlib.pyplot as plt
from matplotlib.collections import LineCollection
from matplotlib.colors import ListedColormap, BoundaryNorm
import numpy as np

X = []
Y = []
T = []
with open("./output/sim.txt", "r") as file:
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


        
        X.append(x)
        Y.append(y)
        T.append(float(t))
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

plt.show()