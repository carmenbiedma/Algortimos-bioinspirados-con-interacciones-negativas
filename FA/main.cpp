#include <iostream>
#include <armadillo>
#include "firefly.h"

using namespace std;

double *OShift,*M,*y,*z,*x_bound;
int ini_flag=0,n_flag,func_flag,*SS;

int main(int argc, char **argv){
	int dim = 10;
	int ef=1;

	if (argc > 1) {
		ef = atoi(argv[1]);
	}


	Firefly prueba = Firefly(10,ef,dim*10000);

	prueba.initialize();
	prueba.algorithm();

	return 0;
}