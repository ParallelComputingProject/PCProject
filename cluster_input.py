import random
import sys

num_clusters = int(input("Enter number of clusters: ")) # k
num_points = int(input("Enter number of points per cluster: ")) # number of points in each cluster
dim = int(input("Enter set dimension: "))

k_means_input = open("test1.txt","w")
k_means_input.write(str(num_clusters*num_points) + " " + str(dim) + " " + str(num_clusters))
k_means_input.close()

file = open("input.txt","w")
#file.write(str(num_points) + "\n")
#file.write(str(num_clusters) + "\n")
file.write('{}'.format(num_points) + "\n")
file.write('{}'.format(num_clusters) + "\n")

variance = ""
for i in range(num_clusters):
	vari = random.uniform(1, 10)
	variance += str(vari) + " "

	for j in range(dim):
		point = random.uniform(-vari*5, vari*5)
		file.write(str(point) + " ")
	
	file.write("\n")

file.write(variance)