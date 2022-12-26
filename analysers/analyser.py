import matplotlib.pyplot as plt
from matplotlib.collections import LineCollection
from matplotlib.colors import ListedColormap, BoundaryNorm
import numpy as np
import sys

import totex

print("Args: ", sys.argv)
print("Looking for file: ", sys.argv[1])

NAME = ".".join(sys.argv[1].split("\\")[-1].split(".")[:-1])
print("Output filenames: ", NAME)

X = []
Y = []
T = []

VX = []
VY = []

KINETIC = []
POTENTIAL = []
ENERGY = []
# "./output/predcorr.txt"
with open(sys.argv[1], "r") as file:
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

        VX.append(vx)
        VY.append(vy)
        T.append(float(t))

        k = (vx**2 + vy**2 + vz**2) / 2
        KINETIC.append(k)

        p = float(np.sqrt((ax**2 + ay**2 + az**2) * (rx**2 + ry**2 + rz**2)))
        POTENTIAL.append(p)

        ENERGY.append(KINETIC[-1] + POTENTIAL[-1])
        #points.append((x, y))
print("End Reading")

if "-gp" in sys.argv:
    fig, ax = plt.subplots(sharex=True, sharey=True)
    # plt.scatter(X, Y, c = np.tan(np.linspace(-1, 1, len(X))) ,marker=".")
    norm = plt.Normalize(0, max(T))

    points = np.array([X, Y]).T.reshape(-1, 1, 2)
    segments = np.concatenate([points[:-1], points[1:]], axis=1)
    lc = LineCollection(segments, cmap='viridis', norm=norm)
    # Set the values used for colormapping
    lc.set_array(np.array(T))
    lc.set_linewidth(0.1)

    line = ax.add_collection(lc)
    # fig.colorbar(line, ax=axs[0])
    ax.set_xlim(min(X)+0.2*min(X), 1.1*max(X))
    ax.set_ylim(min(Y)+0.2*min(X), 1.1*max(Y))
    fig.colorbar(line, ax=ax)

    #fig.savefig(f"./images/{NAME}-path.eps")

    ax.set_ylim(Y[0]-1e2, max(Y)+1e2)
    ax.set_xlim(X[0]-2*1e3, X[0]+10*1e3)
    fig.savefig(f"./images/{NAME}-path-diforbit.eps")


    efig, eax = plt.subplots(sharex=True, sharey=True)
    eax.plot(T, ENERGY, label="full energy")
    eax.plot(T, KINETIC, label="kinetic energy")
    eax.plot(T, POTENTIAL, label="potential energy")
    eax.set_xlabel("t (s)")
    eax.set_ylabel("E/m J/kg")
    eax.legend()

    fig.savefig(f"./images/{NAME}-energy.eps")

if "-tbs" in sys.argv:
    TBF = "./tables"

    tHeaders = [
        "attr",
        "min",
        "max",
        "$\Delta$",
        "mid",
        "deviation"
    ]
    tData = []

    def coopl(attr, d, out):
        res = [attr, float(np.min(d)), float(np.max(d)), float(np.max(d) - np.min(d))]
        mid = float(np.sum(d) / len(d))
        res.append(mid)
        
        det = np.vectorize(lambda x: (mid - x)**2)
        dev = float(np.sqrt(np.sum(det(d)) / (len(d) * (len(d)-1))))

        res.append(dev)

        for i in range(1, len(res)):
            res[i] = round(res[i], 6)

        out.append(res)

    coopl("$\\lvert r\\lvert$ [m]", np.sqrt(np.array(X)**2 + np.array(Y)**2), tData)
    coopl("$\\lvert v\\lvert$ [m/s]", np.sqrt(np.array(VX)**2 + np.array(VY)**2), tData)
    coopl("$\\lvert T\\lvert$ [J]", np.array(KINETIC), tData)
    coopl("$\\lvert U\\lvert$ [J]", np.array(POTENTIAL), tData)
    coopl("$\\lvert E\\lvert$ [J]", np.array(ENERGY), tData)

    totex.tabtex.convertFromData(
        TBF,
        f"{NAME}-stat",
        f"Simulated Data Statistics by {NAME}",
        tHeaders,
        tData
    )

# plt.show()

print("Done")