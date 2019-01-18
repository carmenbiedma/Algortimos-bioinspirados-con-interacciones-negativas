#include <iostream>
#include <armadillo>
#include "da.h"

using namespace std;

double *OShift,*M,*y,*z,*x_bound;
int ini_flag=0,n_flag,func_flag,*SS;

int main(int argc, char **argv){
	int dim = 30;
	int ef=1;

	if (argc > 1) {
		ef = atoi(argv[1]);
	}


	int n=30; //Tamaño de la poblacion

	DragonFly prueba(10,ef);
	int n_iter=dim*10000; //iteraciones maximas

	prueba.initialize(dim);
	for(int i=0;i<n_iter;i++){
		prueba.calculateFitness();
		prueba.calculateValues(i,n_iter);
	}
	
	pair<Row<double>,double> solution = prueba.bestSolution();
	cout<<solution.second - ef*100 <<";";
	return 0;
}