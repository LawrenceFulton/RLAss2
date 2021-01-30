import numpy as np
import matplotlib.pyplot as plt



mouse = "Q_EPS"
path = "./data/"+mouse +"/"+ mouse + "_"


SARSA_EPS = np.genfromtxt(path + "SARSA_EPS.txt", delimiter=',')
SARSA_UCB = np.genfromtxt(path + "SARSA_UCB.txt", delimiter=',')


Q_EPS = np.genfromtxt(path + "Q_EPS.txt", delimiter=',')
Q_UCB = np.genfromtxt(path + "Q_UCB.txt", delimiter=',')

QQ_EPS = np.genfromtxt(path + "QQ_EPS.txt", delimiter=',')
QQ_UCB = np.genfromtxt(path + "QQ_UCB.txt", delimiter=',')


# data[data == -1] = 0
SARSA_EPS = SARSA_EPS.mean(axis = 0)
SARSA_UCB = SARSA_UCB.mean(axis = 0)

Q_EPS = Q_EPS.mean(axis = 0)
Q_UCB = Q_UCB.mean(axis = 0)

QQ_EPS = QQ_EPS.mean(axis = 0)
QQ_UCB = QQ_UCB.mean(axis = 0)


SARSA_EPS = np.cumsum(SARSA_EPS) / np.arange(1, len(SARSA_EPS)+1)
SARSA_UCB = np.cumsum(SARSA_UCB) / np.arange(1, len(SARSA_UCB)+1)

Q_EPS = np.cumsum(Q_EPS) / np.arange(1, len(Q_EPS)+1)
Q_UCB = np.cumsum(Q_UCB) / np.arange(1, len(Q_UCB)+1)

QQ_EPS = np.cumsum(QQ_EPS) / np.arange(1, len(QQ_EPS)+1)
QQ_UCB = np.cumsum(QQ_UCB) / np.arange(1, len(QQ_UCB)+1)


plt.plot(SARSA_EPS, label = "SARSA EPS")
plt.plot(SARSA_UCB, label = "SARSA UCB")

plt.plot(Q_EPS, label ="Q EPS")
plt.plot(Q_UCB, label = "Q UCB")

plt.plot(QQ_EPS, label = "QQ EPS")
plt.plot(QQ_UCB, label = "QQ UCB")


title = "Mouse using Q-learning and EPS"

plt.title(title)
plt.xlabel("Epochs")
plt.ylabel("Cumilative mean of reward (Mouse perspective)")
plt.legend()



plt.savefig("figures/1.pdf")
