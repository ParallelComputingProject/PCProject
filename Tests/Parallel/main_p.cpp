#include <iostream>
#include <fstream>
#include <random>
#include <omp.h>
#include "omp.h"
#include "stdio.h"
#include <chrono>
#include <vector>
#include <ios>
#include <fstream>
#include <string>
#include <math.h>
#include <random>
#include <cstdlib>
#include <ctime>


typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::duration<float> fsec;

std::ofstream timeData;


using namespace std;
float d(float *u, float *x, int dim) {
	float ans = 0;
	for(int i=0; i<dim; i++)
		ans += pow(u[i]-x[i], 2);
	return pow(ans, 0.5);
}

int getCluster(float **u, float *x, int dim, int kmn) {
	int indx = 0;
	float minD = d(u[0], x, dim);
	for(int j=0; j<kmn; j++) {
		if(d(u[j], x, dim) < minD) {
			minD = d(u[j], x, dim); //update min
			indx = j; // storing min index
		}
	}
	return indx;
}

int main() {
	/*************Parallel***************************/

	/***********read in data************************/
	int len, dim, kmn;
	cout << "num_points, dimension, k: ";
	cin >> len >> dim >> kmn;
	int perBlock = len/8;
	ifstream infile("data2.txt");
	//float a, b;
	float points01[perBlock][dim+1];
	float points02[perBlock][dim+1];
	float points03[perBlock][dim+1];
	float points04[perBlock][dim+1];
	float points05[perBlock][dim+1];
	float points06[perBlock][dim+1];
	float points07[perBlock][dim+1];
	float points08[perBlock][dim+1];

	for(int i=0; i<perBlock; i++) {
		for(int j=0; j<dim+1; j++) {
			float a;
			infile >> a;
			points01[i][j] = a;
		}
	}
	for(int i=perBlock; i<2*perBlock; i++) {
		for(int j=0; j<dim+1; j++) {
			float a;
			infile >> a;
			points02[i][j] = a;
		}
	}
	for(int i=2*perBlock; i<3*perBlock; i++) {
		for(int j=0; j<dim+1; j++) {
			float a;
			infile >> a;
			points03[i][j] = a;
		}
	}
	for(int i=3*perBlock; i<4*perBlock; i++) {
		for(int j=0; j<dim+1; j++) {
			float a;
			infile >> a;
			points04[i][j] = a;
		}
	}
	for(int i=4*perBlock; i<5*perBlock; i++) {
		for(int j=0; j<dim+1; j++) {
			float a;
			infile >> a;
			points05[i][j] = a;
		}
	}
	for(int i=5*perBlock; i<6*perBlock; i++) {
		for(int j=0; j<dim+1; j++) {
			float a;
			infile >> a;
			points06[i][j] = a;
		}
	}
	for(int i=6*perBlock; i<7*perBlock; i++) {
		for(int j=0; j<dim+1; j++) {
			float a;
			infile >> a;
			points07[i][j] = a;
		}
	}
	for(int i=7*perBlock; i<8*perBlock; i++) {
		for(int j=0; j<dim+1; j++) {
			float a;
			infile >> a;
			points08[i][j] = a;
		}
	}
	cout << len << endl;

	/******preparing k means*****************/
	float **u = new float*[kmn];
	for (int i = 0; i < kmn; ++i)
		u[i] = new float[dim];

	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> dis(0.0, 1.0);
	for(int i=0; i<kmn; i++) {
		for(int j=0; j<dim; j++)
			u[i][j] = dis(gen);
	}
	//storing the sums
	float usum[kmn][dim+1]; //the x1, x2, ..., xdim, n in cluster


	/********normalizing with min-max********************************/
	float minV[dim];
	float maxV[dim];
	for(int j=0; j<dim; j++) {
		minV[j] = points01[0][j];
		maxV[j] = points01[0][j];
	}
	for(int i=0; i<perBlock; i++) {
		for(int j=0; j<dim; j++) {
			minV[j] = min(minV[j], points01[i][j]);
			maxV[j] = max(maxV[j], points01[i][j]);
		}
	}
	for(int i=0; i<perBlock; i++) {
		for(int j=0; j<dim; j++) {
			minV[j] = min(minV[j], points02[i][j]);
			maxV[j] = max(maxV[j], points02[i][j]);
		}
	}
	for(int i=0; i<perBlock; i++) {
		for(int j=0; j<dim; j++) {
			minV[j] = min(minV[j], points03[i][j]);
			maxV[j] = max(maxV[j], points03[i][j]);
		}
	}
	for(int i=0; i<perBlock; i++) {
		for(int j=0; j<dim; j++) {
			minV[j] = min(minV[j], points04[i][j]);
			maxV[j] = max(maxV[j], points04[i][j]);
		}
	}
	for(int i=0; i<perBlock; i++) {
		for(int j=0; j<dim; j++) {
			minV[j] = min(minV[j], points05[i][j]);
			maxV[j] = max(maxV[j], points05[i][j]);
		}
	}
	for(int i=0; i<perBlock; i++) {
		for(int j=0; j<dim; j++) {
			minV[j] = min(minV[j], points06[i][j]);
			maxV[j] = max(maxV[j], points06[i][j]);
		}
	}
	for(int i=0; i<perBlock; i++) {
		for(int j=0; j<dim; j++) {
			minV[j] = min(minV[j], points07[i][j]);
			maxV[j] = max(maxV[j], points07[i][j]);
		}
	}
	for(int i=0; i<perBlock; i++) {
		for(int j=0; j<dim; j++) {
			minV[j] = min(minV[j], points08[i][j]);
			maxV[j] = max(maxV[j], points08[i][j]);
		}
	} /////////////////a' = (a-min)/(max-min)////////////////////
	for(int i=0; i<perBlock; i++) {
		for(int j=0; j<dim; j++) {
			points01[i][j] = (points01[i][j]-minV[j])/(maxV[j]-minV[j]);
		}
	}
	for(int i=0; i<perBlock; i++) {
		for(int j=0; j<dim; j++) {
			points02[i][j] = (points02[i][j]-minV[j])/(maxV[j]-minV[j]);
		}
	}
	for(int i=0; i<perBlock; i++) {
		for(int j=0; j<dim; j++) {
			points03[i][j] = (points03[i][j]-minV[j])/(maxV[j]-minV[j]);
		}
	}
	for(int i=0; i<perBlock; i++) {
		for(int j=0; j<dim; j++) {
			points04[i][j] = (points04[i][j]-minV[j])/(maxV[j]-minV[j]);
		}
	}
	for(int i=0; i<perBlock; i++) {
		for(int j=0; j<dim; j++) {
			points05[i][j] = (points05[i][j]-minV[j])/(maxV[j]-minV[j]);
		}
	}
	for(int i=0; i<perBlock; i++) {
		for(int j=0; j<dim; j++) {
			points06[i][j] = (points06[i][j]-minV[j])/(maxV[j]-minV[j]);
		}
	}
	for(int i=0; i<perBlock; i++) {
		for(int j=0; j<dim; j++) {
			points07[i][j] = (points07[i][j]-minV[j])/(maxV[j]-minV[j]);
		}
	}
	for(int i=0; i<perBlock; i++) {
		for(int j=0; j<dim; j++) {
			points08[i][j] = (points08[i][j]-minV[j])/(maxV[j]-minV[j]);
		}
	}

	auto start = Time::now();
	omp_set_num_threads(8);
	#pragma omp parallel
	{
		/*******************starting k-means********************************/
		for(int ep=0; ep<100; ep++) { //fix the number of iterations
			/************************* storing u averages as sums***********/
			for(int i=0; i<kmn; i++) {
				for(int j=0; j<=dim; j++)
					usum[i][j] = 0.0f;
			}

			#pragma omp sections
			{
				#pragma omp section
				{
					for(int i=0; i<perBlock; i++) { // each data point
						int index = getCluster(u, points01[i], dim, kmn); //index of cluster
						/****update the sum of the centre*****/
						for(int k=0; k<dim; k++) usum[index][k] += points01[i][k];
						usum[index][dim] += 1.0f; //increment number of points in this cluster
					}
					for(int i=0; i<kmn; i++) {
						cout << "the elements in cluster "<< i <<" is" << usum[i][dim] << endl;
						for(int j=0; j<dim; j++)
							u[i][j] = usum[i][j]/usum[i][dim]; // update centre to average of cluster
					} //usum[i][dim] represents the number of elements in the cluster
				}
				#pragma omp section
				{
					for(int i=0; i<perBlock; i++) { // each data point
						int index = getCluster(u, points02[i], dim, kmn); //index of cluster
						/****update the sum of the centre*****/
						for(int k=0; k<dim; k++) usum[index][k] += points02[i][k];
						usum[index][dim] += 1.0f; //increment number of points in this cluster
					}
					for(int i=0; i<kmn; i++) {
						cout << "the elements in cluster "<< i <<" is" << usum[i][dim] << endl;
						for(int j=0; j<dim; j++)
							u[i][j] = usum[i][j]/usum[i][dim]; // update centre to average of cluster
					} //usum[i][dim] represents the number of elements in the cluster
				}
				#pragma omp section
				{
					for(int i=0; i<perBlock; i++) { // each data point
						int index = getCluster(u, points03[i], dim, kmn); //index of cluster
						/****update the sum of the centre*****/
						for(int k=0; k<dim; k++) usum[index][k] += points03[i][k];
						usum[index][dim] += 1.0f; //increment number of points in this cluster
					}
					for(int i=0; i<kmn; i++) {
						cout << "the elements in cluster "<< i <<" is" << usum[i][dim] << endl;
						for(int j=0; j<dim; j++)
							u[i][j] = usum[i][j]/usum[i][dim]; // update centre to average of cluster
					} //usum[i][dim] represents the number of elements in the cluster
				}
				#pragma omp section
				{
					for(int i=0; i<perBlock; i++) { // each data point
						int index = getCluster(u, points04[i], dim, kmn); //index of cluster
						/****update the sum of the centre*****/
						for(int k=0; k<dim; k++) usum[index][k] += points04[i][k];
						usum[index][dim] += 1.0f; //increment number of points in this cluster
					}
					for(int i=0; i<kmn; i++) {
						cout << "the elements in cluster "<< i <<" is" << usum[i][dim] << endl;
						for(int j=0; j<dim; j++)
							u[i][j] = usum[i][j]/usum[i][dim]; // update centre to average of cluster
					} //usum[i][dim] represents the number of elements in the cluster
				}
				#pragma omp section
				{
					for(int i=0; i<perBlock; i++) { // each data point
						int index = getCluster(u, points05[i], dim, kmn); //index of cluster
						/****update the sum of the centre*****/
						for(int k=0; k<dim; k++) usum[index][k] += points05[i][k];
						usum[index][dim] += 1.0f; //increment number of points in this cluster
					}
					for(int i=0; i<kmn; i++) {
						cout << "the elements in cluster "<< i <<" is" << usum[i][dim] << endl;
						for(int j=0; j<dim; j++)
							u[i][j] = usum[i][j]/usum[i][dim]; // update centre to average of cluster
					} //usum[i][dim] represents the number of elements in the cluster
				}
				#pragma omp section
				{
					for(int i=0; i<perBlock; i++) { // each data point
						int index = getCluster(u, points06[i], dim, kmn); //index of cluster
						/****update the sum of the centre*****/
						for(int k=0; k<dim; k++) usum[index][k] += points06[i][k];
						usum[index][dim] += 1.0f; //increment number of points in this cluster
					}
					for(int i=0; i<kmn; i++) {
						cout << "the elements in cluster "<< i <<" is" << usum[i][dim] << endl;
						for(int j=0; j<dim; j++)
							u[i][j] = usum[i][j]/usum[i][dim]; // update centre to average of cluster
					} //usum[i][dim] represents the number of elements in the cluster
				}
				#pragma omp section
				{
					for(int i=0; i<perBlock; i++) { // each data point
						int index = getCluster(u, points07[i], dim, kmn); //index of cluster
						/****update the sum of the centre*****/
						for(int k=0; k<dim; k++) usum[index][k] += points07[i][k];
						usum[index][dim] += 1.0f; //increment number of points in this cluster
					}
					for(int i=0; i<kmn; i++) {
						cout << "the elements in cluster "<< i <<" is" << usum[i][dim] << endl;
						for(int j=0; j<dim; j++)
							u[i][j] = usum[i][j]/usum[i][dim]; // update centre to average of cluster
					} //usum[i][dim] represents the number of elements in the cluster
				}
				#pragma omp section
				{
					for(int i=0; i<perBlock; i++) { // each data point
						int index = getCluster(u, points08[i], dim, kmn); //index of cluster
						/****update the sum of the centre*****/
						for(int k=0; k<dim; k++) usum[index][k] += points08[i][k];
						usum[index][dim] += 1.0f; //increment number of points in this cluster
					}
					for(int i=0; i<kmn; i++) {
						cout << "the elements in cluster "<< i <<" is" << usum[i][dim] << endl;
						for(int j=0; j<dim; j++)
							u[i][j] = usum[i][j]/usum[i][dim]; // update centre to average of cluster
					} //usum[i][dim] represents the number of elements in the cluster
				}
			}
		}
	}
	auto end = Time::now();
	fsec time = end - start;

	//Write times to file
	timeData.open("times/Data.csv", std::ios_base::app);
	string toSave;
	toSave.append(to_string(len)+",")
			.append(to_string(kmn)+",")
			.append(to_string(time.count()))
			.append("\n");
	timeData << toSave;
	timeData.close();

	cout << "The running time is " << time.count() << endl;

	/**********************writing to file**********************/
	ofstream myfile;
	myfile.open ("data.txt");
	for(int i=0; i<perBlock; i++) {
		int color = getCluster(u, points01[i], dim, kmn);
		for(int j=0; j<dim; j++)
			myfile << points01[i][j] << " ";
		myfile << color << "\n";
	}
	for(int i=0; i<perBlock; i++) {
		int color = getCluster(u, points02[i], dim, kmn);
		for(int j=0; j<dim; j++)
			myfile << points02[i][j] << " ";
		myfile << color << "\n";
	}
	for(int i=0; i<perBlock; i++) {
		int color = getCluster(u, points03[i], dim, kmn);
		for(int j=0; j<dim; j++)
			myfile << points03[i][j] << " ";
		myfile << color << "\n";
	}
	for(int i=0; i<perBlock; i++) {
		int color = getCluster(u, points04[i], dim, kmn);
		for(int j=0; j<dim; j++)
			myfile << points04[i][j] << " ";
		myfile << color << "\n";
	}
	for(int i=0; i<perBlock; i++) {
		int color = getCluster(u, points05[i], dim, kmn);
		for(int j=0; j<dim; j++)
			myfile << points05[i][j] << " ";
		myfile << color << "\n";
	}
	for(int i=0; i<perBlock; i++) {
		int color = getCluster(u, points06[i], dim, kmn);
		for(int j=0; j<dim; j++)
			myfile << points06[i][j] << " ";
		myfile << color << "\n";
	}
	for(int i=0; i<perBlock; i++) {
		int color = getCluster(u, points07[i], dim, kmn);
		for(int j=0; j<dim; j++)
			myfile << points07[i][j] << " ";
		myfile << color << "\n";
	}
	for(int i=0; i<perBlock; i++) {
		int color = getCluster(u, points08[i], dim, kmn);
		for(int j=0; j<dim; j++)
			myfile << points08[i][j] << " ";
		myfile << color << "\n";
	}

	myfile.close();
	return 0;
}
