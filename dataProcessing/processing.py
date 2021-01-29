import numpy as np
import matplotlib.pyplot as plt
data = np.genfromtxt("./data/reward.txt", delimiter=',',)

# data[data == -1] = 0

data = data.mean(axis = 0)

data = np.cumsum(data) / np.arange(1, len(data)+1)


plt.plot(data)
plt.savefig("figures/dsada1")

print(data)