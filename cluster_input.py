import random
import sys

num_clusters = int(input("Enter number of clusters: ")) # k
num_points = int(input("Enter number of points per cluster: ")) # number of points in each cluster

file = open("input.txt","w")
#file.write(str(num_points) + "\n")
#file.write(str(num_clusters) + "\n")
file.write('{}'.format(num_points) + "\n")
file.write('{}'.format(num_clusters) + "\n")

variance = ""
for i in range(num_clusters):
	vari = random.uniform(1, 10)
	variance += str(vari) + " "
	x = random.uniform(-vari, vari)*5
	y = random.uniform(-vari, vari)*5
	file.write(str(x) + " " + str(y) + "\n")

file.write(variance)