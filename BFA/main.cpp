#include <iostream>
#include <armadillo>
#include "bfa.h"

using namespace std;


double *OShift,*M,*y,*z,*x_bound;
int ini_flag=0,n_flag,func_flag,*SS;

int main(int argc, char **argv){

	int ef=12;

	if (argc > 1) {
		ef = atoi(argv[1]);
	}

	BFA prueba = BFA(10,ef);
	prueba.initialize();
	prueba.algorithm();
	return 0;

}
