import matplotlib.pyplot as plt
import numpy as np
x, y, color = np.loadtxt("data2.txt").T
plt.scatter(x, y ,c=color)
plt.show()