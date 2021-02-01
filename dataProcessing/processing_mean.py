import numpy as np
import matplotlib.pyplot as plt



mouse = "QQ_UCB"
path = "./data/"+mouse +"/"+ mouse + "_"


SARSA_EPS = np.genfromtxt(path + "SARSA_EPS.txt", delimiter=',')
SARSA_UCB = np.genfromtxt(path + "SARSA_UCB.txt", delimiter=',')

Q_EPS = np.genfromtxt(path + "Q_EPS.txt", delimiter=',')
Q_UCB = np.genfromtxt(path + "Q_UCB.txt", delimiter=',')

QQ_EPS = np.genfromtxt(path + "QQ_EPS.txt", delimiter=',')
QQ_UCB = np.genfromtxt(path + "QQ_UCB.txt", delimiter=',')


sd_SARSA_EPS = np.delete(SARSA_EPS, -1, 1)
sd_SARSA_EPS = sd_SARSA_EPS.mean(axis=1)
sd_SARSA_EPS = np.nanstd(sd_SARSA_EPS)

# STD
sd_SARSA_UCB = np.delete(SARSA_UCB, -1, 1)
sd_SARSA_UCB = sd_SARSA_UCB.mean(axis=1)
sd_SARSA_UCB = np.nanstd(sd_SARSA_UCB)

sd_Q_EPS = np.delete(Q_EPS, -1, 1)
sd_Q_EPS = sd_Q_EPS.mean(axis=1)
sd_Q_EPS = np.nanstd(sd_Q_EPS)

sd_Q_UCB = np.delete(Q_UCB, -1, 1)
sd_Q_UCB = sd_Q_UCB.mean(axis=1)
sd_Q_UCB = np.nanstd(sd_Q_UCB)

sd_QQ_EPS = np.delete(QQ_EPS, -1, 1)
sd_QQ_EPS = sd_QQ_EPS.mean(axis=1)
sd_QQ_EPS = np.nanstd(sd_QQ_EPS)

sd_QQ_UCB = np.delete(QQ_UCB, -1, 1)
sd_QQ_UCB = sd_QQ_UCB.mean(axis=1)
sd_QQ_UCB = np.nanstd(sd_QQ_UCB)



# MEAN
SARSA_EPS = np.nanmean(SARSA_EPS)
SARSA_UCB = np.nanmean(SARSA_UCB)

Q_EPS = np.nanmean(Q_EPS)
Q_UCB = np.nanmean(Q_UCB)

QQ_EPS = np.nanmean(QQ_EPS)
QQ_UCB = np.nanmean(QQ_UCB)





print(SARSA_EPS, sd_SARSA_EPS)
print(SARSA_UCB, sd_SARSA_UCB)
print(Q_EPS, sd_Q_EPS)
print(Q_UCB ,sd_Q_UCB)
print(QQ_EPS , sd_QQ_EPS)
print(QQ_UCB, sd_QQ_UCB)

print(mouse + ":", np.mean([SARSA_UCB,SARSA_UCB, Q_EPS, Q_UCB, QQ_EPS, QQ_UCB]))

