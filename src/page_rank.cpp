#include <iostream>
#include <fstream>
#include <iomanip> 
#include <cmath>
using namespace std;

#define Alpha 0.85
#define Iter_max 500
#define Error_min 1e-12

double max_err (double*, double*, int);

int main () {
	int n, m, a, b;
	int iter = 0;
	double error = 1e6; 
	ifstream fin;
	ofstream fout;
	fin.open("hw2-sample-input");
	if (fin.is_open()) {
		fin >> n >> m;
	}
	
	//Initialize
	int *L = new int [n];
	double *PR_old = new double [n];
	double *PR_new = new double [n];
	int **A = new int* [n];
	for (int i = 0; i < n; ++i) {
		A[i] = new int[n];
	}
	
	for (int i=0; i<n; i++) {
		PR_old[i] = 1/n;
		L[i] = 0;
		for (int j=0; j<n; j++) {
			A[i][j] = 0;
		}
	}
	
	for (int i=0; i<m; i++) {
		fin >> a >> b;
		A[b-1][a-1]++;
		L[a-1]++;
	}
	fin.close();
	
	for (int i=0; i<n; i++) {
		if (L[i]==0) {
			L[i] = n;
			for (int j=0; j<n; j++) {
				A[j][i]++;
			}
		}
	}

	//Main computation
	while (iter<Iter_max && error>Error_min) {
		for (int i=0; i<n; i++) {
			PR_new[i] = (1-Alpha)/n;
			for (int j=0; j<n; j++) {
				PR_new[i] += Alpha*A[i][j]*PR_old[j]/L[j];
			}
 		}
 		error = max_err(PR_old, PR_new, n);
 		for (int i=0; i<n; i++) {
 			PR_old[i] = PR_new[i];
		 }
		 iter++;
	}
	
	fout.open("hw2-sample-output");
	if (fout.is_open()) {
		for (int i=0; i<n; i++) {
			fout << setprecision(12) << PR_new[i] << endl;
		}
	}
	fout.close();
	
	return 0;
}

double max_err (double *a_old, double *a_new, int len) {
	double err_max = -1;
	for (int i=0; i<len; i++) {
		if (abs(a_old[i]-a_new[i]) > err_max) {
			err_max = abs(a_old[i]-a_new[i]);
		} 
	}
	return err_max;
}
