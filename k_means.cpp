#include <iostream>
#include <fstream>
#include <random>
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
/*************serial***************************/

	/***********read in data************************/
	int len, dim, kmn;
	cout << "num_points, dimension, k: ";
	cin >> len >> dim >> kmn;
	ifstream infile("data2.txt");
	//float a, b;
	float points[len][dim];
	for(int i=0; i<len; i++) {
		for(int j=0; j<dim; j++) {
			float a;
			infile >> a;
			points[i][j] = a;
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
		minV[j] = points[0][j];
		maxV[j] = points[0][j];
	}
	for(int i=0; i<len; i++) {
		for(int j=0; j<dim; j++) {
			minV[j] = min(minV[j], points[i][j]);
			maxV[j] = max(maxV[j], points[i][j]);
		}
	} /////////////////a' = (a-min)/(max-min)////////////////////
	for(int i=0; i<len; i++) {
		for(int j=0; j<dim; j++)
			points[i][j] = (points[i][j]-minV[j])/(maxV[j]-minV[j]);
	}

	/*******************starting k-means********************************/
	for(int ep=0; ep<100; ep++) { //fix the number of iterations
		/************************* storing u averages as sums***********/
		for(int i=0; i<kmn; i++) {
			for(int j=0; j<=dim; j++)
				usum[i][j] = 0.0f;
		}
		for(int i=0; i<len; i++) { // each data point
			int index = getCluster(u, points[i], dim, kmn); //index of cluster 
			/****update the sum of the centre*****/
			for(int k=0; k<dim; k++) usum[index][k] += points[i][k];
			usum[index][dim] += 1.0f; //increment number of points in this cluster
		}
		for(int i=0; i<kmn; i++) {
			cout << "the elements in cluster "<< i <<" is" << usum[i][dim] << endl;
			for(int j=0; j<dim; j++)
				u[i][j] = usum[i][j]/usum[i][dim]; // update centre to average of cluster
		} //usum[i][dim] represents the number of elements in the cluster
	}
	/**********************writing to file**********************/
	ofstream myfile;
	myfile.open ("data.txt");
	for(int i=0; i<len; i++) {
		int color = getCluster(u, points[i], dim, kmn);
		for(int j=0; j<dim; j++)
			myfile << points[i][j] << " ";
		myfile << color << "\n";
	}

	myfile.close();
	return 0;
}
