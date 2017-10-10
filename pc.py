import numpy as np
import matplotlib.pyplot as plt
import random
import sys

num_points = input("Enter a number of points: ") # number of points in each cluster
num_clusters = input("Enter a number of clusters: ") # k
cluster_means = [] # matrix of means

for i in range(num_clusters): # read row by row
	c_i = raw_input("Enter cluster mean of cluster "+str(i)+": ")
	m_i = map(float, c_i.split())
	cluster_means.append(m_i)

c_v = raw_input("Enter list of variance: ")
covarience = map(float, c_v.split()) # variance of the cluster: keep it round...

file = open("data2.txt","w")
cov = []
dim = len(cluster_means[0])

for k in range(dim):
	cov.append([0] * dim)

data = []

for j in range(num_clusters):
	mean = cluster_means[j]
	for l in range(dim):
		cov[l][l] = covarience[j]
	coords = np.random.multivariate_normal(mean, cov, num_points)
	data.extend(coords)

lis = range(num_clusters*num_points)
random.shuffle(lis)
for h in lis:
	file.write(" ".join(map(str, data[h])) + "\n")

# file.close()
X = np.array(data)
plt.plot(X.T[0], X.T[1], 'x')
plt.axis('equal')
plt.show()
