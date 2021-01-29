import numpy as np
import matplotlib.pyplot as plt
data1 = np.genfromtxt("/RLAss2/data/reward.txt", delimiter=',',)
data2 = np.getfromtxt("/RLAss2/data/reward.txt", delimiter=',',)

# data[data == -1] = 0
data1 = data1.mean(axis = 0)
data2 = data2.mean(axis = 0)

data1 = np.cumsum(data1) / np.arange(1, len(data1)+1)
data2 = np.cumsum(data2) / np.arange(1, len(data2)+1)

plt.plot(data1)
plt.plot(data2)
plt.savefig("figures/dsada2")
